import QtQuick 2.0

Item {
    property alias text: content.text
    implicitWidth: content.width
    implicitHeight: content.height
    Rectangle {
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            id: content
            font.pixelSize: 22
            color: "#454647"
        }
    }
}
