#ifndef TASKDATA_H
#define TASKDATA_H
#include <QAbstractListModel>
#include <vector>

#include "scr/dto/GlobalVariables.h"
#include "scr/object/TaskObject.h"
#include "./scr/database/DataBase.h"


class TaskData : public QAbstractListModel {
    Q_OBJECT
private:
    std::vector<TaskObject*> m_data;
    DataBase db;
public:
    enum Roles { // для переадресации из qml
        taskName = Qt::UserRole + 1,
        taskDescription,
        taskType,
        taskCreationTime,
        taskId,
    };

    explicit TaskData(QObject* parent = nullptr) : QAbstractListModel(parent), db(Global::getDatabasePath()) {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override; // для обращения из qml
    QVariant data(const QModelIndex& index, int role) const override; // возвращает соответствующий вариант из обращения

    Q_INVOKABLE void loadTasks(int boardId, int type = 0); // загрузка задач
    Q_INVOKABLE bool updateTask(int boardId, int taskId, QString name, QString description, int typeId); // обновление задачи
    Q_INVOKABLE void refreshModel(int boardId, int type = 0); // обновление модели
    Q_INVOKABLE int getCreatedCount(int boardId); // количество созданных задач
    Q_INVOKABLE int getDoneCount(int boardId); // количество сделанных задач

    ~TaskData(){
        for(auto obj : this->m_data)
            delete obj;
    }
signals:
    void showError(const QString &message); // сигнал ошибки
};

#endif // TASKDATA_H
