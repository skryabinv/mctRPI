import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets
import "../Delegates" as Delegates

Item {
    id: root
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
        anchors.bottom: parent.bottom
        color: "transparent"
        radius: 5

        ListView {
            id: list
            spacing: 10
            anchors.fill: parent
            model: [
                "Ширина, мм:",
                "Глубина, мм:",
                "Высота, мм:",
                "Количество проходов:",
                "Скорость, %:"
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
                        text: modelData
                    }
                    Delegates.SettingsInput {
                        implicitWidth: item.width / 2 - 20
                        text: "100.0"
                    }
                }
            }
        }

    }
}
