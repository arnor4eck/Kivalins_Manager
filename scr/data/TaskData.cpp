#include "TaskData.h"

int TaskData::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_data.size();
}

QHash<int, QByteArray> TaskData::roleNames() const {
    return {
        {taskName, "name"}, // название
        {taskDescription, "description"}, // описание
        {taskCreationTime, "creationTime"}, // время создания
        {taskType, "type"}, // тип задачи
        {taskId, "id"} // ID
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
    SQLite::Statement tasks = SQLite::Statement(this->db.db, "SELECT t.task_id, t.name, t.description, b.name, t.creation_time "
                                     "FROM task AS t JOIN type AS b ON t.type_id = b.type_id WHERE t.board_id = " + std::to_string(boardId) +
                                    (type != 0 ? " AND t.type_id = " + std::to_string(type) : "")); // все задачи этой доски

    while(tasks.executeStep()){
        TaskObject* task = new TaskObject(tasks.getColumn(0).getInt(), // добавление в вектор
                QString::fromStdString(tasks.getColumn(1).getString()),
                (tasks.getColumn(2).getString().size() == 0 ? "Описание отсутствует" : QString::fromStdString(tasks.getColumn(2).getString())),
                QString::fromStdString(tasks.getColumn(3).getString()),
                QString::fromStdString(tasks.getColumn(4).getString()));
        this->m_data.emplace_back(task);
    }
}

bool TaskData::updateTask(int boardId, int taskId, QString name, QString description, int typeId){
    if(name.length() > 16) { // валидация названия
        emit showError("Название больше 16 символов");
        return false;
    }

    if(name.isEmpty()) { // валидация названия
        emit showError("Название не должно быть пустым");
        return false;
    }
    if(description.length() > 64){ // валдиация описания
        emit showError("Описание больше 64 символов");
        return false;
    }

    SQLite::Statement query(this->db.db, "UPDATE task SET name = ?, description = ?" + (typeId == 0 ? "" : std::string(", type_id = ?")) + " WHERE task_id = " + std::to_string(taskId));

    query.bind(1, name.toStdString());
    if(description.isEmpty()){
        query.bind(2);
    }else{
        query.bind(2, description.toStdString());
    }

    if(typeId != 0){
        query.bind(3, typeId);
    }

    query.exec();

    refreshModel(boardId);

    return true;
}

int TaskData::getCreatedCount(int boardId){
    SQLite::Statement allTasks = this->db.getData("task", "COUNT(*)", "board_id = " + std::to_string(boardId));
    if(allTasks.executeStep()){}

    return allTasks.getColumn(0).getInt();
}

int TaskData::getDoneCount(int boardId){
    SQLite::Statement doneTasks = this->db.getData("task", "COUNT(*)", "type_id = 2 AND board_id = " + std::to_string(boardId));
    if(doneTasks.executeStep()){}

    return doneTasks.getColumn(0).getInt();
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
