import QtQuick 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    property alias checked: titleDelegate.checked
    property var settings: ({})

    implicitHeight: titleDelegate.height
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
            text: "Начальная позиция X, мм:"
        }

        SettingsInput {
            id: initialPosX
            text: settings.initial_pos_x.toFixed(1)
            onTextChanged: settings.initial_pos_x = parseFloat(text)
        }

        SettingsLabel {
            text: "Начальная позиция Y, мм:"
        }

        SettingsInput {
            id: initialPosY
            text: settings.initial_pos_y.toFixed(1)
            onTextChanged: settings.initial_pos_y = parseFloat(text)
        }

        SettingsLabel {
            text: "Высота по умолчанию, мм:"
        }

        SettingsInput {
            id: height
            text: settings.height.toFixed(1)
            onTextChanged: settings.height = parseFloat(text)
        }


        SettingsLabel {
            text: "Ширина разряда, мм:"
        }

        SettingsInput {
            id: coronaWidth
            text: settings.corona_width.toFixed(1)
            onTextChanged: settings.corona_width = parseFloat(text)

        }

        SettingsLabel {
            text: "Порт разряда:"
        }

        SettingsInput {
            id: flashPort
            text: settings.corona_pin
            onTextChanged: settings.corona_pin = parseInt(text)
        }

    }

}


