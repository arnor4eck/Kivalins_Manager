#ifndef DATABASE_H
#define DATABASE_H
#include "SQLiteCpp/include/SQLiteCpp/SQLiteCpp.h"

class DataBase{
private:
    std::string path; // путь к бд
public:
    SQLite::Database db;
    DataBase(const std::string _path): path(_path), db(_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
        try{
            this->db = SQLite::Database(_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE); // создание/открытие базы данных
        } catch (const std::exception& e) {
            throw std::runtime_error("Connection to " + path + " was failed: " + e.what());
        }
    }

    const std::string getPath() { return this->path; }

    void createTable(const std::string &params); // создание таблицы
    void addData(const std::string &table_name, const std::string columns, const std::string &data); // добавление данных в таблицу
    SQLite::Statement getData(const std::string &table_name, const std::string columns, const std::string filters = ""); // получение данных из таблиы
    void deleteData(const std::string &table_name, const std::string filters); // удаление данных из таблицы
};

#endif // DATABASE_H
