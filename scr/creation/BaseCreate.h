#ifndef BASECREATE_H
#define BASECREATE_H

#include <QObject>

class BaseCreate : public QObject { // класс создания объекта
    Q_OBJECT
public:
    explicit BaseCreate(QObject *parent = nullptr);
    Q_INVOKABLE virtual bool saveData() = 0; // создание объекта

    virtual ~BaseCreate() = default;
};

#endif // BASECREATE_H
