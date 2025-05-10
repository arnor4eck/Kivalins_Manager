#include "CreateBoard.h"
#include "scr/dto/GlobalVariables.h"
#include <QDebug>

CreateBoard::CreateBoard(QObject *parent) : BaseCreate(parent), db(Global::getDatabasePath()) {}

bool CreateBoard::saveData() {
    if(this->b_name.length() > 16) { // валидация названия
        emit showError("Название больше 16 символов");
        return false;
    }

    if(this->b_name.isEmpty()) { // валидация названия
        emit showError("Название не должно быть пустым");
        return false;
    }

    if(this->b_description.length() >= 64) { // валидация описания
        emit showError("Описание больше 64 символов");
        return false;
    }

    try{
        SQLite::Statement query(this->db.db, "INSERT INTO board (name, description) VALUES (?, ?)"); // создание записи

        query.bind(1, this->b_name.toStdString());
        if(this->b_description.isEmpty()){
            query.bind(2); // если описания нет - вставляет NULL
        }else{
            query.bind(2, this->b_description.toStdString());
        }

        query.exec();
    }catch(const std::exception &e){
        if(std::string(e.what()).find("UNIQUE") != std::string::npos && std::string(e.what()).find("board.name") != std::string::npos){
            emit showError("Название должно быть уникальным"); // проверка на уникальность названия
            return false;
        }
    }

    emit boardAdded();
    return true;
}

void CreateBoard::setName(const QString &name) {
    this->b_name = name;
}

void CreateBoard::setDescription(const QString &description) {
    this->b_description = description;
}

QString CreateBoard::name() const {
    return this->b_name;
}

QString CreateBoard::description() const {
    return this->b_description.isEmpty() ? "" : this->b_description;
}
