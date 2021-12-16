import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets

Item {
    id: root
    implicitWidth: 500
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackground
    }


    ColumnLayout {
        spacing: 20
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
            onActivated: {
                appController.operatorModeController.findHome()
            }
        }

        DelayButtonExt {
            id: btnHomePos
            Layout.fillWidth: true
            implicitHeight: btnHome.height
            keepChecked: false
            text: "В позицию X=0 Y=0"
            font.pixelSize: 24
            onActivated: {
                appController.operatorModeController.moveToZeroPos()
            }
        }

        DelayButtonExt {
            id: btnInitialPos
            implicitHeight: btnHome.implicitHeight
            Layout.fillWidth: true
            keepChecked: false
            text: "В начальную позицию"
            font.pixelSize: 24
            onActivated: {
                appController.operatorModeController.moveToInitialPos()
            }
        }

        CancelButton {
            id: btnCancel
            Layout.fillWidth: true
            implicitHeight: 60
            onPressed: {                
                appController.operatorModeController.cancel();
            }
        }
    }



}
