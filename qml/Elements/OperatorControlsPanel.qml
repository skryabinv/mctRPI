import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets

Item {
    id: root    
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackground
    }


    ColumnLayout {
        spacing: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        InfoPanel {
            Layout.fillWidth: true
            implicitHeight: 60
        }

        DelayButtonExt {
            id: btnHome
            Layout.fillWidth: true
            implicitHeight: 60            
            keepChecked: false
            text: "Поиск HOME"
            font.pixelSize: 24
        }

        DelayButtonExt {
            id: btnHomePos
            Layout.fillWidth: true
            implicitHeight: btnHome.height
            keepChecked: false
            text: "В позицию XY HOME"
            font.pixelSize: 24
        }

        DelayButtonExt {
            id: btnParkingZone
            implicitHeight: btnHome.implicitHeight
            Layout.fillWidth: true
            keepChecked: false
            text: "В начальную позицию"
            font.pixelSize: 24
        }

        CancelButton {
            id: btnCancel
            Layout.fillWidth: true
            implicitHeight: 60
        }
    }

    DelayButtonExt {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        id: btnStart
        implicitHeight: btnHome.implicitHeight
        Layout.fillWidth: true
        keepChecked: false
        text: "Пуск"
        font.pixelSize: 24
    }


}
