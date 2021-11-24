import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets

Item {
    id: root
    implicitHeight: listView.implicitHeight
    property string selectedAxis: appController.manualModeController.selectedAxis

    function getAxisColor(axis) {
         console.log("getAxisColor" + axis)
         return root.selectedAxis === axis ? Assets.Style.colorTextSelectedAxis : Assets.Style.colorTextForeground
    }

    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackground
    }

    ListView {
        id: listView
        interactive: false
        spacing: 10
        topMargin: 10
        anchors.fill: parent
        model: [ "X", "Y", "Z" ]
        delegate: Rectangle {
            height: 60
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            color: Qt.lighter(Assets.Style.colorBackground)
//            border.color: Assets.Style.colorTextBorder
            radius: 5
            RowLayout {
                id: row
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20

                Text {
                    id: textName
                    height: row.height
                    text: modelData + ":"
                    color: Assets.Style.colorTextForeground
                    font.pixelSize: 32
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    id: textPosition
                    Layout.fillWidth: true
                    height: row.height
                    text: "0.0"
                    color: root.getAxisColor(modelData)
                    font.pixelSize: 32
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignRight

                    Behavior on color {
                        ColorAnimation {
                            duration: 200
                        }
                    }
                }

                Timer {
                    id: timerUpdatePos
                    running: true
                    interval: 250
                    repeat: true
                    onTriggered: {
                        let pos = appController.manualModeController.getAxisPos(modelData)
                        textPosition.text = pos.toFixed(4)
                    }
                }
            }
        }


    }
}
