import QtQuick 2.2

Item {
    property bool on: false
    property string onColor
    property string offColor

    function paintIcon(ctx, color) {
        ctx.reset();
        ctx.lineWidth = 1;
        ctx.fillStyle = color;

        ctx.beginPath();
        ctx.moveTo(0.1 * width, height * 0.5);
        ctx.lineTo(0.6 * width, 0.0 * height);
        ctx.lineTo(0.6 * width, height * 0.28);
        ctx.lineTo(0.95 * width, height * 0.28);
        ctx.lineTo(0.95 * width, height * 0.72);
        ctx.lineTo(0.6 * width, height * 0.72);
        ctx.lineTo(0.6 * width, height);
        ctx.lineTo(0.1 * width, height * 0.5);

        ctx.fill();
    }
    Canvas {
        id: backgroundCanvas
        anchors.fill: parent
        onPaint: {
            paintIcon(getContext("2d"), offColor);
        }
    }
    Canvas {
        id: foregroundCanvas
        anchors.fill: parent
        visible: on
        onPaint: {
            paintIcon(getContext("2d"), onColor);
        }
    }
}
