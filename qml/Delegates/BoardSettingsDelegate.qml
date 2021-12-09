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
            text: "0"
            onTextChanged: {

            }
        }

        SettingsLabel {
            text: "Начальная позиция Y, мм:"
        }

        SettingsInput {
            id: initialPosY
            text: "0"
            onTextChanged: {

            }
        }

        SettingsLabel {
            text: "Высота по умолчанию, мм:"
        }

        SettingsInput {
            id: height
            text: "0"
            onTextChanged: {

            }
        }

        SettingsLabel {
            text: "Порт разряда:"
        }

        SettingsInput {
            id: flashPort
            text: "0"
            onTextChanged: {

            }
        }

    }

}


