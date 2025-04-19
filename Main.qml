import QtQuick
import QtQuick.Controls
import "./board"

Window {
    id: window
    width: 640 * (window.textSize == 24 ? 1 : 2)
    height: 480 * (window.textSize == 24 ? 1 : 2)
    visible: true
    title: qsTr("Kivalin`s Manager")

    property color backgroundColor: "lightblue"
    property bool visibilit: false
    property int textSize: (visibilit ? 48 : 24)

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: startPage

    }
    StartPage {
        id: startPage
        backgroundColor: window.backgroundColor
        textSize: window.textSize
        stackView: stackView
    }

}
