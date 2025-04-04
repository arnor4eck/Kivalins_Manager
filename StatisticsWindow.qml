import QtQuick
import QtQuick.Controls

Popup {
    id: root
    required property int textSize

    anchors.centerIn: Overlay.overlay
    // width: root.parentWidth / root.proportion + (root.textSize == 24 ? 30 : 0)
    // height: root.parentWidth / root.proportion + (root.textSize == 24 ? 30 : 0)

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5

    }
}
