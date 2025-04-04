import QtQuick
import QtQuick.Controls

Popup {
    id: root
    required property int textSize
    property int boardId: -1;

    anchors.centerIn: Overlay.overlay
    width: Math.max(nameField.implicitWidth, descriptionField.implicitWidth, createButton.width) + 30
    height: nameField.implicitHeight + descriptionField.implicitHeight + createButton.height + 50

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        id: rect
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5
        ErrorWindow{
            textSize: root.textSize
            id: error
        }

        SuccessWindow{
            id: success
            textSize: root.textSize
        }

        Column {
            anchors.centerIn: parent
            spacing: 10

            TextField {
                id: nameField
                height: root.textSize
                width: createButton.width
                font.pointSize: 24 / (root.textSize == 24 ? 2 : 1)
                placeholderText: "Название задачи"
            }

            TextField {
                id: descriptionField
                height: root.textSize
                width: createButton.width
                font.pointSize: 24 / (root.textSize == 24 ? 2 : 1)
                placeholderText: "Описание задачи"
            }

            CustomButton {
                id: createButton
                text: "Сохранить"
                parentColor: rect.color
                onClicked: {
                    createTaskObject.setName(nameField.text)
                    createTaskObject.setDescription(descriptionField.text)
                    createTaskObject.setBoardId(root.boardId)
                    if (createTaskObject.saveData()) {
                        nameField.text = '';
                        descriptionField.text = '';

                        success.text = "Задача создана!";
                        success.textSize = root.textSize
                        success.open();
                        taskModel.refreshModel(boardId);
                        root.close();
                    }
                }
            }

            Connections {
                target: createTaskObject
                function onShowError(message) {
                    error.errorText = message;
                    error.textSize = root.textSize
                    error.open();
                }
            }
        }
    }
}
