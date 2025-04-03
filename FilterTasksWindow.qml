import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: root
    property int textSize: 24;
    property int parentWidth: 0;
    property int parentHeight: 0;
    property int boardId: 0;

    Component.onCompleted: {
        typeModel.refreshModel(root.boardId)
    }

    anchors.centerIn: Overlay.overlay
    width: root.parentWidth / (textSize == 24 ? 2 : 1);
    height: root.parentHeight / (textSize == 24 ? 2 : 1);

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    background: Rectangle {
        id: mainRect
        color: Qt.darker("lightblue", 1.3)
        radius: 5

    }
    ScrollView {
        anchors.fill: parent

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
                    height: 120


                    ColumnLayout{
                        anchors.fill: parent
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.fillWidth: true
                        spacing: 5
                        Text{
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                            text: model.name
                            font.pixelSize: root.textSize
                        }

                        CustomButton{
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                            parentColor: rect.color
                            text: "Выбрать"
                            textSize: root.textSize - 8
                            padding: root.textSize - 8
                            onClicked: {
                                taskModel.refreshModel(root.boardId, model.id)
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

}
