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

}
