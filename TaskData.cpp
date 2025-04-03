#include "TaskData.h"

int TaskData::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_data.size();
}

QHash<int, QByteArray> TaskData::roleNames() const {
    return {
        {taskName, "name"},
        {taskDescription, "description"},
        {taskCreationTime, "creationTime"},
        {taskType, "type"},
        {taskId, "id"}
    };
}

QVariant TaskData::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    const auto& item = m_data[index.row()];
    switch (role) {
    case taskName:  return item->name();
    case taskDescription: return item->description();
    case taskType: return item->type();
    case taskCreationTime: return item->creationTime();
    case taskId: return item->id();
    default:        return QVariant();
    }
}

void TaskData::loadTasks(int boardId, int type) {
    SQLite::Statement tasks = db.getData("task", "*",
                                          "board_id = " + std::to_string(boardId) +
                                              (type != 0 ? " AND type_id = " + std::to_string(type) : ""));

    while(tasks.executeStep()){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        int id = tasks.getColumn(0);
        SQLite::Statement getType = db.getData("type", "*", "type_id = " + tasks.getColumn(2).getString());

        std::string typeName = "";
        if(getType.executeStep()){
            typeName = getType.getColumn(2).getString();
        }

        TaskObject* task = new TaskObject(id,
                QString::fromStdString(tasks.getColumn(3).getString()),
                (tasks.getColumn(4).getString().size() == 0 ? "Описание отсутствует" : QString::fromStdString(tasks.getColumn(4).getString())),
                QString::fromStdString(typeName),
                QString::fromStdString(tasks.getColumn(5).getString()));
        this->m_data.emplace_back(task);

        endInsertRows();
    }
}

bool TaskData::updateTask(int boardId, int taskId, QString name, QString description){
    if(name.length() > 16) {
        emit showError("Название больше 16 символов");
        return false;
    }

    if(name.isEmpty()) {
        emit showError("Название не должно быть пустым");
        return false;
    }
    if(description.length() > 64){
        emit showError("Описание больше 64 символов");
        return false;
    }

    SQLite::Statement query(this->db.db, "UPDATE task SET name = ?, description = ? WHERE task_id = " + std::to_string(taskId));

    query.bind(1, name.toStdString());
    if(description.isEmpty()){
        query.bind(2);
    }else{
        query.bind(2, description.toStdString());
    }

    query.exec();

    refreshModel(boardId);

    return true;
}

void TaskData::refreshModel(int boardId, int type){
    beginResetModel();

    for (auto item : m_data) {
        delete item;
    }
    m_data.clear();

    loadTasks(boardId, type);

    endResetModel();
}
