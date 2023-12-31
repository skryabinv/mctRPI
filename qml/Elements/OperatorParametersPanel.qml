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
                    data: "x_range",
                    min: 1,
                    max: 550,
                    integer: false
                },
                {
                    title: "Глубина, мм:",
                    data: "y_range",
                    min: 1,
                    max: 400,
                    integer: false
                },
                {
                    title: "Высота, мм:",
                    data: "height",
                    min: 1,
                    max: 300,
                    integer: false
                },
                {
                    title: "Количество проходов:",
                    data: "repeats_count",
                    min: 1,
                    max: 50,
                    integer: true
                },
                {
                    title: "Скорость, %:",
                    data: "speed_factor",
                    min: 5,
                    max: 100,
                    integer: true
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
                        minValue: modelData.min
                        maxValue: modelData.max
                        isInteger: modelData.integer
                        implicitWidth: item.width / 2 - 20
                        text: Number.isInteger(parseFloat(processSettings[modelData.data])) ? processSettings[modelData.data] : processSettings[modelData.data].toFixed(3)
                        onTextChanged: {
                            processSettings[modelData.data] = parseFloat(text)
                        }
                    }
                }
            }
        }

    }

    TreaterProgress {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: btnStart.top
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 20
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
