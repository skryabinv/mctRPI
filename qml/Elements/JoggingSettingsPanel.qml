import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets


Item {
    implicitHeight: 150
    implicitWidth: 100
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackground
        radius: 5
    }

    GridLayout {
        anchors.centerIn: parent
        columns: 2

        Label {
            text: "Перемещать дискретно:"
            font.pixelSize: 18
            color: "white"
        }

        Switch {

        }

        Label {
            text: "Шаг, мм: "
            font.pixelSize: 18
            color: "white"
        }

        ComboBox {
            model: [0.1, 0.25, 0.5, 1.0, 2.5, 5.0, 10.0]
        }

        Label {
            text: "Скорость, %: "
            font.pixelSize: 18
            color: "white"
        }

        Slider {
            id: sliderSpeed
            from: 10
            to: 100
            value: 50
        }

    }

}
