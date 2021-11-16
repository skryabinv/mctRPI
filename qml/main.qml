import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.14
import "Assets" as Assets

Window {
    width: 1024
    height: 600
    visible: true

    Item {
        id: controlPanel
        property alias title: textTitle.text
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: stack.depth > 1 ? 60: 0
        Rectangle {
            anchors.fill: parent
            color: "black"

            Text {
               id: textArrow
               font.family: Assets.Style.fontAwesome
               text: "\uf053"
               anchors.left: parent.left
               anchors.leftMargin: 20
               anchors.verticalCenter: parent.verticalCenter
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
               font.pixelSize: 36
               color: "white"
           }

            Text {
                id: textTitle
                anchors.left: textArrow.right
                anchors.leftMargin: 50
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 32
                color: "white"
            }

            MouseArea {
               id: mouseArea
               anchors.top: parent.top
               anchors.bottom: parent.bottom
               anchors.left: parent.left
               anchors.right: textTitle.left
               onReleased: {
                   appController.resetMode()
               }
           }
        }
    }

    StackView {
        id: stack
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: controlPanel.bottom
        anchors.bottom: parent.bottom
        clip: true
        initialItem: "qrc:/qml/Views/StartView.qml"
    }

    Connections {
        target: appController
        function onModeOperatorActivated() {
            stack.push("qrc:/qml/Views/OperatorView.qml")
            controlPanel.title = appController.operatorModeController.description
        }
        function onModeManualActivated() {
            stack.push("qrc:/qml/Views/ManualView.qml")
            controlPanel.title = appController.manualModeController.description
        }
        function onModeSettingsActivated() {
            stack.push("qrc:/qml/Views/SettingsView.qml")
            controlPanel.title = appController.settingsModeController.descritpion
        }
        function onModeReseted() {
            stack.pop()
        }
    }
}
