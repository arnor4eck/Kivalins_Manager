import QtQuick
import QtQuick.Controls 2.15

Popup {
    id: root
    property alias errorText: errorMessage.text
    property int textSize: 24

    anchors.centerIn: Overlay.overlay
    width: Math.max(parent.width / 4, errorMessage.implicitWidth + 40)
    height: Math.max(parent.height / 4, errorMessage.implicitHeight + error.implicitHeight + 40)

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Rectangle {
        anchors.fill: parent
        color: "red"
        radius: 5

        Column {
            anchors.centerIn: parent
            spacing: 10

            Text {
                id: error
                font.pixelSize: root.textSize
                text: "Ошибка!"
                color: "black"
                font.bold: true
            }

            Text {
                font.pixelSize: root.textSize
                id: errorMessage
                text: "text"
            }
        }
    }
}
