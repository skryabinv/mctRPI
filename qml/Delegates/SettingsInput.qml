import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "../Dialogs" as DLG

Item {
    id: root
    property alias text: content.text
    implicitWidth: Math.max(150, content.implicitWidth)
    implicitHeight: content.height + 20
    Rectangle {
        id: bg
        anchors.fill: parent
        Text {
            id: content
            anchors.centerIn: parent
            font.pixelSize: 22
        }
        border.width: 2
        border.color: "LightSteelBlue"
        color: "lightgray"
        radius: 5
        MouseArea {
            anchors.fill: parent
            onPressed: {
                bg.color = "gray"
            }
            onReleased: {
                console.log("released")
                bg.color = "lightgray"
            }

        }
    }



}
