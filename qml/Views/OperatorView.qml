import QtQuick 2.12
import "../Elements" as Elems
import "../Assets" as Assets

Item {
    id: root

    Elems.OperatorParametersPanel {
        id: surfaceParametersPanel
        anchors.top: parent.top
        anchors.left: root.left
        anchors.bottom: root.bottom
    }

    Elems.OperatorControlsPanel {
        id: statusPanel
        anchors.left: surfaceParametersPanel.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

    }

}
