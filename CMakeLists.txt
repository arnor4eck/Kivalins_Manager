cmake_minimum_required(VERSION 3.16)

project(Kivalins_Manager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Core)

# SQLite
add_subdirectory(SQLiteCpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SQLiteCpp/include)

qt_standard_project_setup()

set(SOURCES
    DataBase.cpp
    main.cpp
    BaseCreate.cpp
    CreateBoard.cpp
    GlobalVariables.cpp
    TaskData.cpp
    CreateTask.cpp
    BoardData.cpp
)

set(HEADERS
    GlobalVariables.h
    DataBase.h
    BaseCreate.h
    CreateBoard.h
    TaskData.h
    CreateTask.h
    BoardData.h
    BoardObject.h
    TaskObject.h
)

set(QML_FILES
    Main.qml
    StartPage.qml
    CustomButton.qml
    BoardsPage.qml
    SettingsPage.qml
    Navbar.qml
    ErrorWindow.qml
    SuccessWindow.qml
    CreateBoardWindow.qml
    CreateTaskWindow.qml
    CircularButton.qml
    BoardPage.qml
    TaskIcon.qml
    TaskIconDescriptionWindow.qml
    BoardIcon.qml
    BoardIconDescriptionWindow.qml
    StatisticsWindow.qml
)

qt_add_executable(appKivalins_Manager
    ${SOURCES}
    ${HEADERS}
)

qt_add_qml_module(appKivalins_Manager
    URI Kivalins_Manager
    VERSION 1.0
    QML_FILES ${QML_FILES}
    SOURCES ${HEADERS} ${SOURCES}
    QML_FILES TypesBoard.qml
    SOURCES TypeObject.h
    SOURCES TypeData.cpp
    SOURCES TypeData.h
    QML_FILES CreateTypeWindow.qml
    SOURCES CreateType.h
    SOURCES CreateType.cpp
    QML_FILES TypeIcon.qml
    QML_FILES UpdateTaskWindow.qml
    QML_FILES FilterTasksWindow.qml
    QML_FILES
)

target_link_libraries(appKivalins_Manager
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Qt6::Core
        SQLiteCpp
        sqlite3
)

include(GNUInstallDirs)
install(TARGETS appKivalins_Manager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(MINGW)
    add_compile_options(-std=c++17)
endif()
