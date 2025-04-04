import QtQuick
import QtQuick.Controls 2.15

Popup {
    id: root
    property alias text: message.text
    required property int textSize

    anchors.centerIn: Overlay.overlay
    width: Math.max(parent.width / 4, message.implicitWidth + 40)
    height: Math.max(parent.height / 4, message.implicitHeight + error.implicitHeight + 40)

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Rectangle {
        anchors.fill: parent
        color: "green"
        radius: 5

        Column {
            anchors.centerIn: parent
            spacing: 10

            Text {
                id: error
                font.pixelSize: root.textSize
                text: "Успешно!"
                color: "black"
                font.bold: true
            }

            Text {
                font.pixelSize: root.textSize
                id: message
                text: "text"
            }
        }
    }
}
