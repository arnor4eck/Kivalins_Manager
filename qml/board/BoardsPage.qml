import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../dto"

Page{
    id: root
    property color backgroundColor: "lightblue"
    property int textSize: 24
    property StackView stackView

    background: Rectangle{
        id: backgroundRect
        color: backgroundColor
    }

    ColumnLayout{
        id: coColumn
        anchors.fill: parent
        spacing: 5

        CreateBoardWindow{
            id: createBoard
            textSize: root.textSize
        }

        CustomButton{
            text: "<"
            textSize: root.textSize
            needsPadding: false
            radius: 0
            parentColor: root.backgroundColor
            onClicked: {
                stackView.pop()
            }
        }

        CustomButton{
            Layout.alignment: Qt.AlignHCenter
            text: "Создать доску"
            textSize: root.textSize
            Layout.fillWidth: true
            parentColor: root.backgroundColor
            onClicked: {
                createBoard.open();
            }
        }
        Rectangle{
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            width: root.width - 10
            height: 1
            color: "black"
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Flow {
                width: root.width
                spacing: 10

                Repeater {
                    model: boardModel

                    delegate: BoardIcon{
                        boardName: model.name
                        textSize: root.textSize
                        description: model.description
                        creationTime: model.creationTime
                        stackView: root.stackView
                        boardId: model.id
                    }
                }
            }
        }

        Item{
            Layout.fillHeight: true
        }
    }
}

