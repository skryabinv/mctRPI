import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import "../Assets" as Assets

Controls.DelayButton {
    id: root
    property bool keepChecked: true
    property alias color: bg.color
    contentItem: Text {
        id: textItem
        text: root.text
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: Assets.Style.colorTextForeground
        font: root.font
    }
    background: Rectangle {
        id: bg
        anchors.fill: parent
        color: Assets.Style.colorBackgroundLight
        border.width: 1
        border.color: Assets.Style.colorTextBorder
        radius: 5
        Rectangle {
            id: fill
            anchors.margins: parent.border.width
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: Assets.Style.colorTextBackground
            radius: parent.radius
            width: parent.width * root.progress - parent.border.width - 1
        }
    }

    onCheckedChanged: {
        // Prevent checked state if checkable set to false
        if(!keepChecked && checked) {
            checked = false
        }
    }


}
