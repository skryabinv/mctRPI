import QtQuick 2.0
import "../Assets" as Assets

Item {
    id: root
    signal pressed()
    Rectangle {
        anchors.fill: parent
        radius: 5
        border.color: Assets.Style.colorTextBorder
        color: mouseArea.checked ? Assets.Style.colorCancelButtonPressed : Assets.Style.colorCancelButtonReleased;
        Text {
            anchors.centerIn: parent
            text: "СТОП"
            color: Assets.Style.colorTextForeground
            font.pixelSize: 28            
        }
        MouseArea {
            property bool checked: false
            id: mouseArea
            anchors.fill: parent
            onPressed: {
                checked = true
            }
            onReleased: {
                checked = false
                root.pressed()
            }
        }
    }
}
