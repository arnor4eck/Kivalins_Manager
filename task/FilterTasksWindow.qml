import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../dto"

Popup {
    id: root
    required property int textSize
    property int parentWidth: 0;
    property int parentHeight: 0;
    property int boardId: 0;

    Component.onCompleted: {
        typeModel.refreshModel(root.boardId)
    }

    anchors.centerIn: Overlay.overlay
    width: root.parentWidth / 2;
    height: root.parentHeight / 2;

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    background: Rectangle {
        id: mainRect
        color: Qt.darker("lightblue", 1.3)
        radius: 5

    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                width: root.width
                anchors.fill: parent
                spacing: 10

                Repeater {
                    model: typeModel
                    delegate: Rectangle{
                        id: rect
                        color: Qt.darker("lightblue", 1.5)
                        border.color: "black"
                        border.width: 2
                        height: typeName.implicitHeight + chooseButton.height + 20


                        ColumnLayout{
                            anchors.fill: parent
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                            Layout.fillWidth: true
                            spacing: 5
                            Text{
                                id: typeName
                                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                                text: model.name
                                font.pixelSize: root.textSize
                            }

                            CustomButton{
                                id: chooseButton
                                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                                parentColor: rect.color
                                text: "Выбрать"
                                textSize: root.textSize - 8
                                padding: root.textSize - 8
                                onClicked: {
                                    taskModel.refreshModel(root.boardId, model.id)
                                    root.close()
                                }
                            }

                            Item{
                                Layout.fillHeight: true
                            }
                        }
                        Layout.fillWidth: true
                    }
                }
                Item{
                    Layout.fillHeight: true
                }
            }

        }
        CustomButton {
            text: "Сбросить фильтр"
            textSize: root.textSize - 8
            padding: root.textSize - 8
            Layout.fillWidth: true
            onClicked: {
                taskModel.refreshModel(root.boardId)
                root.close()
            }
        }
    }
}
