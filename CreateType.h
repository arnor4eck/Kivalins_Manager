#ifndef CREATETYPE_H
#define CREATETYPE_H
#include <QString>

#include "BaseCreate.h"
#include "DataBase.h"


class CreateType : public BaseCreate {
    Q_OBJECT
private:
    QString b_name;
    int b_boardId;
    DataBase db;

public:
    explicit CreateType(QObject *parent = nullptr);
    Q_INVOKABLE bool saveData() override;

    Q_INVOKABLE void setName(const QString &name);
    Q_INVOKABLE void setBoardId(const int &boardId);

    QString name() const;
    int boardId() const;

signals:
    void typeAdded();
    void showError(const QString &message);
};

#endif // CREATETYPE_H
