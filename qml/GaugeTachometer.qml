import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

StyleMainGauge {
    id: tachometer
    tickmarkStepSize: 0.5
    minorTickmarkCount: 4
    labelStepSize: 1
    labelInset: toPixels(0.225)
    dangerZoneStart: 7

    background: Canvas {
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            paintBackground(ctx);
        }
        Rectangle {
            anchors.top: parent.top
            anchors.topMargin: 125
            anchors.horizontalCenter: parent.horizontalCenter
            width: 85
            height: 65
            radius: 7.5
            color: "black"
            border.color: "#2f2f2f"
            border.width: 2

            Text {
                id: rpmTextGhost
                font.pixelSize: tachometer.toPixels(0.2)
                font.family: "Segment7"
                font.italic: true
                text: "8.8"
                color: "#171715"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 5
            }

            Text {
                id: rpmText
                font.pixelSize: tachometer.toPixels(0.2)
                font.family: "Segment7"
                font.italic: true
                text: tachometerGauge.value.toFixed(1)
                color: "#ccccbb"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 5
            }
        }
        Text {
            text: "x1000r/min"
            color: "white"
            font.pixelSize: tachometer.toPixels(0.1)
            font.italic: true
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 195
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
