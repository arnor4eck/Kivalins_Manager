import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: root
    property int textSize: 24
    property int proportion: (root.textSize == 24 ? 4 : 2);
    property string description: ""
    property alias creationTime: creationTime.text

    anchors.centerIn: Overlay.overlay
    width: Math.max(description.implicitWidth, constDesc.implicitWidth,
                    constCreate.implicitWidth, constCreate.implicitWidth, creationTime.implicitWidth) + 40
    height: description.implicitHeight + 30 + constDesc.implicitHeight + constCreate.implicitHeight + creationTime.implicitHeight

    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Rectangle {
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
            Item{
                Layout.fillHeight: true
            }
        }
    }
}
