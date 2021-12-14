import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0
import "../Delegates" as DLG
import "../Assets" as Assets

Rectangle {
    id: root
    implicitHeight: listView.implicitHeight
    color: Assets.Style.colorBackground

    property var settingsAxisX: appController.settingsModeController.getAxisSettings("X")
    property var settingsAxisY: appController.settingsModeController.getAxisSettings("Y")
    property var settingsAxisZ: appController.settingsModeController.getAxisSettings("Z")
    property var settingsTreater: appController.settingsModeController.getTreaterSettings()

    ListView {
        id: listView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: panel.top
        spacing: 15

        ListModel {
            id: listModel
            ListElement {
                type: "X"
            }
            ListElement {
                type: "Y"
            }
            ListElement {
                type: "Z"
            }
            ListElement {
                type: "board"
            }
        }

        DelegateChooser {
            id: chooser
            role: "type"
            DelegateChoice {
                roleValue: "X";
                delegate: DLG.AxisSettingsDelegate {
                    axisName: "X"
                    axisData: settingsAxisX
                    width: listView.width
                }
            }
            DelegateChoice {
                roleValue: "Y";
                delegate: DLG.AxisSettingsDelegate {
                    axisName: "Y"
                    axisData: settingsAxisY
                    width: listView.width
                }
            }
            DelegateChoice {
                roleValue: "Z";
                delegate: DLG.AxisSettingsDelegate {
                    axisName: "Z"
                    axisData: settingsAxisZ
                    width: listView.width
                }
            }
            DelegateChoice {
                roleValue: "board";
                delegate: DLG.BoardSettingsDelegate {
                    settings: settingsTreater
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
            anchors.rightMargin: spacing
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            Rectangle {
                id: bgClearChanges
                width: 150
                height: parent.height
                color: panel.color
                Text {
                    anchors.centerIn: parent
                    id: clearChanges
                    font.family: Assets.Style.fontAwesome
                    font.pixelSize: 36
                    text: "\uf057"
                    color: "red"
                    verticalAlignment: Text.AlignVCenter
                }
                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        bgClearChanges.color = Assets.Style.colorBackgroundLight
                    }
                    onReleased: {
                        bgClearChanges.color = panel.color
                    }
                }

            }

            Rectangle {
                id: bgSaveChanges
                width: 150
                height: parent.height
                color: panel.color
                Text {
                    anchors.centerIn: parent
                    id: saveChanges
                    font.family: Assets.Style.fontAwesome
                    font.pixelSize: 36
                    text: "\uf058"
                    color: "green"
                    verticalAlignment: Text.AlignVCenter
                }
                MouseArea {                    
                    anchors.fill: parent
                    onClicked: {
                        // Устанавливаем значения
                        // Сохраняем в файл
                        appController.settingsModeController.setAxisSettings("X", settingsAxisX)
                        appController.settingsModeController.setAxisSettings("Y", settingsAxisY)
                        appController.settingsModeController.setAxisSettings("Z", settingsAxisZ)
                        appController.settingsModeController.setTreaterSettings(settingsTreater)
                        appController.settingsModeController.save();
                    }
                    onPressed: {
                        bgSaveChanges.color = Assets.Style.colorBackgroundLight
                    }
                    onReleased: {
                        bgSaveChanges.color = panel.color
                    }
                }
            }

        }


    }


}
