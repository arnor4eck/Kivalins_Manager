import QtQuick

Rectangle {
    id: root
    property color backgroundColor: "lightblue"
    property int textSize: 24

    Rectangle{
        id: backgroundRect
        color: root.backgroundColor
        CustomButton{
            text: "<"
            textSize: root.textSize
            needsPadding: false
            radius: 0
            onClicked: {
                stackView.pop()
            }
        }

    }
}
