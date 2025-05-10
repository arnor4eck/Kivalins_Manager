#ifndef CREATEBOARD_H
#define CREATEBOARD_H
#include <QString>

#include "BaseCreate.h"
#include "./scr/database/DataBase.h"


class CreateBoard : public BaseCreate { // создание доски
    Q_OBJECT
private:
    QString b_name;
    QString b_description;
    DataBase db; // база данных

public:
    explicit CreateBoard(QObject *parent = nullptr);
    Q_INVOKABLE bool saveData() override;

    Q_INVOKABLE void setName(const QString &name); // установка название
    Q_INVOKABLE void setDescription(const QString &description); // установка описания

    QString name() const;
    QString description() const;

signals:
    void boardAdded(); // сигнал создания доски
    void showError(const QString &message); // сигнал ошибки
};

#endif // CREATEBOARD_H
