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
                    action: "homeSelectedAxis",
                    text: "Выбранная ось",
                },
                {
                    action: "homeAllAxes",
                    text: "Все оси",
                }
            ]

            DelayButtonExt {
                text: modelData.text
                keepChecked: false
                implicitWidth: 250
                implicitHeight: 40
                font.pixelSize: 18
                delay: 1000
                onActivated: {
                    switch(modelData.action) {
                    case "homeSelectedAxis": appController.manualModeController.homeSelectedAxis(); break;
                    case "homeAllAxes": appController.manualModeController.homeAllAxes(); break;
                    }
                }
            }
        }

        StepChooser {
            id: stepChooser
            Layout.fillWidth: true
            height: 80
            model: [0.0, 0.5, 1.0, 2.5, 5.0, 10.0, 25.0, 50.0]
            onStepValueChanged: {
                console.log(stepValue)
            }
        }

        SpeedChooser {
            id: speedChooser
            Layout.fillWidth: true
            height: 80
            sliderWidth: 560
            sliderHeight: 28
        }

        // Ручное перемещение
        Group {
            id: groupJogging
            Layout.fillWidth: true
            height: 120
            spacing: 40
            title: "Перемещение"
            model: [
                {
                    text: "\uf060",
                    dir: -1
                },
                {
                    text: "\uf061",
                    dir: 1
                }
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
                onPressedChanged: {
                    if(pressed) {
                        if(stepChooser.stepValue === 0.0) {
                            appController.manualModeController.jogStart(modelData.dir * speedChooser.speedValue, 0.0);
                        } else {
                            appController.manualModeController.jogStart(modelData.dir * speedChooser.speedValue, stepChooser.stepValue);
                        }
                    } else {
                        if(stepChooser.stepValue === 0.0) {
                            appController.manualModeController.jogStop()
                        }
                    }
                }

            }
        }

    }

}
