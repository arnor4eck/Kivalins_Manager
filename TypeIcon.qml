import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    property int textSize: 24
    property string typeName: "";
    property int typeId: 0;
    property int boardId: 0;

    width: 300
    height: 120
    color: Qt.darker("lightblue", 1.3)

    ColumnLayout{
        id: coColumn
        anchors.fill: parent
        spacing: 10

        Text{
            Layout.alignment: Qt.AlignHCenter
            id: name
            text: root.typeName
            font.pixelSize: 24
        }

        CustomButton{
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            parentColor: root.color
            buttonColor: "red"
            textColor: "black"
            visible: (root.typeId == 1 || root.typeId == 2 ? false : true);

            text: "Удалить"
            textSize: root.textSize - 8

            onClicked: {
                typeModel.deleteType(root.typeId, root.boardId);
            }
        }

        Item{
            Layout.fillHeight: (root.typeId == 1 || root.typeId == 2 ? false : true);
        }
    }
}
