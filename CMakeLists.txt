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
    scr/database/DataBase.cpp
    main.cpp
    scr/creation/BaseCreate.cpp
    scr/creation/CreateBoard.cpp
    scr/dto/GlobalVariables.cpp
    scr/data/TaskData.cpp
    scr/creation/CreateTask.cpp
    scr/data/BoardData.cpp
    scr/data/TypeData.cpp
    scr/creation/CreateType.cpp
)

set(HEADERS
    scr/dto/GlobalVariables.h
    scr/database/DataBase.h
    scr/creation/BaseCreate.h
    scr/creation/CreateBoard.h
    scr/data/TaskData.h
    scr/creation/CreateTask.h
    scr/data/BoardData.h
    scr/object/BoardObject.h
    scr/object/TaskObject.h
    scr/object/TypeObject.h
    scr/data/TypeData.h
    scr/creation/CreateType.h
)

set(QML_FILES
    Main.qml
    StartPage.qml
    dto/CustomButton.qml
    board/BoardsPage.qml
    dto/SettingsPage.qml
    dto/Navbar.qml
    dto/ErrorWindow.qml
    dto/SuccessWindow.qml
    board/CreateBoardWindow.qml
    task/CreateTaskWindow.qml
    dto/CircularButton.qml
    board/BoardPage.qml
    task/TaskIcon.qml
    task/TaskIconDescriptionWindow.qml
    board/BoardIcon.qml
    board/BoardIconDescriptionWindow.qml
    dto/StatisticsWindow.qml
    type/TypesBoard.qml
    type/CreateTypeWindow.qml
    type/TypeIcon.qml
    task/UpdateTaskWindow.qml
    task/FilterTasksWindow.qml
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
