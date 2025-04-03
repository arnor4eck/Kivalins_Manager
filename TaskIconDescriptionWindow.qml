import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: root
    property int textSize: 24
    property string name: ""
    property string description: ""
    property string creationTime: ""
    property int boardId: 0
    property int taskId: -1
    property string taskType: ""

    anchors.centerIn: Overlay.overlay
    width: Math.max(description.implicitWidth, constDesc.implicitWidth,
                    constCreate.implicitWidth, constCreate.implicitWidth,
                    creationTime.implicitWidth, constType.implicitWidth, taskTypeText.implicitWidth) + 40
    height: description.implicitHeight + 50 + constDesc.implicitHeight +
            constCreate.implicitHeight + creationTime.implicitHeight + button.height + constType.implicitHeight + taskTypeText.implicitHeight

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        id: mainRect
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5
        ColumnLayout{
            id: coColumn
            anchors.fill: parent
            spacing: 5
            Text{
                id: constDesc
                font.pixelSize: root.textSize
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                text: "Описание"
                font.weight: Font.DemiBold
            }

            Text{
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                id: description
                text: root.description.replace(/(.{20})/g, "$1\n")
                font.pixelSize: root.textSize
            }

            Text{
                id: constType
                font.pixelSize: root.textSize
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                text: "Тип задачи"
                font.weight: Font.DemiBold
            }

            Text{
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                id: taskTypeText
                text: root.taskType.replace(/(.{20})/g, "$1\n")
                font.pixelSize: root.textSize
            }

            Text{
                id: constCreate
                font.pixelSize: root.textSize
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                text: "Дата создания"
                font.weight: Font.DemiBold
            }

            Text{
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                id: creationTime
                text: root.creationTime
                font.pixelSize: root.textSize
            }

            UpdateTaskWindow{
                id: updateTask
                textSize: root.textSize

                parentWidth: root.width
                parentHeight: root.height

                taskName: root.name
                taskDescription: root.description
                typeName: root.taskType
                taskId: root.taskId;
                boardId: root.boardId;
            }

            CustomButton{
                id: button
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                parentColor: mainRect.color

                Layout.bottomMargin: 5
                text: "Редактировать"
                textSize: root.textSize - 8
                onClicked: {
                    updateTask.open();
                    root.close();
                }
            }

            Item{
                Layout.fillHeight: true
            }
        }
    }
}
