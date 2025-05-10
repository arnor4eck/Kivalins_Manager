#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <string>

namespace Global { // глабоальные переменные
    void setDatabasePath(const std::string& path);
    const std::string& getDatabasePath(); // путь в базе данных
    void setProjectName(const std::string& name);
    const std::string& getProjectName(); // название проекта
    void setProjectPath(const std::string& path);
    const std::string& getProjectPath(); // путь к проекту
}

#endif // GLOBAL_VARIABLES_H
