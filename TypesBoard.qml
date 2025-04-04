import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page{
    id: root
    property color backgroundColor: "lightblue"
    property int textSize: 24
    property StackView stackView
    property int boardId: -1;

    Component.onCompleted: {
        typeModel.refreshModel(root.boardId)
    }

    background: Rectangle{
        id: backgroundRect
        color: backgroundColor
    }

    ColumnLayout{
        id: coColumn
        anchors.fill: parent
        spacing: 5

        CreateTypeWindow{
            id: createType
            textSize: root.textSize
            boardId: root.boardId
        }

        CustomButton{
            text: "<"
            textSize: root.textSize
            needsPadding: false
            radius: 0
            parentColor: root.backgroundColor
            onClicked: {
                taskModel.refreshModel(root.boardId);
                stackView.pop()
            }
        }

        CustomButton{
            Layout.alignment: Qt.AlignHCenter
            text: "Создать тип"
            textSize: root.textSize
            Layout.fillWidth: true
            parentColor: root.backgroundColor
            onClicked: {
                createType.open();
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
                    model: typeModel
                    delegate: TypeIcon{
                        typeName: model.name
                        textSize: root.textSize
                        typeId: model.id
                        boardId: root.boardId
                    }
                }
            }
        }

        Item{
            Layout.fillHeight: true
        }
    }
}

