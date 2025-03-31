#ifndef BOARDDATA_H
#define BOARDDATA_H
#include <QAbstractListModel>
#include <vector>
#include "GlobalVariables.h"
#include "BoardObject.h"
#include "DataBase.h"


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

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_data.size();
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            {boardName, "name"},
            {boardDescription, "description"},
            {boardCreationTime, "creationTime"},
            {boardId, "id"}
        };
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (!index.isValid()) return QVariant();

        const auto& item = m_data[index.row()];
        switch (role) {
            case boardName:  return item->name();
            case boardDescription: return item->description();
            case boardCreationTime: return item->creationTime();
            case boardId: return item->id();
            default:        return QVariant();
        }
    }

    void addBoards() {
        SQLite::Statement boards = db.getData("board", "*");

        while(boards.executeStep()){
            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            int id = boards.getColumn(0);

            BoardObject* board = new BoardObject(id,
                                                QString::fromStdString(boards.getColumn(1).getString()),
                                                 (boards.getColumn(2).getString().size() == 0 ? "Описание отсутствует" : QString::fromStdString(boards.getColumn(2).getString())),
                                                 QString::fromStdString(boards.getColumn(3).getString()));
            this->m_data.emplace_back(board);

            endInsertRows();
        }
    }

    Q_INVOKABLE void refreshModel(){
        beginResetModel();  // Сообщаем QML о полном обновлении

        // Очищаем старые данные
        for (auto item : m_data) {
            delete item;
        }
        m_data.clear();

        // Загружаем данные заново
        addBoards();

        endResetModel();
        emit modelUpdated();  // Отправляем сигнал
    }

signals:
    void modelUpdated();  // Сигнал об обновлении
};

#endif // BOARDDATA_H
