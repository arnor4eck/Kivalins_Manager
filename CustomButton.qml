import QtQuick

Rectangle{
    id: root
    property color buttonColor: "darkblue"
    property color parentColor: "lightblue"
    property alias text: caption.text
    property alias textSize: caption.font.pixelSize
    property alias radius: rect.radius
    property bool needsPadding: true
    property int padding: 20  // Отступы вокруг текста
    color: parentColor

    signal clicked()

    width: caption.implicitWidth + (root.needsPadding ? padding * 2 : 0)
    height: caption.implicitHeight + (root.needsPadding ? padding * 2 : 0)

    Rectangle{
        id: rect
        anchors.fill: parent
        radius: 4
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
