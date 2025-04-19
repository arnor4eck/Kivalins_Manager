import QtQuick
import QtQuick.Controls
import "../dto"

Popup {
    id: root
    required property int textSize

    anchors.centerIn: Overlay.overlay
    width: Math.max(nameField.implicitWidth, descriptionField.implicitWidth, saveButton.width) + 30
    height: nameField.implicitHeight + descriptionField.implicitHeight + saveButton.height + 100;

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
                width: saveButton.width
                font.pointSize: 24 / (root.textSize == 24 ? 2 : 1)
                placeholderText: "Название доски"
            }

            TextField {
                id: descriptionField
                height: root.textSize
                width: saveButton.width
                font.pointSize: 24 / (root.textSize == 24 ? 2 : 1)
                placeholderText: "Описание доски"
            }

            CustomButton {
                id: saveButton
                parentColor: rect.color
                textSize: root.textSize
                text: "Сохранить"
                onClicked: {
                    createBoardObject.setName(nameField.text)
                    createBoardObject.setDescription(descriptionField.text)
                    if (createBoardObject.saveData()) {
                        nameField.text = '';
                        descriptionField.text = '';

                        success.text = "Доска создана";
                        success.textSize = root.textSize
                        success.open();
                        root.close();
                    }
                }
            }

            Connections {
                target: createBoardObject
                function onShowError(message) {
                    error.errorText = message;
                    error.textSize = root.textSize
                    error.open();
                }
            }
        }
    }
}
