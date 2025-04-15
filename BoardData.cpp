#include "BoardData.h"
#include <fstream>
#include <QDebug>

int BoardData::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_data.size();
}

QHash<int, QByteArray> BoardData::roleNames() const {
    return {
        {boardName, "name"},
        {boardDescription, "description"},
        {boardCreationTime, "creationTime"},
        {boardId, "id"}
    };
}

QVariant BoardData::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    const auto& item = m_data[index.row()];
    switch (role) {
    case boardName:  return item->name();
    case boardDescription: return item->description();
    case boardCreationTime: return item->creationTime();
    case boardId: return item->id();
    default:        return QVariant();
    }
}

void BoardData::addBoards() {
    SQLite::Statement boards = db.getData("board", "*", "board_id <> 1");

    while(boards.executeStep()){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        int id = boards.getColumn(0);

        BoardObject* board = new BoardObject(id,
                                             QString::fromStdString(boards.getColumn(1).getString()),
                                             (boards.getColumn(2).getString().size() == 0 ? "Описание отсутствует" : QString::fromStdString(boards.getColumn(2).getString())),
                                             QString::fromStdString(boards.getColumn(3).getString()));
        this->m_data.emplace_back(board);

        endInsertRows();
    }
}

void BoardData::exportBoard(QString name, int boardId){
    SQLite::Statement tasks = this->db.getData("task", "*", "board_id = " + std::to_string(boardId));

    std::ofstream out;
    std::wstring fileName = name.toStdWString();
    out.open((Global::getProjectPath() + "\\" + std::string(fileName.begin(), fileName.end()) + ".csv").c_str(),
             std::ios::out | std::ios::binary);

    out << "\xEF\xBB\xBF";

    out << "Task;Description;Creation Date;Task type\n";


    while(tasks.executeStep()){
        out << tasks.getColumn(3).getString() << ';'
            << ( tasks.getColumn(4).getString().size() == 0 ? "" : tasks.getColumn(4).getString()) << ';'
            << tasks.getColumn(5).getString() << ';';
        SQLite::Statement type = this->db.getData("type", "*", "type_id = " + tasks.getColumn(2).getString());
        if(type.executeStep()){
            out << type.getColumn(2) << '\n';
        }
    }

    out.close();
}

void BoardData::deleteBoard(int boardId){
    this->db.deleteData("task", "board_id = " + std::to_string(boardId));
    this->db.deleteData("type", "board_id = " + std::to_string(boardId));
    this->db.deleteData("board", "board_id = " + std::to_string(boardId));

    refreshModel();
}

void BoardData::refreshModel(){
    beginResetModel();

    for (auto item : m_data) {
        delete item;
    }
    m_data.clear();

    addBoards();

    endResetModel();
    emit modelUpdated();
}
