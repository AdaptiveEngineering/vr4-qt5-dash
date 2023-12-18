import QtQuick 2.2

Item {
    property bool on: false
    property string onColor
    property string offColor
    scale: -1

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
        ctx.moveTo(0.4 * width, 0.3 * height);
        ctx.lineTo(0.04 * width, 0.3 * height);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(0.4 * width, 0.5 * height);
        ctx.lineTo(0.04 * width, 0.5 * height);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(0.4 * width, 0.7 * height);
        ctx.lineTo(0.04 * width, 0.7 * height);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(0.19 * width, 0.17 * height);
        ctx.lineTo(0.25 * width, 0.32 * height);
        ctx.lineTo(0.21 * width, 0.41 * height);
        ctx.lineTo(0.21 * width, 0.48 * height);
        ctx.lineTo(0.25 * width, 0.58 * height);
        ctx.lineTo(0.25 * width, 0.68 * height);
        ctx.lineTo(0.19 * width, 0.84 * height);
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
