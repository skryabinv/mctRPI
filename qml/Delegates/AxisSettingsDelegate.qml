import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    // Имя оси
    property string axisName: ""
    property var axisData: ({})
    property alias checked: titleDelegate.checked

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
            input: axisData.limit_low
            onInputChanged: axisData.limit_low = input
        }

        SettingsLabel {            
            text: "Макс. значение, мм:"
        }

        SettingsInput {
            id: limitHigh
            input: axisData.limit_high
        }

        // Коэффициент передачи

        SettingsLabel {
            text: "Перемещение, мкм:"
        }

        SettingsInput {
            id: distForSteps
            input: axisData.dist_for_steps
        }

        SettingsLabel {
            text: "Перемещение, шагов:"
        }

        SettingsInput {
            id: stepsForDist
            input: axisData.steps_for_dist
        }

        // Скорость

        SettingsLabel {
            text: "Макс. скорость, см/мин:"
        }

        SettingsInput {
            id: speed
            input: axisData.speed
        }

        SettingsLabel {
            text: "Время набора скорости, мс:"
        }

        SettingsInput {
            id: timeToSpeed
            input: axisData.time_to_speed
            onInputChanged: axisData.time_to_speed = input
        }

        SettingsLabel {
            text: "Скорость HOME вперед, cм/мин:"
        }

        SettingsInput {
            id: speedHomeForward
            input: axisData.speed_homing_forward
        }

        SettingsLabel {
            text: "Скорость HOME назад, cм/мин:"
        }

        SettingsInput {
            id: speedHomeBackward
            input: axisData.speed_homing_backward
        }

        // Порт ввода-вывода

        SettingsLabel {
            text: "Порт STEP:"
        }

        SettingsInput {
            id: portStep
            input: axisData.port_step.join(".")
        }

        SettingsLabel {            
            text: "Порт DIR:"
        }

        SettingsInput {
            id: portDir
            input: axisData.port_dir.join(".")
        }

        SettingsLabel {
            text: "Порт HOME:"
        }

        SettingsInput {
            id: portHome
            input: axisData.port_home.join(".")
        }        

    }    

}

