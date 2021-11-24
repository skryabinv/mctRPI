import QtQuick 2.12
import "../Assets" as Assets

Item {
    id: root
    property int modeHomeX: 0
    property int modeHomeY: 0
    property int modeHomeZ: 0
    property int modePlasma: 0
    property int modeBusy: 0
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackgroundLight
        border.width: 1        
        radius: 5
        Row {                        
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
}
