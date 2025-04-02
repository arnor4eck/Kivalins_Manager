#include "CreateBoard.h"
#include "GlobalVariables.h"
#include <QDebug>

CreateBoard::CreateBoard(QObject *parent) : BaseCreate(parent), db(Global::getDatabasePath()) {}

bool CreateBoard::saveData() {
    if(this->b_name.length() > 16) {
        emit showError("Название больше 16 символов");
        return false;
    }

    if(this->b_name.isEmpty()) {
        emit showError("Название не должно быть пустым");
        return false;
    }

    if(this->b_description.length() >= 64) {
        emit showError("Описание больше 64 символов");
        return false;
    }

    try{
        SQLite::Statement query(this->db.db, "INSERT INTO board (name, description) VALUES (?, ?)");

        query.bind(1, this->b_name.toStdString());
        if(this->b_description.isEmpty()){
            query.bind(2);
        }else{
            query.bind(2, this->b_description.toStdString());
        }

        query.exec();
    }catch(const std::exception &e){
        if(std::string(e.what()).find("UNIQUE") != std::string::npos && std::string(e.what()).find("board.name") != std::string::npos){
            emit showError("Название должно быть уникальным");
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
