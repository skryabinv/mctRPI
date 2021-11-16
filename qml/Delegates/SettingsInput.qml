import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "../Dialogs" as DLG
import "../Assets" as Assets
import QtQuick.VirtualKeyboard 2.14

Item {
    id: root
    property bool isInteger: false
    property alias text: content.text
    property bool dirty: false
    implicitWidth: Math.max(150, content.implicitWidth)
    implicitHeight: content.height + 20
    Rectangle {
        id: bg
        anchors.fill: parent
        Text {
            id: content
            anchors.centerIn: parent
            font.pixelSize: 22
            color: Assets.Style.colorTextForeground
            onTextChanged: {
                root.dirty = true
            }
        }
        border.width: 2
        border.color: Assets.Style.colorTextBorder
        color: Assets.Style.colorTextBackground
        radius: 5
        MouseArea {
            anchors.fill: parent
            onPressed: {
                bg.color = "gray"
            }
            onReleased: {
                console.log("released")
                bg.color = Assets.Style.colorTextBackground
                inputDialog.show()
            }
        }

        DLG.DialogNumericInput {
            id: inputDialog
            visible: false
        }

        Connections {
            target: inputDialog
            function onAccepted(data) {
                console.log(data)
                text = data
            }
        }

    }



}
