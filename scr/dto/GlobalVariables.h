#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <string>

namespace Global {
    void setDatabasePath(const std::string& path);
    const std::string& getDatabasePath();
    void setProjectName(const std::string& name);
    const std::string& getProjectName();
    void setProjectPath(const std::string& path);
    const std::string& getProjectPath();
}

#endif // GLOBAL_VARIABLES_H
