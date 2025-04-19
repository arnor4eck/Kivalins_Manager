#include "CreateType.h"
#include "scr/dto/GlobalVariables.h"
#include <QDebug>

CreateType::CreateType(QObject *parent) : BaseCreate(parent), db(Global::getDatabasePath()) {}

bool CreateType::saveData() {
    if(this->b_name.length() > 16) {
        emit showError("Название больше 16 символов");
        return false;
    }

    if(this->b_name.isEmpty()) {
        emit showError("Название не должно быть пустым");
        return false;
    }

    SQLite::Statement query(this->db.db, "INSERT INTO type (name, board_id) VALUES (?, ?)");

    query.bind(1, this->b_name.toStdString());
    query.bind(2, this->b_boardId);

    query.exec();


    emit typeAdded();
    return true;
}

void CreateType::setName(const QString &name) {
    this->b_name = name;
}

void CreateType::setBoardId(const int &boardId) {
    this->b_boardId = boardId;
}

QString CreateType::name() const {
    return this->b_name;
}

int CreateType::boardId() const {
    return this->b_boardId;
}
