import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    property int textSize: 24
    property string boardName: "";
    property string description: "";
    property string creationTime: "";
    property int boardId: -1;
    property StackView stackView

    width: Math.max(200, name.implicitWidth, showDescription.width, openBoardPage.width) + 30
    height: name.implicitHeight + showDescription.height + openBoardPage.height + 60
    color: Qt.darker("lightblue", 1.3)

    ColumnLayout{
        id: coColumn
        anchors.fill: parent
        spacing: 5

        BoardIconDescriptionWindow{
            id: descriptionWindow
            textSize: root.textSize
            description: root.description
            creationTime: root.creationTime
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
            text: root.boardName
            font.pixelSize: root.textSize
        }

        CustomButton{
            id: openBoardPage
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            parentColor: root.color
            Layout.bottomMargin: 5
            text: "Открыть доску"
            textSize: root.textSize - 8
            onClicked: {
                stackView.push("BoardPage.qml", {
                    textSize: root.textSize,
                    stackView: root.stackView,
                    boardName: root.boardName,
                    boardId: root.boardId
                })
            }
        }


    }
}
