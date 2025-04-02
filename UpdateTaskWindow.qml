import QtQuick
import QtQuick.Controls

Popup {
    id: root
    property int textSize: 24
    property int proportion: (root.textSize == 24 ? 2 : 1);
    property int parentWidth: 0;
    property int parentHeight: 0;
    property string taskName: "";
    property string taskDescription: ""
    property int taskId: -1;
    property int boardId: -1;

    anchors.centerIn: Overlay.overlay
    width: root.parentWidth / root.proportion + (root.textSize == 24 ? 30 : 0)
    height: root.parentWidth / root.proportion + (root.textSize == 24 ? 30 : 0)

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5
        ErrorWindow{
            id: error
        }

        Column {
            anchors.centerIn: parent
            spacing: 10

            TextField {
                id: nameField
                text: root.taskName;
                placeholderText: "Название задачи"
            }

            TextField {
                id: descriptionField
                text: (root.taskDescription != "Описание отсутствует" ? root.taskDescription : "");
                placeholderText: "Описание задачи"
            }

            Button {
                text: "Сохранить"
                onClicked: {
                    if (taskModel.updateTask(root.boardId, root.taskId, nameField.text, descriptionField.text)) {
                        taskModel.refreshModel(boardId);
                        root.close();
                    }
                }
            }

            Connections {
                target: taskModel
                function onShowError(message) {
                    error.errorText = message;
                    error.textSize = root.textSize
                    error.open();
                }
            }
        }
    }
}
