import QtQuick 2.0
import "../Assets" as Assets

Item {
    property alias text: content.text
    implicitWidth: content.width
    implicitHeight: content.height
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackground
        Text {
            anchors.centerIn: parent
            id: content
            font.pixelSize: 22
            color: Assets.Style.colorTextForeground
        }
    }
}
