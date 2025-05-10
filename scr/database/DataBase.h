#ifndef DATABASE_H
#define DATABASE_H
#include "SQLiteCpp/include/SQLiteCpp/SQLiteCpp.h"

class DataBase{
private:
    std::string path;
public:
    SQLite::Database db;
    DataBase(const std::string _path): path(_path), db(_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
        try{
            this->db = SQLite::Database(_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        } catch (const std::exception& e) {
            throw std::runtime_error("Connection to " + path + " was failed: " + e.what());
        }
    }

    const std::string getPath() { return this->path; }

    void createTable(const std::string &params);
    void addData(const std::string &table_name, const std::string columns, const std::string &data);
    SQLite::Statement getData(const std::string &table_name, const std::string columns, const std::string filters = "");
    void deleteData(const std::string &table_name, const std::string filters);
    void updateData(const std::string &table_name, const std::string param, const std::string new_data, const std::string filters);
    void exec(const std::string &query);
};

#endif // DATABASE_H
