import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

StyleMainGauge {
    id: speedometer
    labelStepSize: 20

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
            width: 127
            height: 65
            radius: 7.5
            color: "black"
            border.color: "#2f2f2f"
            border.width: 2

            Text {
                id: speedTextGhost
                font.pixelSize: speedometer.toPixels(0.2)
                font.family: "Segment7"
                font.italic: true
                text: "888"
                color: "#171715"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 5
            }

            Text {
                id: speedText
                font.pixelSize: speedometer.toPixels(0.2)
                font.family: "Segment7"
                font.italic: true
                text:
                    control.value.toFixed(0) < 10 ?
                        "  " + control.value.toFixed(0) :
                        control.value.toFixed(0) < 100 ?
                            " " + control.value.toFixed(0) :
                            control.value.toFixed(0)
                color: "#ccccbb"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 5
            }
        }
        Text {
            text: "km/h"
            color: "white"
            font.pixelSize: speedometer.toPixels(0.1)
            font.italic: true
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 195
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
