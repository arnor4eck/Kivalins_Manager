import QtQuick

Rectangle{
    id: root
    property color buttonColor: "darkblue"
    property color parentColor: "lightblue"
    property alias text: caption.text
    property alias textSize: caption.font.pixelSize
    property bool needsPadding: true
    property int padding: 20

    color: parentColor
    signal clicked()

    width: Math.max(caption.implicitWidth + (root.needsPadding ? padding * 2 : 0), caption.implicitHeight + (root.needsPadding ? padding * 2 : 0))
    height: root.width

    Rectangle{
        anchors.fill: parent
        width: root.width
        height: root.height
        radius: 180
        color: mouseArea.containsPress ? Qt.darker(root.buttonColor, 1.3) : root.buttonColor

        Text{
            id: caption
            anchors.centerIn: parent
            color: "lightblue"
            text: qsTr("text")
            font.pixelSize: 24
        }
        MouseArea{
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                root.clicked();
            }
        }
    }
}
