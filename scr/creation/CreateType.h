#ifndef CREATETYPE_H
#define CREATETYPE_H
#include <QString>

#include "BaseCreate.h"
#include "./scr/database/DataBase.h"


class CreateType : public BaseCreate { // создание типа
    Q_OBJECT
private:
    QString b_name;
    int b_boardId;
    DataBase db;

public:
    explicit CreateType(QObject *parent = nullptr);
    Q_INVOKABLE bool saveData() override; // создание объекта

    Q_INVOKABLE void setName(const QString &name); // установка имени
    Q_INVOKABLE void setBoardId(const int &boardId); // установка ID

    QString name() const;
    int boardId() const;

signals:
    void showError(const QString &message); // сигнал ошибки
};

#endif // CREATETYPE_H
