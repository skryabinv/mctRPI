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
        anchors.fill: parent
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
                    axisName: "Y"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "Z"; delegate:
                    DLG.AxisSettingsDelegate {
                    axisName: "Z"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "board"; delegate:
                    DLG.BoardSettingsDelegate {
                    width: listView.width
                }
            }
        }
        model: listModel
        delegate: chooser

    }


}
