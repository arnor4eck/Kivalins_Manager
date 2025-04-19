import QtQuick
import QtQuick.Controls
import "../dto"

Popup {
    id: root
    required property int textSize
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
    width: Math.max(nameField.implicitWidth, descriptionField.implicitWidth,
                    typeCombo.implicitWidth, saveButton.width) + 30
    height: nameField.height + descriptionField.height + typeCombo.height + saveButton.height + 50

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

        Column {
            anchors.centerIn: parent
            spacing: 10

            TextField {
                id: nameField
                height: root.textSize
                text: root.taskName;
                width: saveButton.width
                font.pointSize: 24 / (root.textSize == 24 ? 2 : 1)
                placeholderText: "Название задачи"
            }

            TextField {
                id: descriptionField
                width: nameField.width
                height: root.textSize
                text: (root.taskDescription != "Описание отсутствует" ? root.taskDescription : "");
                font.pointSize: 24 / (root.textSize == 24 ? 2 : 1)
                placeholderText: "Описание задачи"
            }

            ComboBox {
                id: typeCombo
                model: typeModel
                textRole: "name"
                valueRole: "id"
                width: descriptionField.width
                height: root.textSize

                property string selectedDisplayText: root.typeName

                displayText: selectedDisplayText

                popup: Popup { // скроллбар
                    y: typeCombo.height
                    width: typeCombo.width
                    implicitHeight: Math.min(contentItem.implicitHeight, 200)
                    padding: 1

                    contentItem: ListView {
                        clip: true
                        implicitHeight: contentHeight
                        model: typeCombo.popup.visible ? typeCombo.delegateModel : null
                        currentIndex: typeCombo.highlightedIndex

                        ScrollBar.vertical: ScrollBar {
                            policy: ScrollBar.AsNeeded
                        }

                        boundsBehavior: Flickable.StopAtBounds
                        snapMode: ListView.SnapToItem
                    }

                    background: Rectangle {
                        border.color: "#21be2b"
                        radius: 2
                    }
                }

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

            CustomButton {
                id: saveButton
                parentColor: rect.color
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
