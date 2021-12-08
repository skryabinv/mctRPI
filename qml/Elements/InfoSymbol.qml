import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Assets" as Assets

Text {
    enum Modes {
        Inactive = 0,
        Active = 1,
        Alert = 2
    }

    id: root
    property int mode: 0
    color: colorInactive
    property color colorInactive: "gray"
    property color colorActive: "limegreen"
    property color colorAlert: "red"
    property alias alertAnimationDuration: alertAnimation.duration
    font.pixelSize: 32
    font.family: Assets.Style.fontAwesome

    onModeChanged: {
        alertAnimation.stop()
        if(mode === InfoSymbol.Modes.Active) {
            color = colorActive
        } else if(mode === InfoSymbol.Modes.Inactive) {
            color = colorInactive
        } else {
            alertAnimation.start()
        }
    }

    ColorAnimation {
        id: alertAnimation
        target: root
        properties: "color"
        running: false
        loops: Animation.Infinite
        from: colorInactive
        to: colorAlert
        duration: 300
    }

}
