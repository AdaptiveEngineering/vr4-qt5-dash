import QtQuick 2.2

Item {
    property bool on: false
    property string onColor
    property string offColor

    function paintIcon(ctx, color) {
        ctx.reset();
        ctx.lineWidth = 4;
        ctx.fillStyle = color;
        ctx.strokeStyle = color === "transparent" ? "transparent" : "black";

        ctx.beginPath();
        ctx.moveTo(0, 0.1 * height);
        ctx.lineTo(0, 0.9 * height);
        ctx.lineTo(width, 0.9 * height);
        ctx.lineTo(width, 0.1 * height);
        ctx.lineTo(0, 0.1 * height);
        ctx.fill();

        ctx.beginPath();
        ctx.arc(0.62 * width, 0.5 * height, width * 0.25, -(Math.PI / 2), (Math.PI / 2));
        ctx.stroke();

        ctx.beginPath();
        ctx.arc(1.30 * width, 0.5 * height, width * 0.75, (Math.PI / 2) + (Math.PI / 2.65) , (3 * Math.PI / 2) - (Math.PI / 2.65));
        ctx.stroke();

        ctx.lineWidth = 3;
        ctx.beginPath();
        ctx.moveTo(0.45 * width, 0.3 * height);
        ctx.lineTo(0.1 * width, 0.3 * height);
        ctx.moveTo(0.45 * width, 0.4 * height);
        ctx.lineTo(0.1 * width, 0.4 * height);
        ctx.moveTo(0.45 * width, 0.5 * height);
        ctx.lineTo(0.1 * width, 0.5 * height);
        ctx.moveTo(0.45 * width, 0.6 * height);
        ctx.lineTo(0.1 * width, 0.6 * height);
        ctx.moveTo(0.45 * width, 0.7 * height);
        ctx.lineTo(0.1 * width, 0.7 * height);
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
