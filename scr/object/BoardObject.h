#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H
#include <QObject>
#include <QString>

class BoardObject : public QObject {
    Q_OBJECT
public:
    BoardObject(int id, QString name, QString description, QString creationTime, QObject* parent = nullptr)
        : QObject(parent), m_id(id), m_name(name), m_description(description), m_creationTime(creationTime) {}

    int id() const { return m_id; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    QString creationTime() const { return m_creationTime; }

private:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_creationTime;
};

#endif // BOARDOBJECT_H
