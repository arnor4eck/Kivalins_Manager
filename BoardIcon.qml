import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    property int textSize: 24
    property alias boardName: name.text
    property alias description: descriptionWindow.description
    property alias creationTime: descriptionWindow.creationTime

    width: 200
    height: 200
    color: Qt.darker("lightblue", 1.3)

    ColumnLayout{
        id: coColumn
        anchors.fill: parent
        spacing: 5

        BoardIconDescriptionWindow{
            id: descriptionWindow
            textSize: root.textSize
            description: "Описание"
            creationTime: "22-12-2222 21:21:21"
        }

        CircularButton{
            id: showDescription
            parentColor: root.color
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.rightMargin: root.textSize * 0.5
            Layout.topMargin: root.textSize * 0.5

            text: "?"
            textSize: root.textSize
            needsPadding: false
            onClicked: {
                descriptionWindow.open()
            }
        }

        Text{
            Layout.alignment: Qt.AlignHCenter
            id: name
            text: qsTr("Название")
            font.pixelSize: 24
        }

        CustomButton{
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            parentColor: root.color
            Layout.bottomMargin: 5
            text: "Открыть доску"
            textSize: root.textSize - 8
            onClicked: {
                // открытие доски
            }
        }


    }
}
