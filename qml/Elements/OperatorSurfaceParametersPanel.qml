import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets
import "../Delegates" as Delegates

Item {
    id: root
    implicitWidth: 524
    implicitHeight: list.height

    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackgroundLight
    }

    ListView {
        id: list
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        spacing: 10
        model: [
            "Ширина:",
            "Глубина:",
            "Высота"
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
