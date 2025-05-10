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
    enum Roles { // для переадресации из qml
        boardName = Qt::UserRole + 1,
        boardDescription,
        boardCreationTime,
        boardId
    };

    explicit BoardData(QObject* parent = nullptr) : QAbstractListModel(parent), db(Global::getDatabasePath()) {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override; // для обращения из qml
    QVariant data(const QModelIndex& index, int role) const override; // возвращает соответствующий вариант из обращения
    void addBoards();

    Q_INVOKABLE void refreshModel(); // обновление модели
    Q_INVOKABLE void deleteBoard(int boardId); // удаление доски
    Q_INVOKABLE void exportBoard(const QUrl url, int boardId); // экспорт задач

    ~BoardData(){
        for(auto obj : this->m_data)
            delete obj;
    }

signals:
    void showError(); // сигнал об ошибке
    void exported(); // сигнал об успешном экспорте
};

#endif // BOARDDATA_H
