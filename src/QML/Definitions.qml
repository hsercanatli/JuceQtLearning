import QtQuick

QtObject {
    readonly property int windowWidth: 200
    readonly property int windowHeight: 350

    // colors
    readonly property color colorGeneralBackground: "#1D1D1D"
    readonly property color colorCheckedText: "#1c8fdf"
    readonly property color colorParameterText: "#7D7D7D"
    readonly property color colorDropShadow: "#80000000"
    readonly property color colorGlow: "#ff0000"

    // Knob
    readonly property color colorOutherInnerBorderChecked: "#1c8fdf"
    readonly property color colorKnobDefaultGradientStart: "#333333"
    readonly property color colorKnobDefaultGradientMid: "#2D2D2D"
    readonly property color colorKnobDefaultGradientEnd: "#282828"
    readonly property color colorKnobPressedGradientStart: "white"
    readonly property color colorKnobPressedGradientMid: "#2D2D2D"
    readonly property color colorKnobPressedGradientEnd: "black"
}
