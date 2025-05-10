#ifndef TYPEOBJECT_H
#define TYPEOBJECT_H
#include <QObject>
#include <QString>

class TypeObject : public QObject { // объект типа задачи
    Q_OBJECT
public:
    TypeObject(int id, QString name, QObject* parent = nullptr)
        : QObject(parent), m_id(id), m_name(name) {}

    int id() const { return m_id; }
    QString name() const { return m_name; }

private:
    int m_id;
    QString m_name;
};

#endif // TYPEOBJECT_H
