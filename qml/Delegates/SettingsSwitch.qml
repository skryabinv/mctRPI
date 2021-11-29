import QtQuick 2.0
import "../Assets" as Assets

Item {
    id: root
    property var textItems: []
    property int currentIndex: 0
    implicitWidth: Math.max(150, content.implicitWidth)
    implicitHeight: content.height + 20
    Rectangle {
        anchors.fill: parent
        border.color: Assets.Style.colorTextBorder
        border.width: 2
        color: Assets.Style.colorBackgroundLight
        radius: 5
        Text {
            id: content
            text: textItems[currentIndex]
            anchors.centerIn: parent
            color: Assets.Style.colorTextForeground
            font.pixelSize: 22
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                currentIndex = (currentIndex + 1) % textItems.length
            }
        }
    }
}
