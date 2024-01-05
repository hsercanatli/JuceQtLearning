import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

import Sercan
import com.sercan.JuceQtLearning
import AudioComponents
import Utilities

Rectangle {
    id: window

    width: Definitions.windowWidth
    height: Definitions.windowHeight

    color: "black"

    Rectangle {
        id: background
        width: parent.width - radius
        height: parent.height - radius
        radius: 14
        anchors.centerIn: parent
        color: Definitions.colorGeneralBackground
    }

    InnerShadow {
        anchors.fill: background
        radius: 8.0
        samples: 16
        horizontalOffset: 2
        verticalOffset: 2
        color: "white"
        source: background
        opacity: 0.15
    }

    Text {
        id: paramLabelId

        width: window.width
        height: window.height * 0.25

        font.pixelSize: window.height * 0.09
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: Definitions.colorParameterText
        text: qsTr("Gain")
    }

    DropShadow {
        anchors.fill: paramLabelId
        horizontalOffset: 2
        verticalOffset: 2
        radius: 8.0
        color: Definitions.colorDropShadow
        source: paramLabelId
    }

    Knob {
        id: dial

        width: 100
        height: 100

        anchors {
            top: paramLabelId.bottom
            horizontalCenter: parent.horizontalCenter
        }

        from: GainModel.minGain
        to: GainModel.maxGain

        inputMode: Dial.Vertical
        onMoved: GainController.updateGain(dial.value)
    }

    DropShadow {
        anchors.fill: dial
        horizontalOffset: 4
        verticalOffset: 4
        radius: 8.0
        color: Definitions.colorDropShadow
        source: dial
    }

    Text {
        anchors.top: dial.bottom
        anchors.horizontalCenter: dial.horizontalCenter
        text: SharedFunctions.round(GainModel.gain, 2)
        font: monoSpacedFont
        color: "white"
    }

    Rectangle {
        id: led
        width: 20
        height: 20
        radius: height / 2
        anchors {
            horizontalCenter: button.horizontalCenter
            bottom: button.top
            bottomMargin: 10
        }
        color: GainModel.bypass ? "lightgray" : "red"
        border {
            width: 3
            color: "gray"
        }
    }

    InnerShadow {
        anchors.fill: led
        radius: 8.0
        samples: 16
        horizontalOffset: 3
        verticalOffset: 3
        color: "white"
        source: led
        opacity: 0.3
    }

    DropShadow {
        anchors.fill: led
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        color: Definitions.colorDropShadow
        source: led
    }

    Glow {
        id: glow
        anchors.fill: led
        radius: 8
        samples: 25
        spread: 0
        color: Qt.lighter(Definitions.colorGlow, 2)
        source: led
        visible: !GainModel.bypass
    }

    Rectangle {
        id: button
        width: 50
        height: 50
        radius: height / 2
        opacity: buttomMouseArea.pressed ? 0.05 : 0.3
        Behavior on opacity {
            NumberAnimation {
                duration: 50
            }
        }
        Image {
            id: knobImage
            anchors.fill: parent
            source: "qrc:/sercan.com/imports/AudioComponents/Images/button.png"
            clip: true
        }

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: parent.height * 0.1
        }

        MouseArea {
            id: buttomMouseArea
            anchors.fill: parent
            onClicked: GainController.updateBypass(!GainModel.bypass)
        }
    }

    DropShadow {
        anchors.fill: button
        horizontalOffset: 6
        verticalOffset: 6
        radius: 8.0
        color: "black"
        source: button
    }
}
