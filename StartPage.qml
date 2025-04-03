import QtQuick
import QtQuick.Controls

Page{
    id: root
    property color backgroundColor: "lightblue"
    property int textSize: 24
    property StackView stackView

    background: Rectangle{
        id: backgroundRect
        color: root.backgroundColor
    }

    Item {
        id: roort
        width: 200
        height: 50

        property bool expanded: false
        property int menuItemHeight: 40
        property var menuItems: ["Действие 1", "Действие 2", "Действие 3"]

        // Главная кнопка
        Button {
            id: mainButton
            text: "Меню"
            width: parent.width
            height: parent.height

            onClicked: {
                roort.expanded = !roort.expanded
            }
        }

        // Контейнер меню
        Column {
            id: menuContainer
            width: parent.width
            anchors.top: mainButton.bottom
            anchors.topMargin: 5
            spacing: 2
            visible: roort.expanded

            Repeater {
                model: roort.menuItems

                delegate: Button {
                    width: parent.width
                    height: roort.menuItemHeight
                    text: modelData

                    onClicked: {
                        console.log("Выбрано:", modelData)
                        roort.expanded = false
                    }
                }
            }
        }

        // Анимация раскрытия
        Behavior on height {
            NumberAnimation { duration: 200 }
        }

        // Автоматическое закрытие при клике вне меню
        MouseArea {
            anchors.fill: parent
            enabled: roort.expanded
            onClicked: roort.expanded = false
        }
    }

    Row {
        id: buttonsRow
        anchors.centerIn: parent
        spacing: 10  // Расстояние между кнопками

        CustomButton {
            id: myBoards
            text: "Мои доски"
            parentColor: root.backgroundColor
            textSize: root.textSize
            onClicked: {
                stackView.push("BoardsPage.qml", {
                    textSize: root.textSize,
                    backgroundColor: root.backgroundColor,
                    stackView: root.stackView
                })
            }
        }

        CustomButton {
            id: settings
            text: "Настройки"
            width: myBoards.width
            height: myBoards.height
            textSize: root.textSize
            parentColor: root.backgroundColor
            onClicked: {
                stackView.push("SettingsPage.qml", {
                    textSize: root.textSize,
                    backgroundColor: root.backgroundColor,
                    stackView: root.stackView
                })
            }
        }
    }
}
