import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0

StyleSideGauge {
    id: fuelGauge

    tickmarkLabel: null
    tickmarkStepSize: 50
    minorTickmarkCount: 18
    minimumValueAngle: 270 - 45
    maximumValueAngle: 270 + 45
    inverted: false

    property string icon: "qrc:/images/temperature-icon.png"
    property string iconColor: "white"
    property string minValueLabel: "C"
    property string maxValueLabel: "H"

    function paintBackground(ctx) {
        ctx.beginPath();
        ctx.lineWidth = outerRadius * 0.02;
        ctx.strokeStyle = "white";
        ctx.arc(xCenter, yCenter, outerRadius - ctx.lineWidth / 2, degToRad(minimumValueAngle) - (Math.PI * 0.5025), degToRad(maximumValueAngle) - (Math.PI * 0.545), inverted);
        ctx.stroke();
    }

    tickmark: Rectangle {
        // visible: styleData.value % tickmarkStepSize == 0
        antialiasing: true
        implicitWidth: outerRadius * 0.04
        implicitHeight: (styleData.value / tickmarkStepSize) % 2 > 0 ? outerRadius * 0.075 : outerRadius * 0.1
        color: styleData.value >= 120 ? "red" : "white"
    }

    minorTickmark: Rectangle {
        // visible: styleData.value % tickmarkStepSize == 0
        antialiasing: true
        implicitWidth: outerRadius * 0.005
        implicitHeight: outerRadius * 0.03
        color: styleData.value >= 120 ? "red" : "white"
    }

    background: Item {
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();
                paintBackground(ctx);

                ctx.beginPath();
                ctx.moveTo(width * 0.16, height * 0.14);
                ctx.lineTo(width * 0.21, height * 0.19);
                ctx.lineTo(width * 0.16, height * 0.24);
                ctx.lineTo(width * 0.11, height * 0.19);
                ctx.closePath();
                ctx.fillStyle = "red";
                ctx.fill();
            }
        }
        Image {
            id: coolantIcon
            source: icon
            anchors.bottom: parent.bottom
            anchors.bottomMargin: toPixels(0.125)
            anchors.horizontalCenter: parent.left
            width: toPixels(0.2)
            height: width
            fillMode: Image.PreserveAspectFit
        }
        ColorOverlay {
            anchors.fill: coolantIcon
            source: coolantIcon
            color: iconColor
        }
        Text {
            text: minValueLabel
            color: "white"
            font.pixelSize: toPixels(0.25)
            font.italic: true
            font.bold: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 50
        }
        Text {
            text: maxValueLabel
            color: "white"
            font.pixelSize: toPixels(0.25)
            font.italic: true
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 50
        }
    }
}
