cmake_minimum_required(VERSION 3.16)

project(testqtstrat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Поиск Qt6 компонентов
find_package(Qt6 REQUIRED COMPONENTS Quick Qml Core)

# SQLite
add_subdirectory(SQLiteCpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SQLiteCpp/include)

qt_standard_project_setup()

# Список исходных файлов
set(SOURCES
    DataBase.cpp
    main.cpp
    BaseCreate.cpp
    CreateBoard.cpp
    GlobalVariables.cpp
)

# Список заголовочных файлов
set(HEADERS
    GlobalVariables.h
    DataBase.h
    BaseCreate.h
    CreateBoard.h
)

# Список QML-файлов (все файлы в одном списке)
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
)

# Создание исполняемого файла
qt_add_executable(apptestqtstrat
    ${SOURCES}
    ${HEADERS}
)

# Добавление QML модуля (правильный формат)
qt_add_qml_module(apptestqtstrat
    URI testqtstrat
    VERSION 1.0
    QML_FILES ${QML_FILES}
    SOURCES ${HEADERS} ${SOURCES}
    QML_FILES BoardIcon.qml
    QML_FILES BoardIconDescriptionWindow.qml
    SOURCES BoardObject.h
    SOURCES BoardData.h
    QML_FILES CircularButton.qml
)

# Подключение библиотек
target_link_libraries(apptestqtstrat
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Qt6::Core
        SQLiteCpp
        sqlite3
)

# Установка
include(GNUInstallDirs)
install(TARGETS apptestqtstrat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
