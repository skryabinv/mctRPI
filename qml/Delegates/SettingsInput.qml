import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "../Dialogs" as DLG
import "../Assets" as Assets
import QtQuick.VirtualKeyboard 2.14

Item {
    id: root
    property alias text: content.text
    implicitWidth: Math.max(150, content.implicitWidth)
    implicitHeight: content.height + 20
    Rectangle {
        id: bg
        anchors.fill: parent
        TextInput {
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            id: content
            anchors.centerIn: parent
            font.pixelSize: 22
            color: Assets.Style.colorTextForeground
        }
        border.width: 2
        border.color: Assets.Style.colorTextBorder
        color: Assets.Style.colorTextBackground
        radius: 5
//        MouseArea {
//            anchors.fill: parent
//            onPressed: {
//                bg.color = "gray"
//            }
//            onReleased: {
//                console.log("released")
//                bg.color = Assets.Style.colorTextBackground
//                inputPanel.active = true
//            }

//        }

//        InputPanel {
//            id: inputPanel
//            //: Qt.ImhFormattedNumbersOnly
//            visible: active
//            y: active ? parent.height - inputPanel.height : parent.height
//            anchors.left: parent.left
//            anchors.right: parent.right
//        }
    }



}
