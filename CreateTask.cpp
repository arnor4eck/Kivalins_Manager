#include "CreateTask.h"
#include "GlobalVariables.h"
#include <QDebug>

CreateTask::CreateTask(QObject *parent) : BaseCreate(parent), db(Global::getDatabasePath()) {}

bool CreateTask::saveData() {
    if(this->b_name.length() > 16) {
        emit showError("Название больше 16 символов");
        return false;
    }

    if(this->b_name.isEmpty()) {
        emit showError("Название не должно быть пустым");
        return false;
    }
    if(this->b_description.length() > 64){
        emit showError("Описание больше 64 символов");
        return false;
    }

    SQLite::Statement query(this->db.db, "INSERT INTO task (name, description, board_id) VALUES (?, ?, ?)");

    query.bind(1, this->b_name.toStdString());
    if(this->b_description.isEmpty()){
        query.bind(2);
    }else{
        query.bind(2, this->b_description.toStdString());
    }
    query.bind(3, this->b_boardId);

    query.exec();


    emit taskAdded();
    return true;
}

void CreateTask::setName(const QString &name) {
    this->b_name = name;
}

void CreateTask::setBoardId(const int &boardId) {
    this->b_boardId = boardId;
}

void CreateTask::setDescription(const QString &description) {
    this->b_description = description;
}

QString CreateTask::name() const {
    return this->b_name;
}

QString CreateTask::description() const {
    return this->b_description.isEmpty() ? "" : this->b_description;
}

int CreateTask::boardId() const {
    return this->b_boardId;
}
