import QtQuick 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    property alias checked: titleDelegate.checked
    property var settings: ({})

    implicitHeight: titleDelegate.height + (titleDelegate.checked ? content.height + 20 : 0)
    SettingsDelegate {
        id: titleDelegate
        anchors.left: parent.left
        anchors.right: parent.right
        title: "Общие настройки"
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

        SettingsLabel {
            id: lblInitialPosX
            text: "Начальная позиция X, мм:"
        }

        SettingsInput {
            id: initialPosX
            title: lblInitialPosX.text
            text: settings.initial_pos_x.toFixed(1)
            onTextChanged: settings.initial_pos_x = parseFloat(text)
        }

        SettingsLabel {
            id: lblInitialPosY
            text: "Начальная позиция Y, мм:"
        }

        SettingsInput {
            id: initialPosY
            title: lblInitialPosY.text
            text: settings.initial_pos_y.toFixed(1)
            onTextChanged: settings.initial_pos_y = parseFloat(text)
        }

        SettingsLabel {
            id: lblHeight
            text: "Высота разряда, мм:"
        }

        SettingsInput {
            id: height
            title: lblHeight.text
            text: settings.height.toFixed(1)
            onTextChanged: settings.height = parseFloat(text)
        }


        SettingsLabel {
            id: lblWidth
            text: "Ширина разряда, мм:"
        }

        SettingsInput {
            id: coronaWidth
            title: lblWidth.text
            text: settings.corona_width.toFixed(1)
            onTextChanged: settings.corona_width = parseFloat(text)

        }

        SettingsLabel {
            id: lblPortEnable
            text: "Порт включения разряда:"
        }

        SettingsInput {
            id: portEnable
            title: lblPortEnable.text
            text: settings.corona_enable_pin
            onTextChanged: settings.corona_enable_pin = parseInt(text)
        }

        SettingsLabel {
            id: lblPortDisable
            text: "Порт выключения разряда:"
        }

        SettingsInput {
            id: flashPort
            title: lblPortDisable.text
            text: settings.corona_disable_pin
            onTextChanged: settings.corona_disable_pin = parseInt(text)
        }

        SettingsLabel {
            id: lblTreaterSpeedX
            text: "Скорость переезда X, %"
        }

        SettingsInput {
            id: treaterSpeedX
            title: lblTreaterSpeedX.text
            text: 100 * settings.corona_speed_x
            onTextChanged: settings.corona_speed_x = parseFloat(text) / 100.0
            minValue: 5
            maxValue: 100
            isInteger: true
        }

        SettingsLabel {
            id: lblTreaterSpeedY
            text: "Скорость переезда Z, %"
        }

        SettingsInput {
            id: treaterSpeedZ
            title: lblTreaterSpeedX.text
            text: 100 * settings.corona_speed_z
            onTextChanged: settings.corona_speed_z = parseFloat(text) / 100.0
            minValue: 5
            maxValue: 100
            isInteger: true
        }

        SettingsLabel {
            id: lblPortTimeout
            text: "Задержка вкл./выкл., мс:"
        }

        SettingsInput {
            id: portTimeOut
            title: lblPortTimeout.text
            text: settings.corona_ports_delay_ms
            onTextChanged: settings.corona_ports_delay_ms = parseInt(text)
        }
    }

}


