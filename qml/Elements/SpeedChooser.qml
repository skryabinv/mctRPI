import QtQuick 2.0
import "../Assets" as Assets

Item {
    id: root
    property double speedValue: 0.5
    property alias sliderWidth: slider.width
    property alias sliderHeight: slider.height

    Text {
        id: title
        text: "Скорость, %:"
        anchors.left: parent.left
        anchors.right: parent.right
        font.pixelSize: 18
        color: Assets.Style.colorTextForeground
    }

    Rectangle {
        id: bg
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        color: Assets.Style.colorBackground
        radius: 5
    }

    Rectangle {
        id: slider
        anchors.centerIn: bg
        color: Assets.Style.colorBackgroundLight
        border.color: Assets.Style.colorTextBorder
        radius: 5

        MouseArea {
            anchors.fill: parent
            onMouseXChanged: {
                if(pressed) {
                    let value = (mouseX - parent.x) / parent.width
                    speedValue = Math.min(1.0, Math.max(0.05, value))
                }
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.margins: slider.border.width
            width: speedValue * parent.width - slider.border.width
            radius: 5
            color: Assets.Style.colorTextBackground
        }

        Text {
            id: textValue
            anchors.centerIn: slider
            text: Math.round(100 * speedValue) + " %"
            font.pixelSize: 16
            color: Assets.Style.colorTextForeground
        }


    }
}
