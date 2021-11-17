import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import "../Assets" as Assets

Item {
    id: root
    Rectangle {
        anchors.fill: parent
        color: Qt.lighter(Assets.Style.colorBackground)
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 10

        // Кнопки выбора оси
        Group {
            id: groupSelectAxis
            Layout.fillWidth: true
            title: "Выбор оси"
            height: 100
            model: [ "X", "Y", "Z" ]
            Button {

                function isSelected(axis) {
                    return appController.manualModeController.selectedAxis === axis;
                }

                id: btnSelectAxis
                checkable: true
                checked: isSelected(modelData)
                autoExclusive: true
                text: modelData
                background: Rectangle {
                    color: parent.checked ? Assets.Style.colorHomeButtonPressed : Qt.lighter(Assets.Style.colorBackground)
                    border.color: Assets.Style.colorTextBorder
                    implicitWidth: 120
                    implicitHeight: 40
                    radius: 5
                }
                contentItem:  Text {
                    anchors.centerIn: parent
                    text: btnSelectAxis.text
                    color: Assets.Style.colorTextForeground
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onToggled: {
                    if(checked) {
                        appController.manualModeController.selectedAxis = modelData
                    }
                }
            }
        }

        // Кнопки базирования
        Group {
            id: groupHoming
            Layout.fillWidth: true
            title: "Поиск HOME"
            height: 100
            model: [
                {
                    id: 0,
                    text: "Выбранная ось",
                },
                {
                    id: 1,
                    text: "Все оси",
                }
            ]
            Button {

                id: btnHome
                text: modelData.text
                background: Rectangle {
                    color: parent.pressed ? Assets.Style.colorTextBackground : Qt.lighter(Assets.Style.colorBackground)
                    border.color: Assets.Style.colorTextBorder
                    implicitWidth: 250
                    implicitHeight: 40
                    radius: 5
                }
                contentItem:  Text {
                    anchors.centerIn: parent
                    text: btnHome.text
                    color: Assets.Style.colorTextForeground
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onPressAndHold: {
                    if(modelData.id === 0) {
                        appController.manualModeController.homeSelectedAxis()
                    } else {
                        appController.manualModeController.homeAllAxes()
                    }
                }
            }
        }

        JoggingSettingsPanel {
            id: joggingSettings
            Layout.fillWidth: true
        }

        // Ручное перемещение
        Group {
            id: groupJogging
            Layout.fillWidth: true
            height: 150
            spacing: 40
            title: "Перемещение"
            model: [
                {  text: "\uf060"  },
                {  text: "\uf061", }
            ]
            Button {
                id: btnJog
                text: modelData.text
                background: Rectangle {
                    color: parent.pressed ? Assets.Style.colorTextBackground : Qt.lighter(Assets.Style.colorBackground)
                    border.color: Assets.Style.colorTextBorder
                    implicitWidth: 150
                    implicitHeight: 60
                    radius: 5
                }
                contentItem:  Text {
                    anchors.centerIn: parent
                    text: parent.text
                    color: Assets.Style.colorTextForeground
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onPressAndHold: {
                   console.log(modelData.text)
                }
            }
        }

    }

}
