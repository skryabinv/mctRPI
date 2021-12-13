import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets
import "../Delegates" as Delegates

Item {
    id: root
    property var processSettings: ({})
    implicitWidth: 524

    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackgroundLight
    }

    Rectangle {
        id: surfacePanel
        anchors.topMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: btnStart.top
        color: "transparent"
        radius: 5

        ListView {
            id: list
            spacing: 10
            anchors.fill: parent
            model: [
                {
                    title: "Ширина, мм:",
                    data: "x_range"
                },
                {
                    title: "Глубина, мм:",
                    data: "y_range"
                },
                {
                    title: "Высота, мм:",
                    data: "height"
                },
                {
                    title: "Количество проходов:",
                    data: "repeats_count"
                },
                {
                    title: "Скорость, %:",
                    data: "speed_factor"
                }
            ]
            delegate: Rectangle {
                id: item
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                color: Assets.Style.colorBackground
                height: 60
                radius: 5
                RowLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    Delegates.SettingsLabel {
                        implicitWidth: item.width / 2 - 20
                        text: modelData.title
                    }
                    Delegates.SettingsInput {
                        title: modelData.title
                        implicitWidth: item.width / 2 - 20
                        text: processSettings[modelData.data]
                        onTextChanged: {
                            processSettings[modelData.data] = text
                        }
                    }
                }
            }
        }

    }

    DelayButtonExt {
        id: btnStart
        color: "forestgreen"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20


        implicitHeight: 60
        Layout.fillWidth: true
        keepChecked: false
        text: "СТАРТ"
        font.pixelSize: 24

        onActivated: {
            appController.operatorModeController.setProcessParameters(root.processSettings)
            appController.operatorModeController.startTreater();
        }

    }
}
