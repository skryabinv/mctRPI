import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    property string axisName: ""
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
            text: "123"
        }

        SettingsLabel {
            text: "Макс. значение, мм:"
        }

        SettingsInput {
            text: "321"
        }

        // Коэффициент передачи

        SettingsLabel {
            text: "Перемещение, мкм:"
        }

        SettingsInput {
            text: "124"
        }

        SettingsLabel {
            text: "Перемещение, шагов:"
        }

        SettingsInput {
            text: "765"
        }

        // Скорость

        SettingsLabel {
            text: "Макс. скорость, см/мин:"
        }

        SettingsInput {
            text: "150"
        }

        SettingsLabel {
            text: "Время набора скорости, мс:"
        }

        SettingsInput {
            text: "400"
        }

        // Порт ввода-вывода

        SettingsLabel {
            text: "Порт STEP:"
        }

        SettingsInput {
            text: "1"
        }

        SettingsLabel {
            text: "Порт DIR:"
        }

        SettingsInput {
            text: "2"
        }

        SettingsLabel {
            text: "Порт HOME:"
        }

        SettingsInput {
            text: "3"
        }

        // Включить дополнительную ось

    }    

}

