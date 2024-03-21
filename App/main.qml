import QtQuick
import QuteUIKit 1.0

Window {
    width: 600
    height: 600
    visible: true
    title: qsTr("Hello World")

    QuteCheckbox {
        anchors.centerIn: parent
        width: 100
        height: 100
    }

    StandardToggleButton {
        x: 100
        y: 100
        width: 170/2
        height: 100/2
    }
}
