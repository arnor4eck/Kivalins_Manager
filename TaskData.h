#ifndef TASKDATA_H
#define TASKDATA_H
#include <QAbstractListModel>
#include <vector>
#include "GlobalVariables.h"
#include "TaskObject.h"
#include "DataBase.h"


class TaskData : public QAbstractListModel {
    Q_OBJECT
private:
    std::vector<TaskObject*> m_data;
    DataBase db;
public:
    enum Roles {
        taskName = Qt::UserRole + 1,
        taskDescription,
        taskType,
        taskCreationTime,
        taskId,
    };

    explicit TaskData(QObject* parent = nullptr) : QAbstractListModel(parent), db(Global::getDatabasePath()) {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

    Q_INVOKABLE void loadTasks(int boardId, int type = 0);
    Q_INVOKABLE bool updateTask(int boardId, int taskId, QString name, QString description);
    Q_INVOKABLE void refreshModel(int boardId, int type = 0);

signals:
    void showError(const QString &message);
};

#endif // TASKDATA_H
