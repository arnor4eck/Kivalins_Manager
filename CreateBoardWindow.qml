import QtQuick
import QtQuick.Controls

Popup {
    id: root
    property int textSize: 24
    property int proportion: (root.textSize == 24 ? 4 : 2);

    anchors.centerIn: Overlay.overlay
    width: parent.width / root.proportion
    height: parent.width / root.proportion

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5
        ErrorWindow{
            id: error
        }

        SuccessWindow{
            id: success
        }

        Column {
            anchors.centerIn: parent
            spacing: 10

            TextField {
                id: nameField
                placeholderText: "Название доски"
            }

            TextField {
                id: descriptionField
                placeholderText: "Описание доски"
            }

            Button {
                text: "Сохранить"
                onClicked: {
                    board.setName(nameField.text)
                    board.setDescription(descriptionField.text)
                    if (board.saveData()) {
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
                target: board
                function onShowError(message) {
                    error.errorText = message;
                    error.textSize = root.textSize
                    error.open();
                }
            }
        }
    }
}
