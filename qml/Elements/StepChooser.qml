import QtQuick 2.12
import "../Assets" as Assets

Item {
    id: root
    property int stepIndex: 0
    property var stepValue: model[stepIndex]
    property var model: []

    function getColor(index) {
        return stepIndex === index ? Assets.Style.colorTextBackground : Assets.Style.colorBackgroundLight
    }

    Text {
        id: title
        text: "Шаг перемещения, мм:"
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

    Row {
        id: row
        anchors.centerIn: bg
        Repeater {
            model: root.model
            delegate: Rectangle {
                id: box
                implicitWidth: 70
                implicitHeight: text.implicitHeight + 8
                color: getColor(index)
                border.color: Assets.Style.colorTextBorder
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: modelData
                    color: Assets.Style.colorTextForeground
                    font.pixelSize: 18
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: stepIndex = index
                }
            }
        }
    }

    Rectangle {
        anchors.fill: row
        color: "transparent"
        border.color: Assets.Style.colorBackground
    }

    Rectangle {
        anchors.fill: row
        color: "transparent"
        border.color: Assets.Style.colorTextForeground
        radius: 5
    }

    Behavior on stepIndex {
        NumberAnimation {
            duration: 100
        }
    }

}
