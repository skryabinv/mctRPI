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
    }

}
