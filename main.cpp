#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <string>
#include <filesystem>

#include "scr/creation/CreateBoard.h"
#include "scr/creation/CreateTask.h"
#include "scr/dto/GlobalVariables.h"
#include "scr/object/BoardObject.h"
#include "scr/data/BoardData.h"
#include "scr/object/TaskObject.h"
#include "scr/data/TaskData.h"
#include "scr/data/TypeData.h"
#include "scr/creation/CreateType.h"

void prepareGlobalVariables(char *argv[]){
    Global::setProjectName("Kivalins_Manager"); // глабальная переменная названия проекта

    std::filesystem::path exePath = argv[0];
    std::string thisPath = exePath.string();
    thisPath.erase(thisPath.begin() + thisPath.find(Global::getProjectName()), thisPath.end());

    Global::setProjectPath(thisPath + Global::getProjectName()); // путь к проекту
    Global::setDatabasePath(Global::getProjectPath() + "\\manager.db"); // путь к базе данных
}

void prepareDB(){
    DataBase db(Global::getDatabasePath());
    db.db.exec("PRAGMA foreign_keys = ON;"); // разрешение связей
    db.createTable("board (board_id INTEGER PRIMARY KEY AUTOINCREMENT, name varchar(16) UNIQUE NOT NULL, " // создание таблицы досок
                   "description varchar(64), creation_time TIMESTAMP DEFAULT (datetime('now', 'localtime')))");

    if(!(db.getData("board", "*", "board_id = 1").executeStep()))
        db.addData("board", "name, description", "'base_board', 'base_board'"); // при первом запуске - создание нулевой таблицы, к которой прикреплены основные типы

    db.createTable("type(" // создание таблицы типов
                   "type_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "board_id INTEGER NOT NULL, "
                   "name varchar(16) NOT NULL,"
                   "FOREIGN KEY (board_id) REFERENCES board(board_id) ON DELETE CASCADE)");

    if(!(db.getData("type", "*", "type_id = 1").executeStep())) // при первом запуске - создание базовых типов задач
        db.addData("type", "name, board_id", "'В работе', 1");
    if(!(db.getData("type", "*", "type_id = 2").executeStep()))
        db.addData("type", "name, board_id", "'Завершено', 1");

    db.createTable("task(task_id INTEGER PRIMARY KEY AUTOINCREMENT, " // создание таблицы задач
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
    // регистрация соответствующих моделей
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

    // регистрация соответствующих моделей
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
