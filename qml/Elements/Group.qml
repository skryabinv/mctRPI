import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import "../Assets" as Assets

Item {
    id: root
    property alias title: title.text
    property alias spacing: row.spacing
    property var model: []
    default property Component delegate: ({})
    Text {
        id: title
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 5        
        color: Assets.Style.colorTextForeground
        font.pixelSize: 18
//        font.family: Assets.Style.fontMontserrat
    }    
    Rectangle {
        id: bg
        width: parent.width
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 5
        // border.color: Assets.Style.colorTextBorder
        color: Assets.Style.colorBackground
        radius: 5        
        Row {
            id: row
            anchors.centerIn: parent
            spacing: 20
            Repeater {
                model: root.model
                delegate: root.delegate
            }
        }

    }           
}
