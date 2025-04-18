#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <string>
#include <filesystem>

#include "CreateBoard.h"
#include "CreateTask.h"
#include "GlobalVariables.h"
#include "BoardObject.h"
#include "BoardData.h"
#include "TaskObject.h"
#include "TaskData.h"
#include "TypeData.h"
#include "CreateType.h"

void prepareGlobalVariables(char *argv[]){
    Global::setProjectName("Kivalins_Manager");

    std::filesystem::path exePath = argv[0];
    std::string thisPath = exePath.string();
    thisPath.erase(thisPath.begin() + thisPath.find(Global::getProjectName()), thisPath.end());

    Global::setProjectPath(thisPath + Global::getProjectName());
    Global::setDatabasePath(Global::getProjectPath() + "\\manager.db");
}

void prepareDB(){
    DataBase db(Global::getDatabasePath());
    db.exec("PRAGMA foreign_keys = ON;");
    db.createTable("board (board_id INTEGER PRIMARY KEY AUTOINCREMENT, name varchar(16) UNIQUE NOT NULL, "
                   "description varchar(64), creation_time TIMESTAMP DEFAULT (datetime('now', 'localtime')))");

    if(!(db.getData("board", "*", "board_id = 1").executeStep()))
        db.addData("board", "name, description", "'base_board', 'base_board'");

    db.createTable("type("
                   "type_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "board_id INTEGER NOT NULL, "
                   "name varchar(16) NOT NULL,"
                   "FOREIGN KEY (board_id) REFERENCES board(board_id) ON DELETE CASCADE)");

    if(!(db.getData("type", "*", "type_id = 1").executeStep()))
        db.addData("type", "name, board_id", "'В работе', 1");
    if(!(db.getData("type", "*", "type_id = 2").executeStep()))
        db.addData("type", "name, board_id", "'Завершено', 1");

    db.createTable("task(task_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "board_id INTEGER NOT NULL, "
                   "type_id INTEGER NOT NULL DEFAULT 1,"
                   "name varchar(16) NOT NULL,"
                   "description varchar(64), "
                   "creation_time TIMESTAMP DEFAULT (datetime('now', 'localtime')),"
                   "FOREIGN KEY (board_id) REFERENCES board(board_id) ON DELETE CASCADE,"
                   "FOREIGN KEY (type_id) REFERENCES type(type_id) ON DELETE SET DEFAULT)");
}

int main(int argc, char *argv[]){
    QGuiApplication app(argc, argv);

    prepareGlobalVariables(argv);
    prepareDB();

    CreateBoard createBoardObject;
    CreateTask createTaskObject;
    CreateType createTypeObject;
    qmlRegisterType<BoardData>(Global::getProjectName().c_str(), 1, 0, "BoardData");
    qmlRegisterType<BoardObject>(Global::getProjectName().c_str(), 1, 0, "BoardObject");
    qmlRegisterType<TaskData>(Global::getProjectName().c_str(), 1, 0, "TaskData");
    qmlRegisterType<TaskObject>(Global::getProjectName().c_str(), 1, 0, "TaskObject");
    qmlRegisterType<TypeData>(Global::getProjectName().c_str(), 1, 0, "TypeData");
    qmlRegisterType<TypeObject>(Global::getProjectName().c_str(), 1, 0, "TypeObject");


    QQmlApplicationEngine engine;

    BoardData* model = new BoardData(&engine);
    TaskData* taskModel = new TaskData(&engine);
    TypeData* typeModel = new TypeData(&engine);
    model->addBoards();

    QObject::connect(&createBoardObject, &CreateBoard::boardAdded,
                     model, &BoardData::refreshModel);

    engine.rootContext()->setContextProperty("createBoardObject", &createBoardObject);
    engine.rootContext()->setContextProperty("createTaskObject", &createTaskObject);
    engine.rootContext()->setContextProperty("createTypeObject", &createTypeObject);
    engine.rootContext()->setContextProperty("taskModel", taskModel);
    engine.rootContext()->setContextProperty("boardModel", model);
    engine.rootContext()->setContextProperty("typeModel", typeModel);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Kivalins_Manager", "Main");


    return app.exec();
}
