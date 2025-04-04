import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    property int textSize: 24
    property string typeName: "";
    property int typeId: 0;
    property int boardId: 0;

    width: 257
    height: name.implicitHeight + deleteButton.height + 10
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
            id: deleteButton
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            parentColor: root.color
            buttonColor: "red"
            textColor: "black"
            visible: (root.typeId == 1 || root.typeId == 2 ? false : true);

            text: "Удалить"
            textSize: root.textSize - (root.textSize == 24 ? 8 : 24 + 8)

            onClicked: {
                typeModel.deleteType(root.typeId, root.boardId);
            }
        }

        Item{
            Layout.fillHeight: (root.typeId == 1 || root.typeId == 2 ? false : true);
        }
    }
}
