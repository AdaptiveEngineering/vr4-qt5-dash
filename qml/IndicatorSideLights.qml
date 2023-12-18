import QtQuick 2.2

Item {
    property bool on: false
    property string onColor
    property string offColor

    function paintIcon(ctx, color) {
        ctx.reset();
        ctx.lineWidth = 4;
        ctx.strokeStyle = color;

        ctx.beginPath();
        ctx.arc(0.62 * width, 0.5 * height, width * 0.33, -(Math.PI / 2), (Math.PI / 2));
        ctx.stroke();

        ctx.beginPath();
        ctx.arc(1.5 * width, 0.5 * height, width * 0.95, (Math.PI / 2) + (Math.PI / 2.65) , (3 * Math.PI / 2) - (Math.PI / 2.65));
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(0.4 * width, 0.35 * height);
        ctx.lineTo(0.04 * width, 0.15 * height);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(0.4 * width, 0.5 * height);
        ctx.lineTo(0.04 * width, 0.5 * height);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(0.4 * width, 0.65 * height);
        ctx.lineTo(0.04 * width, 0.85 * height);
        ctx.stroke();

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
