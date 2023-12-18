import QtQuick 2.2

Item {
    property bool on: false
    property string onColor
    property string offColor

    function paintIcon(ctx, color) {
        ctx.reset();
        ctx.lineWidth = 1;
        ctx.strokeStyle = color;

        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(0, height);
        ctx.lineTo(width, height);
        ctx.lineTo(width, 0);
        ctx.lineTo(0, 0);
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
