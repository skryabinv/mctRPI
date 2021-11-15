import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0
import "../Delegates" as MyDelegates

Item {
    id: root

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
                    MyDelegates.AxisSettingsDelegate {
                    id: xSettingsDelegate
                    axisName: "X"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "Y"; delegate:
                    MyDelegates.AxisSettingsDelegate {
                    axisName: "Y"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "Z"; delegate:
                    MyDelegates.AxisSettingsDelegate {
                    axisName: "Z"
                    width: listView.width
                }
            }
            DelegateChoice { roleValue: "board"; delegate:
                    MyDelegates.BoardSettingsDelegate {
                    width: listView.width
                }
            }
        }
        model: listModel
        delegate: chooser

    }


}
