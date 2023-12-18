import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0

StyleSmallGauge {
    id: fuelGauge

    tickmarkLabel: null
    tickmarkStepSize: 25
    minorTickmarkCount: 4
    minimumValueAngle: 90 + 45
    maximumValueAngle: 90 - 45
    inverted: true

    property string icon: "qrc:/images/fuel-icon.png"
    property string iconColor: "white"
    property string minValueLabel: "E"
    property string maxValueLabel: "F"

    background: Item {
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();
                paintBackground(ctx);
            }
        }
        Image {
            id: fuelIcon
            source: icon
            anchors.bottom: parent.bottom
            anchors.bottomMargin: toPixels(0.125)
            anchors.horizontalCenter: parent.right
            width: toPixels(0.2)
            height: width
            fillMode: Image.PreserveAspectFit
        }
        ColorOverlay {
            anchors.fill: fuelIcon
            source: fuelIcon
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
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 50
        }
        Text {
            text: maxValueLabel
            color: "white"
            font.pixelSize: toPixels(0.25)
            font.italic: true
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 50
        }
    }
}
