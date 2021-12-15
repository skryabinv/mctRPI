import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../Assets" as Assets

Item {
    id: root        
    signal accepted(string value)
    signal rejected()
    property string textData: ""    
    property bool isInteger: false
    readonly property var regExpFloat: /^\d+\.?\d{0,3}$/
    readonly property var regExpInt: /^\d+$/
    property alias title: titleText.text
    property double minValue: 0.0
    property double maxValue: 10000.0


    anchors.fill: parent

    // Прямоугольник фона (замылен, не пускает сообщения)
    Rectangle {
        anchors.fill: parent
        color: Assets.Style.colorBackground        
        opacity: 0.75
        // Для модальности
        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: false
            onPressAndHold: hide()
            pressAndHoldInterval: 50
        }
    }

    Rectangle {
        id: bg
        anchors.centerIn: parent
        color: "black"
        width: Math.max(keyboard.implicitWidth, titleText.implicitWidth) + 50
        height: keyboard.implicitHeight + 50

        MouseArea {
            anchors.fill: parent
        }

        Rectangle {
            id: titleRect
            height: titleText.implicitHeight + 10
            width: parent.width
            anchors.top: parent.top
            color: Assets.Style.colorTextBackground
            Text {
                id: titleText
                text: ""
                anchors.centerIn: parent
                color: Assets.Style.colorTextForeground
                font.pixelSize: 18
            }

        }

        GridLayout {
            id: keyboard
            anchors.top: titleRect.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 3
            columnSpacing: 10
            rowSpacing: 10

            // Поле текстового ввода

            Rectangle {
                id: inputArea
                width: str.width
                height: str.height
                color: Assets.Style.colorBackgroundLight
                border.color: Assets.Style.colorTextBorder
                radius: 5
                Layout.columnSpan: 3
                Text {
                    id: str
                    text: root.textData
                    height: 80
                    width: 240 + 2 * keyboard.columnSpacing
                    color: Assets.Style.colorTextForeground
                    font.pixelSize: 34
                    clip: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            // Клавиши

            Repeater {
                model: [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, "." ]
                Loader {
                    id: loader
                    sourceComponent: button
                    onLoaded: {
                        item.symbol = modelData
                        item.fontName = Assets.Style.fontAwesome
                    }
                    Connections {
                        target: loader.item
                        function onPressed(symbol) {                            
                            if(root.textData === "0") {
                                if(symbol !== "0" && symbol !== ".") root.textData = ""
                                else if(symbol === "0") return;
                            }
                            let tmp = root.textData + symbol                            
                            if(validate(tmp)) {
                                root.textData = tmp
                            }
                        }
                    }
                }
            }

            // Backspace

            Loader {
                id: loaderBackspace
                Layout.row: 4
                Layout.column: 2
                sourceComponent: button
                onLoaded: {
                    item.symbol = "\uf55a"
                    item.fontName = Assets.Style.fontAwesome
                }
                Connections {
                    target: loaderBackspace.item
                    function onPressed(symbol) {
                        let len = root.textData.length
                        if(len > 0) {
                            root.textData = (root.textData.substring(0, len - 1))
                        }
                    }
                }
            }

            // Кнопка Ok

            Loader {
                id: loaderOk
                Layout.row: 5
                Layout.column: 0
                Layout.columnSpan: 2
                Layout.fillWidth: true
                sourceComponent: button
                onLoaded: {
                    item.symbol = "\uf00c"
                    item.fontName = Assets.Style.fontAwesome
                }
                Connections {
                    target: loaderOk.item
                    function onPressed(symbol) {
                        hide()
                        if(root.textData.length > 0 && validate(root.textData) && parseFloat(root.textData) >= minValue) {
                            root.textData = parseFloat(root.textData)
                            accepted(root.textData)
                        }
                    }
                }
            }

            // Кнопка "Отмена"

            Loader {
                id: loaderCancel
                Layout.row: 5
                Layout.column: 2
                sourceComponent: button
                onLoaded: {
                    item.symbol = "\uf00d"
                    item.fontName = Assets.Style.fontAwesome
                }
                Connections {
                    target: loaderCancel.item
                    function onPressed(symbol) {
                        hide()
                        rejected()
                    }
                }
            }
        }
    }


    Component.onCompleted:  {
        let obj = root
        let rootObject = null
        while(obj) {
            rootObject = obj
            obj = obj.parent
        }
        root.parent = rootObject
        root.visible = false
    }

    // Кнопка
    Component {
        id: button
        Rectangle {
            id: btn
            signal pressed(string symbol)
            property string symbol: ""
            property alias fontName: text.font.family
            implicitWidth: 80;
            implicitHeight: 80
            color: mouseArea.pressed ? Qt.lighter(Assets.Style.colorTextBackground) : Assets.Style.colorTextBackground
            radius: 5
            Text {
                id: text
                color: Assets.Style.colorTextForeground
                anchors.centerIn: parent
                text: symbol
                font.pixelSize: 20
            }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: btn.pressed(symbol)
            }
        }

    }

    function show() {
        root.textData = ""
        visible = true
    }

    function hide() {
        visible = false
    }   

    function validate(value) {        
        const test = isInteger ? regExpInt.test(value) : regExpFloat.test(value)
        return test && value <= maxValue
    }

}
