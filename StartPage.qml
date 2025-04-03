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
