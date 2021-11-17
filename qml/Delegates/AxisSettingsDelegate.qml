import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    property string axisName: ""
    property alias checked: titleDelegate.checked

    property alias valueLimitLow: limitLow.text
    property alias valueLimitHigh: limitHigh.text
    property alias valueDistForSteps: distForSteps.text
    property alias valueStepsForDist: stepsForDist.text
    property alias valueSpeed: speed.text
    property alias valueTimeToSpeed: timeToSpeed.text
    //property alias valueHomeForwardSpeed:
    //property alias valueHomeBackwardSpeed:
    property alias valuePortStep: portStep.text
    property alias valuePortDir: portDir.text
    property alias valuePortHome: portHome.text


    implicitHeight: titleDelegate.implicitHeight + (titleDelegate.checked ? content.implicitHeight : 0)
    SettingsDelegate {
        id: titleDelegate
        anchors.left: root.left
        anchors.right:  root.right
        title: "Ось " + axisName
    }

    GridLayout {
        id: content
        anchors.top: titleDelegate.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 5
        rowSpacing: 5

        visible: root.checked
        columns: 4

        // Математические ограничения

        SettingsLabel {
            text: "Мин. значение, мм:"            
        }

        SettingsInput {
            id: limitLow
            text: appController.settingsModeController.getLimitLow(axisName)
        }

        SettingsLabel {            
            text: "Макс. значение, мм:"
        }

        SettingsInput {
            id: limitHigh
            text: appController.settingsModeController.getLimitHigh(axisName)
        }

        // Коэффициент передачи

        SettingsLabel {
            text: "Перемещение, мкм:"
        }

        SettingsInput {
            id: distForSteps
            text: appController.settingsModeController.getDistForSteps(axisName)
        }

        SettingsLabel {
            text: "Перемещение, шагов:"
        }

        SettingsInput {
            id: stepsForDist
            text: appController.settingsModeController.getStepsForDist(axisName)
        }

        // Скорость

        SettingsLabel {
            text: "Макс. скорость, см/мин:"
        }

        SettingsInput {
            id: speed
            text: appController.settingsModeController.getSpeed(axisName)
        }

        SettingsLabel {
            text: "Время набора скорости, мс:"
        }

        SettingsInput {
            id: timeToSpeed
            text: appController.settingsModeController.getTimeToSpeed(axisName)
        }

        SettingsLabel {
            text: "Скорость HOME вперед, cм/мин:"
        }

        SettingsInput {
            id: speedHomeForward
            text: "2"
        }

        SettingsLabel {
            text: "Скорость HOME назад, cм/мин:"
        }

        SettingsInput {
            id: speedHomeBackward
            text: "3"
        }

        // Порт ввода-вывода

        SettingsLabel {
            text: "Порт STEP:"
        }

        SettingsInput {
            id: portStep
            text: "1"
        }

        SettingsLabel {            
            text: "Порт DIR:"
        }

        SettingsInput {
            id: portDir
            text: "2"
        }

        SettingsLabel {
            text: "Порт HOME:"
        }

        SettingsInput {
            id: portHome
            text: "3"
        }        

        // Включить дополнительную ось

    }    

}

