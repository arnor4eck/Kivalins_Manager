import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: root
    required property int textSize
    property int boardId: -1
    property int createdTasks: -1
    property int doneTasks: -1

    anchors.centerIn: Overlay.overlay
    width: Math.max(countTasks.implicitWidth, doneTasks.implicitWidth) + 50
    height: countTasks.height + doneTasks.height + 50

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5
        ColumnLayout {
            anchors.fill: parent
            spacing: 10

            Text{
                id: countTasks
                Layout.alignment: Qt.AlignLeft | Qt.AlignHTop
                font.pixelSize: root.textSize
                text: "Общее количество задач: " + root.createdTasks
            }
            Text{
                id: doneTasks
                Layout.alignment: Qt.AlignLeft | Qt.AlignHTop
                font.pixelSize: root.textSize
                text: "Выполнено: " + root.doneTasks
            }
        }
    }
}
