import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets

Item {
    id: root
    implicitHeight: title.height + bar.height
    property double ring: 10
    property double progress: 0.0
    visible: false

    Rectangle {
        id: bar        
        height: 5
        color: Assets.Style.colorBackground
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5

        Rectangle {
            id: cursor
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: progress * parent.width
            color: Assets.Style.colorTextBackground
        }
    }

    Text {
        id: title
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 5
        anchors.bottom: bar.top
        font.pixelSize: 18
        text: ((progress * 100) | 0) + " %"
        horizontalAlignment: Text.horizontalCenter
        color: Assets.Style.colorTextForeground
    }

    Connections {
        target: boardController
        function onProcessProgressChanged(value) {            
            progress = value
            visible = true
        }
    }

}
