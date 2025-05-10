#ifndef TASKOBJECT_H
#define TASKOBJECT_H
#include <QObject>
#include <QString>

class TaskObject : public QObject { // объект задачи
    Q_OBJECT
public:
    TaskObject(int id, QString name, QString description, QString type, QString creationTime, QObject* parent = nullptr)
        : QObject(parent), m_id(id), m_name(name), m_type(type), m_description(description), m_creationTime(creationTime) {}

    int id() const { return m_id; }
    QString name() const { return m_name; }
    QString type() const { return m_type; }
    QString description() const { return m_description; }
    QString creationTime() const { return m_creationTime; }

private:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_type;
    QString m_creationTime;
};

#endif // TASKOBJECT_H
