#ifndef CREATEBOARD_H
#define CREATEBOARD_H
#include <QString>

#include "BaseCreate.h"
#include "./scr/database/DataBase.h"


class CreateBoard : public BaseCreate {
    Q_OBJECT
private:
    QString b_name;
    QString b_description;
    DataBase db;

public:
    explicit CreateBoard(QObject *parent = nullptr);
    Q_INVOKABLE bool saveData() override;

    Q_INVOKABLE void setName(const QString &name);
    Q_INVOKABLE void setDescription(const QString &description);

    QString name() const;
    QString description() const;

signals:
    void boardAdded();
    void showError(const QString &message);
};

#endif // CREATEBOARD_H
