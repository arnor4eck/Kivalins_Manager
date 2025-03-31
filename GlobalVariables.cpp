#include "GlobalVariables.h"
#include <filesystem>

namespace {
    std::string databasePath;
    std::string projectName;
}

namespace Global {
    void setDatabasePath(const std::string& path) {
        databasePath = path;
    }

    const std::string& getDatabasePath() {
        return databasePath;
    }

    void setProjectName(const std::string& name){
        projectName = name;
    }
    const std::string& getProjectName(){
        return projectName;
    }
}
