#include "GlobalVariables.h"

namespace {
    std::string databasePath;
    std::string projectName;
    std::string projectPath;
}

namespace Global {
    void setProjectPath(const std::string& path){
        projectPath = path;
    }

    const std::string& getProjectPath(){
        return projectPath;
    }

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
