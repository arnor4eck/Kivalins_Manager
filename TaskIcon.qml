import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    property int textSize: 24
    property string taskName: "";
    property string description: "";
    property string creationTime: "";
    property string taskType: "";
    property int taskId: -1;
    property int boardId: -1;

    Layout.fillWidth: true
    height: name.implicitHeight + showDescription.height + 10
    color: Qt.darker("lightblue", 1.3)

    ColumnLayout{
        id: coColumn
        anchors.fill: parent
        spacing: 5

        TaskIconDescriptionWindow{
            id: descriptionWindow
            textSize: root.textSize
            description: root.description
            creationTime: root.creationTime
            taskType: root.taskType
            taskId: root.taskId
            boardId: root.boardId
            name: root.taskName
        }
        Text{
            Layout.alignment: Qt.AlignHCenter
            id: name
            text: root.taskName
            font.pixelSize: 24
        }

        CustomButton{
            id: showDescription
            parentColor: root.color
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            text: "Подробнее"
            textSize: root.textSize - 8
            padding: root.textSize - 8
            onClicked: {
                descriptionWindow.open()
            }
        }

        Item{
            Layout.fillHeight: true
        }
    }
}
