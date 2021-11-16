import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Assets" as Assets

Item {
    id: root
    Rectangle {
        anchors.fill: parent
        Row {
            anchors.centerIn: parent
            spacing: 20

            // Кнопка режима оператор
            Loader {
                id: loaderOperatorMode
                sourceComponent: btn
                onLoaded: item.text = appController.operatorModeController.description
            }
            Connections {
                target: loaderOperatorMode.item
                function onClicked() {
                    appController.modeOperatorActivated()
                }
            }

            // Кнопка ручного режима
            Loader {
                id: loaderManualMode
                sourceComponent: btn
                onLoaded: item.text = appController.manualModeController.description
            }
            Connections {
                target: loaderManualMode.item
                function onClicked() {
                    appController.modeManualActivated()
                }
            }

            // Кнопка настроек
            Loader {
                id: loaderSettings
                sourceComponent: btn
                onLoaded: item.text = appController.settingsModeController.descritpion
            }
            Connections {
                target: loaderSettings.item
                function onClicked() {
                    appController.modeSettingsActivated()
                }
            }

        }
        color: Assets.Style.colorBackground
    }

    Component {
        id: btn
        Rectangle {
            id: rect
            signal clicked;
            property alias text: text.text
            implicitWidth: 250
            implicitHeight: 250
            radius: 15
            border {
                width: 4
                color: "black"
            }
            Text {
                id: text
                anchors.centerIn: parent
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 36
                wrapMode: Text.WordWrap
                color: "white"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    rect.clicked();
                }
            }
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.lighter(Assets.Style.colorTextBackground) }
                GradientStop { position: 0.5; color: Assets.Style.colorTextBackground }
                GradientStop { position: 1.0; color: Qt.lighter(Assets.Style.colorTextBackground) }
            }
        }
    }

    RoundButton {
        width: 60
        height: width
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        text: "\u23FB"
        font.pixelSize: 28
        onPressAndHold: {
            console.log("Try to power off...")
        }
    }


}
