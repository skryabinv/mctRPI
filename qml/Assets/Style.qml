pragma Singleton
import QtQuick 2.0

Item {
    readonly property color colorBackground: "#353637"
    readonly property color colorTextBackground: "#0067d5"
    readonly property color colorDirtyTextBackground: "#d52723"
    readonly property color colorTextForeground: "white"
    readonly property color colorSettingsSection: "darkgray"
    readonly property color colorTextBorder: "lightsteelblue"
    property alias fontAwesome: fontAwesomeLoader.name

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/fonts/fontawesome.ttf"
    }
}

