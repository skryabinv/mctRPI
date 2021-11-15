import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Assets" as Assets

Item {
    property alias title: titleText.text
    property alias checked: arrow.checked
    implicitHeight: titleRect.height
    Rectangle {
        id: titleRect
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        implicitHeight: 50
        radius: 5
        Text {
            id: titleText
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 20
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 28
        }

        Text {
            id: arrow
            property bool checked: false
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 20
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 23
            text: checked ? "\u02C4" : "\u02C5"
            MouseArea {
                anchors.fill: parent
                onClicked: arrow.checked = !arrow.checked
            }

        }

        color: Assets.Style.colorSettingsSection
    }

}
