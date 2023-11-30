import QtQuick
import QtQuick.Controls
import QtQuick.Shapes

import "SharedFunctions.js" as SharedFunctions

Dial {
    id: control

    inputMode: Dial.Vertical
    background: Item {
        width: control.width
        height: control.height

        // Arc
        Canvas {
            anchors.fill: parent
            onPaint: {
                let ctx = getContext("2d")
                ctx.reset()

                const leftInnerPoint = SharedFunctions.calculateCirclePoint(130, internalId.innerRadius,
                    Qt.point(internalId.centreX, internalId.centreY))
                const leftOuterPoint = SharedFunctions.calculateCirclePoint(130, internalId.outerRadius,
                    Qt.point(internalId.centreX, internalId.centreY))
                const rightInnerPoint = SharedFunctions.calculateCirclePoint(50, internalId.innerRadius,
                    Qt.point(internalId.centreX, internalId.centreY))

                ctx.lineWidth = 1
                ctx.fillStyle = "#2D2D2D"
                ctx.beginPath()

                ctx.moveTo(leftInnerPoint.x, leftInnerPoint.y)
                ctx.lineTo(leftOuterPoint.x, leftOuterPoint.y)
                ctx.arc(internalId.centreX, internalId.centreY, internalId.outerRadius, Math.PI * 130 / 180, Math.PI * 50 / 180, false);
                ctx.lineTo(rightInnerPoint.x, rightInnerPoint.y)
                ctx.arc(internalId.centreX, internalId.centreY, internalId.innerRadius, Math.PI * 50 / 180, Math.PI * 130 / 180, true);

                ctx.fill()
            }
        }

        // Inner circle
        Rectangle {
            width: control.width / 2
            height: control.height / 2
            radius: width / 2

            x: (control.width - width) / 2
            y: (control.height - height) / 2

            border {
                width: 1
                color: "black"
            }

            Gradient {
                id: defaultGradientId
                GradientStop {
                    position: 0.0; color: definitions.colorKnobDefaultGradientStart
                }
                GradientStop {
                    position: 0.5; color: definitions.colorKnobDefaultGradientMid
                }
                GradientStop {
                    position: 1.0; color: definitions.colorKnobDefaultGradientEnd
                }
            }

            Gradient {
                id: pressedGradientId
                GradientStop {
                    position: 0.0; color: definitions.colorKnobPressedGradientStart
                }
                GradientStop {
                    position: 0.5; color: definitions.colorKnobPressedGradientMid
                }
                GradientStop {
                    position: 1.0; color: definitions.colorKnobPressedGradientEnd
                }
            }

            color: pressed ? definitions.colorOutherInnerBorderChecked : "transparent"
            Behavior on color {
                ColorAnimation {
                    duration: 150
                }
            }
            opacity: pressed ? 0.6 : 1
            Behavior on opacity {
                NumberAnimation {
                    duration: 150
                }
            }
            gradient: control.pressed ? undefined : defaultGradientId
        }
    }

    handle: Rectangle {
        id: handleItem
        x: control.background.width / 2 - width / 2
        y: control.background.height / 2 - height / 2
        width: 4
        height: internalId.outerRadius - internalId.innerRadius
        color: definitions.colorCheckedText
        antialiasing: true
        opacity: control.enabled ? 1 : 0.3
        transform: [
            Translate {
                y: -Math.min(control.background.width, control.background.height) * 0.4
            },
            Rotation {
                angle: control.angle
                origin.x: handleItem.width / 2
                origin.y: handleItem.height / 2
            }
        ]
    }

    QtObject {
        id: internalId

        readonly property real centreX: control.width / 2
        readonly property real centreY: control.height / 2
        readonly property real outerRadius: control.width / 2 - 2
        readonly property real curvePathWidth: outerRadius * 0.3
        readonly property real innerRadius: outerRadius - curvePathWidth
    }
}
