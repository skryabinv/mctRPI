import QtQuick 2.12
import "../Elements" as Elems
import "../Assets" as Assets

Item {
    id: root

    Row {
        anchors.fill: parent

        Column {
            Elems.DelayButtonExt {
                keepChecked: false
                text: "\uf015"
                font.pixelSize: 24

                implicitWidth: 100
                implicitHeight: 100
            }

            Elems.DelayButtonExt {
                text: "\uf04c"
                font.pixelSize: 24

                implicitWidth: 100
                implicitHeight: 100
            }


        }

    }

}
