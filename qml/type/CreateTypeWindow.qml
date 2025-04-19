import QtQuick
import QtQuick.Controls
import "../dto"

Popup {
    id: root
    required property int textSize
    property int boardId: -1;

    anchors.centerIn: Overlay.overlay
    width: Math.max(nameField.implicitWidth, createButton.width) + 30
    height: nameField.implicitHeight + createButton.height + 50

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        id: rect
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5
        ErrorWindow{
            id: error
            textSize: root.textSize
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
                placeholderText: "Название типа"
            }

            CustomButton {
                id: createButton
                text: "Сохранить"
                textSize: root.textSize
                parentColor: rect.color
                onClicked: {
                    createTypeObject.setName(nameField.text)
                    createTypeObject.setBoardId(root.boardId)
                    if (createTypeObject.saveData()) {
                        nameField.text = '';

                        success.text = "Тип задачи создан!";
                        success.textSize = root.textSize
                        success.open();
                        typeModel.refreshModel(boardId);
                        root.close();
                    }
                }
            }

            Connections {
                target: createTypeObject
                function onShowError(message) {
                    error.errorText = message;
                    error.textSize = root.textSize
                    error.open();
                }
            }
        }
    }
}
