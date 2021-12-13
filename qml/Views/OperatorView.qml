import QtQuick 2.12
import "../Elements" as Elems
import "../Assets" as Assets

Item {
    id: root

    Elems.OperatorControlsPanel {
        id: statusPanel        
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

    }

    Elems.OperatorParametersPanel {
        id: surfaceParametersPanel
        processSettings: appController.operatorModeController.getProcessParameters()
        anchors.left: statusPanel.right
        anchors.top: parent.top
        anchors.right: root.right
        anchors.bottom: root.bottom
    }

}
