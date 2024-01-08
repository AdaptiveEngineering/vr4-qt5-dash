import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

StyleInsetGauge {
    id: boostgauge
    labelStepSize: 0.5
    tickmarkStepSize: 0.5

    background: Canvas {
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            paintBackground(ctx);
        }

        Text {
            text: "Boost"
            color: "white"
            font.pixelSize: 20
            font.italic: true
            font.bold: true
            anchors.top: parent.verticalCenter
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
