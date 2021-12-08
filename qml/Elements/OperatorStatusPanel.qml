import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets

Item {
    id: root
    implicitHeight: 80
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackground
    }

    RowLayout {
        spacing: 20
        anchors.verticalCenter: parent.verticalCenter

        DelayButtonExt {
            id: btnDelay
            Layout.leftMargin: 20
            implicitHeight: 60
            implicitWidth: 220
            keepChecked: false
            text: "Поиск HOME"
            font.pixelSize: 24
        }

        CancelButton {
            id: btnCancel
            implicitHeight: 60
            implicitWidth: btnDelay.width
        }
    }

    InfoPanel {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        implicitWidth: 300

    }

}
