import QtQuick
import QtQuick.Controls

Page{
    id: root
    property color backgroundColor: "lightblue"
    property int textSize: 24
    property StackView stackView

    Navbar{}

    background: Rectangle{
        id: backgroundRect
        color: root.backgroundColor
    }

    Column {
        id: buttonsRow
        anchors.centerIn: parent
        spacing: 10

        CustomButton {
            id: myBoards
            text: "Режим для слабовидящих"
            parentColor: root.backgroundColor
            textSize: root.textSize
            onClicked: {
                console.log("сделай")
            }
        }

        CustomButton {
            id: faq
            text: "F.A.Q"
            width: myBoards.width
            height: myBoards.height
            textSize: root.textSize
            parentColor: root.backgroundColor
            onClicked: {
                Qt.openUrlExternally("https://docs.google.com/document/d/1zPHbxPAOk9KvekUQxETPAlHZWjFHEZcCWvdmcq0k1ek/edit?usp=sharing");
            }
        }
    }
}
