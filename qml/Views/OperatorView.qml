import QtQuick 2.12
import "../Elements" as Elems
import "../Assets" as Assets

Item {
    id: root

    Elems.OperatorStatusPanel {
        id: statusPanel
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

    }

    Elems.OperatorSurfaceParametersPanel {
        id: surfaceParametersPanel
        anchors.top: statusPanel.bottom
        anchors.left: root.left
        anchors.bottom: root.bottom
    }

    Elems.OperatorProcessingControlPanel {
        id: processingPanel
        anchors.left: surfaceParametersPanel.right
        anchors.top: statusPanel.bottom
        anchors.right: root.right
        anchors.bottom: root.bottom
    }


}
