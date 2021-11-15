import QtQuick 2.12

Item {
    id: root
    property alias checked: titleDelegate.checked
    implicitHeight: titleDelegate.height
    SettingsDelegate {
        id: titleDelegate
        anchors.left: parent.left
        anchors.right: parent.right
        title: "Общие настройки"
    }

}


