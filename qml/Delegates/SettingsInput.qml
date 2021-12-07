import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "../Dialogs" as DLG
import "../Assets" as Assets
import QtQuick.VirtualKeyboard 2.14

Item {
    id: root
    property alias text: content.text
    property bool isInteger: false
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
        color: Assets.Style.colorBackgroundLight
        radius: 5
        MouseArea {
            anchors.fill: parent
            onPressed: {
                // bg.color = "gray"
            }
            onReleased: {                
                let comp = Qt.createComponent("../Dialogs/DialogNumericInput.qml")
                let obj = comp.createObject(root, {x:0, y:0})
                obj.show()
                obj.accepted.connect((data)=>{text = data});
            }
        }
    }
}
