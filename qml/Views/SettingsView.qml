import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0
import "../Delegates" as DLG
import "../Assets" as Assets

Rectangle {
    id: root
    color: Assets.Style.colorBackground

    ListView {
        id: listView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: panel.top
        spacing: 15

        ListModel {
            id: listModel
            ListElement { type: "X" }
            ListElement { type: "Y" }
            ListElement { type: "Z" }
            ListElement { type: "board" }
        }

        DelegateChooser {
            id: chooser
            role: "type"
            DelegateChoice { roleValue: "X"; delegate:
                    DLG.AxisSettingsDelegate {
                    id: xSettingsDelegate
                    axisName: "X"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "Y"; delegate:
                    DLG.AxisSettingsDelegate {
                    id: ySettingsDelegate
                    axisName: "Y"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "Z"; delegate:
                    DLG.AxisSettingsDelegate {
                    id: zSettingsDelegate
                    axisName: "Z"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "board"; delegate:
                    DLG.BoardSettingsDelegate {
                    id: boardSettingsDelegate
                    width: listView.width
                }
            }
        }
        model: listModel
        delegate: chooser

    }

    // Панель управления

    Rectangle {
        id: panel
        color: "black"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 60

        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: false
        }

        Row {

            spacing: 40

            Text {
                font.family: Assets.Style.fontAwesome
                font.pixelSize: 36
                text: "\uf057"
                color: "red"
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                font.family: Assets.Style.fontAwesome
                font.pixelSize: 36
                text: "\uf058"
                color: "green"
                verticalAlignment: Text.AlignVCenter
            }

            anchors.rightMargin: spacing
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

        }


    }


}
