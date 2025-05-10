#ifndef TYPEDATA_H
#define TYPEDATA_H
#include <QAbstractListModel>
#include <vector>

#include "scr/dto/GlobalVariables.h"
#include "scr/object/TypeObject.h"
#include "./scr/database/DataBase.h"


class TypeData : public QAbstractListModel { // массив объектов типов
    Q_OBJECT
private:
    std::vector<TypeObject*> m_data;
    DataBase db;
public:
    enum Roles { // для переадресации из qml
        typeName = Qt::UserRole + 1,
        typeId,
    };

    explicit TypeData(QObject* parent = nullptr) : QAbstractListModel(parent), db(Global::getDatabasePath()) {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override; // для обращения из qml
    QVariant data(const QModelIndex& index, int role) const override; // возвращает соответствующий вариант из обращения

    Q_INVOKABLE void loadTypes(int boardId); // загрузка типов задач
    Q_INVOKABLE void deleteType(int typeId, int boardId); // удаление типа
    Q_INVOKABLE void refreshModel(int boardId); // обновление модели

    ~TypeData(){ // деструктор
        for(auto obj : this->m_data)
            delete obj;
    }
};

#endif // TYPEDATA_H
