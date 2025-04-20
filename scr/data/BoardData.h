#ifndef BOARDDATA_H
#define BOARDDATA_H
#include <QAbstractListModel>
#include <vector>
#include <QUrl>

#include "scr/dto/GlobalVariables.h"
#include "scr/object/BoardObject.h"
#include "./scr/database/DataBase.h"


class BoardData : public QAbstractListModel {
    Q_OBJECT
private:
    std::vector<BoardObject*> m_data;
    DataBase db;
public:
    enum Roles {
        boardName = Qt::UserRole + 1,
        boardDescription,
        boardCreationTime,
        boardId
    };

    explicit BoardData(QObject* parent = nullptr) : QAbstractListModel(parent), db(Global::getDatabasePath()) {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void addBoards();

    Q_INVOKABLE void refreshModel();
    Q_INVOKABLE void deleteBoard(int boardId);
    Q_INVOKABLE void exportBoard(const QUrl url, int boardId);

signals:
    void modelUpdated();
    void showError(const QString &message);
};

#endif // BOARDDATA_H
