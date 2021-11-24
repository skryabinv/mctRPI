import QtQuick 2.0
import "../Elements" as Elem
import "../Assets" as Assets

Item {
    id: root

    Elem.ManualControlPanel {
        id: controlPanel
        anchors.left: parent.left
        anchors.right: axesBg.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Rectangle {
        id: axesBg
        anchors.top:  parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: Assets.Style.colorBackground
        width: 400

        Elem.InfoPanel {
            id: infoPanel
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            height: 50
            modeHomeX: Elem.InfoSymbol.Modes.Alert
            modeHomeY: Elem.InfoSymbol.Modes.Alert
            modeHomeZ: Elem.InfoSymbol.Modes.Alert
            modePlasma: Elem.InfoSymbol.Modes.Inactive
            modeBusy: Elem.InfoSymbol.Modes.Inactive
        }

        Elem.AxesPanel {
            id: axesPanel
            anchors.left: parent.left
            anchors.top: infoPanel.bottom
            anchors.right: parent.right
            height: 210
        }




        Elem.CancelButton {
            id: cancelBtn
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10
            height: 60
            onPressed: {
                appController.manualModeController.cancel()
            }
        }

        Elem.DelayButtonExt {
            id: delayBtn
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: cancelBtn.top
            anchors.margins: 10
            height: 60
            delay: 2000
            text: checked ? "Выключить разряд" : "Включить разряд"
            font.pixelSize: 28
            onClicked: {
                if(checked) {
                    infoPanel.modePlasma = Elem.InfoSymbol.Modes.Active
                    // Enavle plasma
                } else {
                    infoPanel.modePlasma = Elem.InfoSymbol.Modes.Inactive
                    // Disable plasma
                }
            }
        }

        Connections {
            target: appController.manualModeController
            function onTaskStarted() {
                infoPanel.modeBusy = Elem.InfoSymbol.Modes.Active
            }

            function onTaskFinished(canceled) {
                infoPanel.modeBusy = Elem.InfoSymbol.Modes.Inactive
            }
        }

    }

}
