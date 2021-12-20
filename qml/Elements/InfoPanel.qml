import QtQuick 2.12
import "../Assets" as Assets

Item {
    id: root
    property int modeHomeX: boardController.isHomingDone("X") ? InfoSymbol.Modes.Active : InfoSymbol.Modes.Alert
    property int modeHomeY: boardController.isHomingDone("Y") ? InfoSymbol.Modes.Active : InfoSymbol.Modes.Alert
    property int modeHomeZ: boardController.isHomingDone("Z") ? InfoSymbol.Modes.Active : InfoSymbol.Modes.Alert
    property int modePlasma: boardController.getOutputState() ? InfoSymbol.Modes.Active : InfoSymbol.Modes.Inactive
    property int modeBusy: boardController.isBusy() ? InfoSymbol.Modes.Active : InfoSymbol.Modes.Inactive
//    implicitWidth: row.width
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackgroundLight
        radius: 5
        Row {                        
            id: row
            anchors.centerIn: parent
            spacing: 24

            Repeater {
                anchors.fill: parent
                model: [
                    {  text: "\uf015",  mode: modeHomeX },
                    {  text: "\uf015",  mode: modeHomeY },
                    {  text: "\uf015",  mode: modeHomeZ },
                    {  text: "\uf0e7",  mode: modePlasma },
                    {  text: "\uf1da",  mode: modeBusy },
                ]
                InfoSymbol {
                    text: modelData.text
                    mode: modelData.mode
                }
            }
        }
    }

    Connections {
        target: boardController
        function onTaskStarted() {
            modeBusy = InfoSymbol.Modes.Active
        }

        function onTaskFinished(canceled) {
            modeBusy = InfoSymbol.Modes.Inactive
        }

        function onCoronaStateChanged(value) {
            if(value) {
                modePlasma = InfoSymbol.Modes.Active
            } else {
                modePlasma = InfoSymbol.Modes.Inactive
            }
        }

        function onAxesHomingDone(axes) {
            if(axes.includes("X")) {
                modeHomeX = InfoSymbol.Modes.Active
            }
            if(axes.includes("Y")) {
                modeHomeY = InfoSymbol.Modes.Active
            }
            if(axes.includes("Z")) {
                modeHomeZ = InfoSymbol.Modes.Active
            }
        }
    }

    Component.onCompleted:  {
        console.log("completed", boardController.isHomingDone("X"), modeHomeX)

    }
}
