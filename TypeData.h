#ifndef TYPEDATA_H
#define TYPEDATA_H
#include <QAbstractListModel>
#include <vector>
#include "GlobalVariables.h"
#include "TypeObject.h"
#include "DataBase.h"


class TypeData : public QAbstractListModel {
    Q_OBJECT
private:
    std::vector<TypeObject*> m_data;
    DataBase db;
public:
    enum Roles {
        typeName = Qt::UserRole + 1,
        typeId,
    };

    explicit TypeData(QObject* parent = nullptr) : QAbstractListModel(parent), db(Global::getDatabasePath()) {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

    Q_INVOKABLE void loadTypes(int boardId);
    Q_INVOKABLE void deleteType(int typeId, int boardId);
    Q_INVOKABLE void refreshModel(int boardId);

};

#endif // TYPEDATA_H
