#include "TypeData.h"

int TypeData::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_data.size();
}

QHash<int, QByteArray> TypeData::roleNames() const {
    return {
        {typeName, "name"}, // название
        {typeId, "id"} // ID
    };
}

QVariant TypeData::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    const auto& item = m_data[index.row()];
    switch (role) {
    case typeName:  return item->name();
    case typeId: return item->id();
    default:        return QVariant();
    }
}

void TypeData::loadTypes(int boardId) {
    SQLite::Statement types = db.getData("type", "*", // загрузка всех типов этой доски
                                         "board_id = 1 OR board_id =" + std::to_string(boardId));

    while(types.executeStep()){
        int id = types.getColumn(0);

        TypeObject* task = new TypeObject(id, // добавление в вектор всех типов
                                          QString::fromStdString(types.getColumn(2).getString()));
        this->m_data.emplace_back(task);
    }
}


void TypeData::deleteType(int typeId, int boardId){
    this->db.db.exec("UPDATE task SET type_id = 1 WHERE type_id = " + std::to_string(typeId)); // где был этот тип - ставится "В работе"
    this->db.deleteData("type", "type_id = " + std::to_string(typeId)); // удаление типа

    refreshModel(boardId);
}

void TypeData::refreshModel(int boardId){
    beginResetModel();

    for (auto item : m_data) {
        delete item;
    }
    m_data.clear();

    loadTypes(boardId);
    endResetModel();
}
