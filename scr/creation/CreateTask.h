#ifndef CREATETASK_H
#define CREATETASK_H
#include <QString>

#include "BaseCreate.h"
#include "./scr/database/DataBase.h"

class CreateTask : public BaseCreate { // создание задачи
    Q_OBJECT
private:
    QString b_name;
    QString b_description;
    int b_boardId;
    DataBase db;

public:
    explicit CreateTask(QObject *parent = nullptr);
    Q_INVOKABLE bool saveData() override; // создание объекта

    Q_INVOKABLE void setName(const QString &name); // установка имени
    Q_INVOKABLE void setDescription(const QString &description); // установка описания
    Q_INVOKABLE void setBoardId(const int &boardId); // установка ID

    QString name() const;
    QString description() const;
    int boardId() const;

signals:
    void showError(const QString &message); // сигнал об ошибке
};

#endif // CREATETASK_H
