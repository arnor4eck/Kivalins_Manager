import QtQuick
import QtQuick.Controls

Popup {
    id: root
    property int textSize: 24
    property int proportion: (root.textSize == 24 ? 4 : 2);
    property int parentWidth: 0;
    property int parentHeight: 0;
    property int boardId: -1;

    anchors.centerIn: Overlay.overlay
    width: root.parentWidth / root.proportion
    height: root.parentWidth / root.proportion

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
                placeholderText: "Название типа"
            }

            Button {
                text: "Сохранить"
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
