import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
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

        // Нижнее ограничение

        SettingsLabel {
            text: "Мин. значение, мм:"            
        }

        SettingsInput {
            id: limitLow
            text: axisData.limit_low.toFixed(1)
            onTextChanged: axisData.limit_low = parseFloat(text)
        }

        // Верхнее ограничение

        SettingsLabel {            
            text: "Макс. значение, мм:"
        }

        SettingsInput {
            id: limitHigh
            text: axisData.limit_high.toFixed(1)
            onTextChanged: axisData.limit_high = parseFloat(text)
        }

        // Коэффициент передачи

        SettingsLabel {
            text: "Перемещение, мм:"
        }

        SettingsInput {
            id: distForSteps
            text: axisData.dist_for_steps.toFixed(1)
            onTextChanged: axisData.dist_for_steps = parseFloat(text)

        }

        SettingsLabel {
            text: "Перемещение, шагов:"
        }

        SettingsInput {
            id: stepsForDist
            text: axisData.steps_for_dist.toFixed(1)
            onTextChanged: axisData.steps_for_dist = parseFloat(text)
        }

        // Скорость

        SettingsLabel {
            text: "Макс. скорость, мм/мин:"
        }

        SettingsInput {
            id: speed
            text: axisData.speed.toFixed(1)
            onTextChanged: axisData.speed = parseFloat(text)
        }

        SettingsLabel {
            text: "Время набора скорости, мс:"
        }

        SettingsInput {
            id: timeToSpeed
            text: axisData.time_to_speed.toFixed(1)
            onTextChanged: axisData.time_to_speed = parseFloat(text)
        }

        SettingsLabel {
            text: "Скорость HOME вперед, cм/мин:"
        }

        SettingsInput {
            id: speedHomeForward            
            text: axisData.speed_homing_forward.toFixed(1)
            onTextChanged: axisData.speed_homing_forward = parseFloat(text)
        }

        SettingsLabel {
            text: "Скорость HOME назад, cм/мин:"
        }

        SettingsInput {
            id: speedHomeBackward            
            text: axisData.speed_homing_backward.toFixed(1)
            onTextChanged: axisData.speed_homing_backward = parseFloat(text)
        }

        // Порт ввода-вывода

        SettingsLabel {
            text: "Порт STEP:"
        }

        SettingsInput {
            id: portStep
            text: axisData.port_step.join(".")
            onTextChanged: {
                if(text !== axisData.port_step.join(".")) {
                    axisData.port_step = text.split(".").map((item) => { return parseInt(item) })
                }
            }
        }

        SettingsLabel {            
            text: "Порт DIR:"
        }

        SettingsInput {
            id: portDir
            text: axisData.port_dir.join(".")
            onTextChanged: {
                if(text !== axisData.port_dir.join(".")) {
                    axisData.port_dir = text.split(".").map((item) => { return parseInt(item) })
                }
            }
        }

        SettingsLabel {
            text: "Порт HOME:"
        }

        SettingsInput {
            id: portHome
            text: axisData.port_home.join(".")
            onTextChanged: {
                if(text !== axisData.port_home.join(".")) {
                    axisData.port_home = text.split(".").map((item) => { return parseInt(item) })
                }
            }
        }        

    }    

}

