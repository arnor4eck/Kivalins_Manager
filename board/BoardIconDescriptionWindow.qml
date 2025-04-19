import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../dto"

Popup {
    id: root
    required property int textSize
    property string description: ""
    property alias creationTime: creationTime.text
    property int boardId: -1

    anchors.centerIn: Overlay.overlay
    width: Math.max(description.implicitWidth, constDesc.implicitWidth,
                    constCreate.implicitWidth, constCreate.implicitWidth, creationTime.implicitWidth, deleteButton.width) + 40
    height: description.implicitHeight + 50 + constDesc.implicitHeight +
            constCreate.implicitHeight + creationTime.implicitHeight + deleteButton.height

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
        id: rect
        anchors.fill: parent
        color: Qt.darker("lightblue", 1.3)
        radius: 5
        ColumnLayout{
            id: coColumn
            anchors.fill: parent
            spacing: 5
            Text{
                id: constDesc
                font.pixelSize: root.textSize
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                text: "Описание"
                font.weight: Font.DemiBold
            }

            Text{
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                id: description
                text: root.description.replace(/(.{20})/g, "$1\n")
                font.pixelSize: root.textSize
            }

            Text{
                id: constCreate
                font.pixelSize: root.textSize
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                text: "Дата создания"
                font.weight: Font.DemiBold
            }

            Text{
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
                id: creationTime
                text: "22-12-2222 21:21:21"
                font.pixelSize: root.textSize
            }

            CustomButton{
                id: deleteButton
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                parentColor: rect.color
                buttonColor: "red"
                textColor: "black"

                text: "Удалить"
                textSize: root.textSize

                onClicked: {
                    boardModel.deleteBoard(root.boardId);
                    root.close();
                }
            }

            Item{
                Layout.fillHeight: true
            }
        }
    }
}
