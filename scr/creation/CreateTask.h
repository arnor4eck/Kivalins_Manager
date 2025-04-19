#ifndef CREATETASK_H
#define CREATETASK_H
#include <QString>

#include "BaseCreate.h"
#include "./scr/database/DataBase.h"

class CreateTask : public BaseCreate {
    Q_OBJECT
private:
    QString b_name;
    QString b_description;
    int b_boardId;
    DataBase db;

public:
    explicit CreateTask(QObject *parent = nullptr);
    Q_INVOKABLE bool saveData() override;

    Q_INVOKABLE void setName(const QString &name);
    Q_INVOKABLE void setDescription(const QString &description);
    Q_INVOKABLE void setBoardId(const int &boardId);

    QString name() const;
    QString description() const;
    int boardId() const;

signals:
    void taskAdded();
    void showError(const QString &message);
};

#endif // CREATETASK_H
