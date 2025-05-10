#include "DataBase.h"

void DataBase::createTable(const std::string &params){
    try{
        this->db.exec("CREATE TABLE IF NOT EXISTS " + params);
    }catch(const std::exception &e){
        throw std::runtime_error("Creation table in " + this->getPath() + " wasn`t done: " + e.what());
    }
}

void DataBase::addData(const std::string &table_name, const std::string columns, const std::string &data){
    try{
        std::string query = "INSERT INTO " + table_name + "(" + columns + ")\n" + "VALUES\n" + "(" + data + ")";

        this->db.exec(query.c_str());
    }catch(const std::exception &e){
        throw std::runtime_error("Adding data to table " + table_name + " in " + this->getPath() + " wasn`t done: " + e.what());
    }
}

SQLite::Statement DataBase::getData(const std::string &table_name, const std::string columns, const std::string filters){
    std::string query = "SELECT " + columns + " FROM " + table_name + " ";
    if(!filters.empty()) query += "WHERE " + filters;

    try{
        return SQLite::Statement(this->db, query);
    }catch(const std::exception &e){
        throw std::runtime_error("Getting data from table " + table_name + " in " + this->getPath() + " wasn`t done: " + e.what());
    }
}

void DataBase::deleteData(const std::string &table_name, const std::string filters){
    std::string query = "DELETE FROM " + table_name + " WHERE " + filters;
    try{
        this->db.exec(query);
    }catch(const std::exception &e){
        throw std::runtime_error("Deleting data from table " + table_name + " in " + this->getPath() + " wasn`t done: " + e.what());
    }
}


