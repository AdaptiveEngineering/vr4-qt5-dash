import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

CircularGaugeStyle {
    tickmarkInset: toPixels(0.01)
    minorTickmarkInset: toPixels(0.05)
    labelInset: toPixels(0.25)

    property real xCenter: outerRadius
    property real yCenter: outerRadius
    property real needleLength: outerRadius - tickmarkInset * 1.25
    property real needleTipWidth: toPixels(0.03)
    property real needleBaseWidth: toPixels(0.06)
    property bool inverted: false

    function toPixels(percentage) {
        return percentage * outerRadius;
    }

    function degToRad(degrees) {
        return degrees * (Math.PI / 180);
    }

    function radToDeg(radians) {
        return radians * (180 / Math.PI);
    }

    function paintBackground(ctx) {
        ctx.beginPath();
        ctx.lineWidth = outerRadius * 0.02;
        ctx.strokeStyle = "white";
        ctx.arc(xCenter, yCenter, outerRadius - ctx.lineWidth / 2, degToRad(minimumValueAngle) - (Math.PI * 0.495), degToRad(maximumValueAngle) - (Math.PI * 0.505), inverted);
        ctx.stroke();
    }

    tickmark: Rectangle {
        // visible: styleData.value % tickmarkStepSize == 0
        antialiasing: true
        implicitWidth: outerRadius * 0.04
        implicitHeight: (styleData.value / tickmarkStepSize) % 2 > 0 ? outerRadius * 0.075 : outerRadius * 0.1
        color: "white"
    }

    minorTickmark: Rectangle {
        // visible: styleData.value % tickmarkStepSize == 0
        antialiasing: true
        implicitWidth: outerRadius * 0.005
        implicitHeight: outerRadius * 0.03
        color: "white"
    }

    tickmarkLabel: Text {
        font.pixelSize: Math.max(6, outerRadius * 0.15)
        font.italic: true
        font.weight: Font.Black
        style: Text.Outline
        styleColor: "#222"
        text: styleData.value + "  "
        color: "white"
        antialiasing: true
    }

    needle: Canvas {
        implicitWidth: needleBaseWidth
        implicitHeight: needleLength

        property real xCenter: width / 2
        property real yCenter: height / 2

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            ctx.beginPath();
            ctx.moveTo(xCenter, height);
            ctx.lineTo(xCenter - needleBaseWidth / 2, height);
            ctx.lineTo(xCenter - needleTipWidth / 2, 0);
            ctx.lineTo(xCenter + needleTipWidth / 2, 0);
            ctx.lineTo(xCenter + needleBaseWidth / 2, height);
            ctx.closePath();
            ctx.fillStyle = "red";
            ctx.fill();
        }
    }

    foreground: null
}
