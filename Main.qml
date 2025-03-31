import QtQuick
import QtQuick.Controls

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Kivalin`s Manager")

    property color backgroundColor: "lightblue"
    property int textSize: 24

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
