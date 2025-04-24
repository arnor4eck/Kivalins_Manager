#include "BoardData.h"
#include <QStringConverter>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
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
                                             (boards.getColumn(2).getString().size() == 0 ? "ÐžÐ¿Ð¸ÑÐ°Ð½Ð¸Ðµ Ð¾Ñ‚ÑÑƒÑ‚ÑÑ‚Ð²ÑƒÐµÑ‚" : QString::fromStdString(boards.getColumn(2).getString())),
                                             QString::fromStdString(boards.getColumn(3).getString()));
        this->m_data.emplace_back(board);

        endInsertRows();
    }
}

void BoardData::exportBoard(QUrl url, int boardId){
    QString filePath = url.toLocalFile();

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit showError();
        return;
    }

    QTextStream out(&file); //  áâà®©ª  â¥ªáâ®¢®£® ¯®â®ª 
    out.setEncoding(QStringConverter::Utf8); // “áâ ­®¢ª  UTF-8
    out.setGenerateByteOrderMark(true);      // BOM

    SQLite::Statement tasks = SQLite::Statement(this->db.db, "SELECT t.name, t.description, t.creation_time, b.name "
                                                             "FROM task AS t JOIN type AS b ON b.type_id = t.type_id WHERE t.board_id = " + std::to_string(boardId));


    out << "Task;Description;Creation Date;Task type\n";

    while (tasks.executeStep()) {
        out << QString::fromUtf8(tasks.getColumn(0).getString()) << ';' // task name
            << (tasks.getColumn(1).getString().empty() ? "" : QString::fromUtf8(tasks.getColumn(1).getString())) << ';' // task description
            << QString::fromUtf8(tasks.getColumn(2).getString()) << ';' // creation time
            << QString::fromUtf8(tasks.getColumn(3).getString()) << '\n'; // type name
    }

    emit exported();

    file.close();
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
