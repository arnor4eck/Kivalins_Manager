#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "CreateBoard.h"
#include "GlobalVariables.h"
#include "BoardObject.h"
#include "BoardData.h"
#include <string>
#include <QQmlContext>

int main(int argc, char *argv[]){
    QGuiApplication app(argc, argv);
    Global::setProjectName("testqtstrat");

    std::filesystem::path exePath = argv[0];

    std::string thisPath = exePath.string();
    thisPath.erase(thisPath.begin() + thisPath.find(Global::getProjectName()), thisPath.end());
    Global::setDatabasePath(thisPath + Global::getProjectName() + "\\manager.db");

    CreateBoard board;
    qmlRegisterType<BoardData>("testqtstrat", 1, 0, "BoardData");
    qmlRegisterType<BoardObject>("testqtstrat", 1, 0, "BoardObject");

    QQmlApplicationEngine engine;

    BoardData* model = new BoardData(&engine);
    model->addBoards();

    QObject::connect(&board, &CreateBoard::boardAdded,
                     model, &BoardData::refreshModel);
    engine.rootContext()->setContextProperty("board", &board);
    engine.rootContext()->setContextProperty("boardModel", model);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("testqtstrat", "Main");


    return app.exec();
}
