#include "BoardData.h"

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
