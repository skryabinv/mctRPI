import QtQuick 2.0
import "../Elements" as Elem
import "../Assets" as Assets

Item {
    id: root

    Elem.ManualControlPanel {
        id: controlPanel
        anchors.left: parent.left
        anchors.right: axesPanel.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Elem.AxesPanel {
        id: axesPanel
        width: 400
        anchors.top:  parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom


        Elem.CancelButton {
            id: cancelBtn
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 20
            height: 60
            onPressed: {
                appController.manualModeController.cancel()
            }
        }

        Elem.DelayButtonExt {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: cancelBtn.top
            anchors.margins: 20
            height: 60
            delay: 2000
            text: checked ? "Выключить разряд" : "Включить разряд"
            font.pixelSize: 28
            onActivated: {
                console.log("Plazma")
            }
        }

    }

}
