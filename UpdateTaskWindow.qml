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
    property string typeName: ""
    property int taskId: -1;
    property int boardId: -1;
    property bool wasClicked: false

    onOpened: {
        typeCombo.currentIndex = -1
        typeCombo.selectedDisplayText = root.typeName
    }

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
                width: nameField.width
                text: (root.taskDescription != "Описание отсутствует" ? root.taskDescription : "");
                placeholderText: "Описание задачи"
            }

            ComboBox {
                id: typeCombo
                model: typeModel
                textRole: "name"
                valueRole: "id"
                width: descriptionField.width


                property string selectedDisplayText: root.typeName

                displayText: selectedDisplayText

                delegate: ItemDelegate {
                    width: typeCombo.width
                    height: 40
                    text: model.name
                    highlighted: typeCombo.highlightedIndex === index

                    background: Rectangle {
                        color: highlighted ? Qt.darker("white", 1.3) : "white"
                    }
                }

                onActivated: {
                    root.wasClicked = true
                    selectedDisplayText = currentText
                }
            }

            Button {
                text: "Сохранить"
                onClicked: {
                    if (taskModel.updateTask(root.boardId, root.taskId, nameField.text,
                                descriptionField.text, (wasClicked ? typeCombo.currentValue : 0))){
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
