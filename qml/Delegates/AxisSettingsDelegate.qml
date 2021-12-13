import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import SettingsModeController 1.0

Item {
    id: root
    property string axisName: ""
    property var axisData: ({})
    property alias checked: titleDelegate.checked
    readonly property string axisTitle: "Ось " + axisName + ": "

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
            id: lblLimitLow
            text: "Мин. значение, мм:"            
        }

        SettingsInput {
            id: limitLow
            title: axisTitle + lblLimitLow.text
            text: axisData.limit_low.toFixed(1)
            onTextChanged: axisData.limit_low = parseFloat(text)
        }

        // Верхнее ограничение

        SettingsLabel {
            id: lblLimitHigh
            text: "Макс. значение, мм:"
        }

        SettingsInput {
            id: limitHigh
            title: axisTitle + lblLimitHigh.text
            text: axisData.limit_high.toFixed(1)
            onTextChanged: axisData.limit_high = parseFloat(text)
        }

        // Коэффициент передачи

        SettingsLabel {
            id: lblDistForSteps
            text: "Перемещение, мм:"
        }

        SettingsInput {
            id: distForSteps
            title: axisTitle + lblDistForSteps.text
            text: axisData.dist_for_steps.toFixed(1)
            onTextChanged: axisData.dist_for_steps = parseFloat(text)

        }

        SettingsLabel {
            id: lblStepsForDist
            text: "Перемещение, шагов:"
        }

        SettingsInput {
            id: stepsForDist
            title: axisTitle + lblStepsForDist.text
            text: axisData.steps_for_dist.toFixed(1)
            onTextChanged: axisData.steps_for_dist = parseFloat(text)
        }

        // Скорость

        SettingsLabel {
            id: lblSpeed
            text: "Макс. скорость, мм/мин:"
        }

        SettingsInput {
            id: speed
            title: axisTitle + lblSpeed.text
            text: axisData.speed.toFixed(1)
            onTextChanged: axisData.speed = parseFloat(text)
        }

        SettingsLabel {
            id: lblTimeToSpeed
            text: "Время набора скорости, мс:"
        }

        SettingsInput {
            id: timeToSpeed
            title: axisTitle + lblTimeToSpeed.text
            text: axisData.time_to_speed.toFixed(1)
            onTextChanged: axisData.time_to_speed = parseFloat(text)
        }

        SettingsLabel {
            id: lblSpeedHomeForward
            text: "Скорость HOME вперед, мм/мин:"
        }

        SettingsInput {
            id: speedHomeForward
            title: axisTitle + lblSpeedHomeForward.text
            text: axisData.speed_homing_forward.toFixed(1)
            onTextChanged: axisData.speed_homing_forward = parseFloat(text)
        }

        SettingsLabel {
            id: lblSpeedHomeBackward
            text: "Скорость HOME назад, мм/мин:"
        }

        SettingsInput {
            id: speedHomeBackward            
            title: axisTitle + lblSpeedHomeBackward.text
            text: axisData.speed_homing_backward.toFixed(1)
            onTextChanged: axisData.speed_homing_backward = parseFloat(text)
        }

        // Порт ввода-вывода

        SettingsLabel {
            id: lblPortStep
            text: "Порт STEP:"
        }

        SettingsInput {
            id: portStep
            title: axisTitle + lblPortStep.text
            text: axisData.port_step.join(".")
            onTextChanged: {
                if(text !== axisData.port_step.join(".")) {
                    axisData.port_step = text.split(".").map((item) => { return parseInt(item) })
                }
            }
        }

        SettingsLabel {
            id: lblPortDir
            text: "Порт DIR:"
        }

        SettingsInput {
            id: portDir
            title: axisTitle + lblPortDir.text
            text: axisData.port_dir.join(".")
            onTextChanged: {
                if(text !== axisData.port_dir.join(".")) {
                    axisData.port_dir = text.split(".").map((item) => { return parseInt(item) })
                }
            }
        }

        SettingsLabel {
            id: lblPortHome
            text: "Порт HOME:"
        }

        SettingsInput {
            id: portHome
            title: axisTitle + lblPortHome.text
            text: axisData.port_home.join(".")
            onTextChanged: {
                if(text !== axisData.port_home.join(".")) {
                    axisData.port_home = text.split(".").map((item) => { return parseInt(item) })
                }
            }
        }        

        SettingsLabel {            
            text: "Направление поиска Home:"
        }

        SettingsSwitch {
            textItems: [
                "+",
                "-"
            ]
            currentIndex: axisData.home_direction === "positive" ? 0 : 1
            onCurrentIndexChanged: {
                console.log(currentIndex)
                axisData.home_direction = ["positive", "negative"][currentIndex]
            }
        }

        SettingsLabel {
            id: lblPosHome
            text: "Координата HOME:"
        }

        SettingsInput {
            title: axisTitle + lblPosHome.text
            text: axisData.pos_home
            onTextChanged: {
                axisData.pos_home = parseFloat(text)
            }
        }

        SettingsLabel {
            id: lblPosSafe
            text: "Отъезд от HOME:"
        }

        SettingsInput {
            title: axisTitle + lblPosSafe.text
            text: axisData.pos_safe
            onTextChanged: {
                axisData.pos_safe = parseFloat(text)
            }
        }

    }    

}

