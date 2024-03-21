import QtQuick 2.15


Item {
    id: toggleButton
    width: 170
    height: 100
    state: "OFF"

    states: [
        State {
            name: "OFF"
            PropertyChanges {
                target: indicator
                x: (background.height-indicator.height)/2
            }
            PropertyChanges {
                target: background
                color: "#E9E9EA"
            }
        },
        State {
            name: "ON"
            PropertyChanges {
                target: indicator
                x: background.width-indicator.width-(background.height-indicator.height)/2
            }
            PropertyChanges {
                target: background
                color: "#65C466"
            }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "*"
            PropertyAnimation {
                properties: "x"
                duration: 200
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
    ]

    Rectangle {
        id: background
        color: "#E9E9EA"
        radius: width/2
        border.width: 0
        anchors.fill: parent

        Rectangle {
            id: indicator
            x: (background.height-indicator.height)/2
            y: (background.height-indicator.height)/2
            width: 86/170 * toggleButton.width
            height: 86/100 * toggleButton.height
            color: "#ffffff"
            radius: width/2
            border.width: 0
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if (toggleButton.state === "OFF")
                    toggleButton.state = "ON";
                else
                    toggleButton.state = "OFF";
            }
        }
    }
}
