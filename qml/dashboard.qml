import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0

Window {
    id: root
    visible: true
    visibility: "FullScreen"
    width: Screen.width
    height: Screen.height

    color: "#000000"
    title: "VR-4 Dash"

    ValueSource {
        id: valueSource
    }

    property bool backgroundEnabled: false
    property int tripMode: 1
    property real odoReading: 0
    property real fuelLevel: 100
    property real coolantTemperature: 95
    property bool flashing: false
    property bool ayc3Bars: false
    property bool ayc2Bars: true
    property bool ayc1Bars: true
    property int aycStatus: 0
    property int cruiseStatus: 1
    property bool debugIcons: true

    // Delete this section when done
    Rectangle {
        id: backgroundImage
        anchors.centerIn: parent
        width: 1920
        height: 720
        color: "red"
        opacity: 0.5
        z: -1
        visible: backgroundEnabled

        Image {
            source: "qrc:/images/dashpreview2.png"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Timer {
        id: fastTimer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            flashing = !flashing
            odoReading += valueSource.kph * (0.000277778 / 2)
            fuelLevel -= ((valueSource.gear === "P" ? 0 : valueSource.gear) * valueSource.rpm) * 0.01
            if (fuelLevel <= 0) { fuelLevel = 100 }

            aycStatus += (Math.random() * 2).toFixed(0) - 1
            if (aycStatus > 3) { aycStatus = 3; }
            if (aycStatus < 0) { aycStatus = 0; }
            ayc3Bars = (aycStatus >= 3) ? true : false
            ayc2Bars = (aycStatus >= 2) ? true : false
            ayc1Bars = (aycStatus >= 1) ? true : false
        }
    }
    Timer {
        id: slowTimer
        interval: 10000
        running: true
        repeat: true
        onTriggered: {
            coolantTemperature = valueSource.temperature + ((Math.random() * 50) - 25)
            debugIcons = false
        }
    }
    // End delete this section

    Item {
        id: container
        // anchors.fill: parent
        anchors.centerIn: parent
        width: 1920
        height: 720

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (mouse.button == Qt.LeftButton) {
                    debugIcons = true
                }
                if (mouse.button == Qt.RightButton) {
                    backgroundEnabled = !backgroundEnabled
                }
            }
        }

        Row {
            id: topRow
            height: 58
            spacing: 50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5

            IndicatorTurnSignal {
                id: leftIndicator
                anchors.verticalCenter: parent.verticalCenter
                width: height
                height: parent.height

                onColor: "lime"
                offColor: "transparent"
                on: flashing
            }

            IndicatorFrontFog {
                id: frontFog
                anchors.verticalCenter: parent.verticalCenter
                width: height
                height: parent.height

                onColor: "lime"
                offColor: "transparent"
                on: debugIcons
            }

            IndicatorHighBeam {
                id: highBeam
                anchors.verticalCenter: parent.verticalCenter
                width: height
                height: parent.height

                onColor: "blue"
                offColor: "transparent"
                on: debugIcons
            }

            IndicatorRearFog {
                id: rearFog
                anchors.verticalCenter: parent.verticalCenter
                width: height
                height: parent.height

                onColor: "orange"
                offColor: "transparent"
                on: debugIcons
            }

            IndicatorTurnSignal {
                id: rightIndicator
                anchors.verticalCenter: parent.verticalCenter
                width: height
                height: parent.height
                scale: -1

                onColor: "lime"
                offColor: "transparent"
                on: flashing
            }
        }

        CircularGauge {
            id: fuelGauge

            width: 350
            height: 350
            anchors.rightMargin: 75
            anchors.bottomMargin: 97.5
            anchors.right: speedometer.left
            anchors.bottom: speedometer.bottom
            value: fuelLevel
            Behavior on value { SmoothedAnimation { velocity: 10 } }
            maximumValue: 100

            style: GaugeFuel {
                iconColor: fuelLevel <= 8.33 ? "red" : fuelLevel <= 16.67 ? "orange" : "white"
            }
        }

        Row {
            id: sideLightsIndicator
            anchors.bottom: fuelGauge.top
            anchors.bottomMargin: 15
            anchors.left: fuelGauge.horizontalCenter
            anchors.leftMargin: 40
            width: 58
            spacing: -(this.width / 2) + 5
            height: this.width
            opacity: debugIcons ? 1.0 : 0.0

            IndicatorSideLights {
                width: parent.width
                height: parent.height
                scale: 0.5
                onColor: "lime"
                offColor: "transparent"
                on: true
            }
            IndicatorSideLights {
                width: parent.width
                height: parent.height
                scale: -0.5
                onColor: "lime"
                offColor: "transparent"
                on: true
            }
        }

        Item {
            id: cruiseIndicator
            anchors.left: sideLightsIndicator.horizontalCenter
            anchors.leftMargin: 100
            anchors.bottom: sideLightsIndicator.verticalCenter
            anchors.bottomMargin: this.height / 2
            width: 58
            height: 58
            opacity: debugIcons ? 1.0 : 0.0

            Text {
                font.pixelSize: 20
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "CRUISE"
                color: cruiseStatus === 2 ? "orange" : cruiseStatus === 1 ? "lime" : "transparent"
            }
        }

        Rectangle {
            id: spareIndicator2
            anchors.left: cruiseIndicator.horizontalCenter
            anchors.leftMargin: 58
            anchors.bottom: cruiseIndicator.verticalCenter
            anchors.bottomMargin: this.height / 2
            width: 58
            height: 58
            radius: 5
            color: "red"
            opacity: debugIcons ? 1.0 : 0.0

            Text {
                font.pixelSize: 16
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "SPARE"
                color: "black"
            }
        }

        CircularGauge {
            id: speedometer

            width: 675
            height: 675
            anchors.rightMargin: -160
            anchors.topMargin: -5
            anchors.right: topRow.left
            anchors.top: topRow.bottom

            value: valueSource.kph
            maximumValue: 180
            style: GaugeSpeedometer {}
        }

        Rectangle {
            id: odometer
            anchors.bottom: speedometer.bottom
            anchors.bottomMargin: 57.5
            anchors.horizontalCenter: speedometer.horizontalCenter
            width: 300
            height: 52.5
            radius: 7.5
            color: "black"
            border.color: "#2f2f2f"
            border.width: 2

            Text {
                id: tripText
                font.pixelSize: 25
                text: "TRIP"
                color: "#ccccbb"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 0
                visible: tripMode > 0
            }

            Text {
                id: odoText
                font.pixelSize: 25
                text: "ODO"
                color: "#ccccbb"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: tripMode === 0
            }

            Rectangle {
                id: tripIconA
                anchors.top: odometer.top
                anchors.topMargin: 5
                anchors.left: odometer.left
                anchors.leftMargin: 70
                width: 25
                height: 20
                color: "#ccccbb"
                visible: tripMode === 1

                Text {
                    id: tripIconTextA
                    font.pixelSize: 20
                    text: "A"
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Rectangle {
                id: tripIconB
                anchors.bottom: odometer.bottom
                anchors.bottomMargin: 5
                anchors.left: odometer.left
                anchors.leftMargin: 70
                width: 25
                height: 20
                color: "#ccccbb"
                visible: tripMode === 2

                Text {
                    id: tripIconTextB
                    font.pixelSize: 20
                    text: "B"
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Text {
                id: odoValueGhost
                font.pixelSize: 50
                font.family: "Segment7"
                font.italic: true
                text: "88888.8"
                color: "#171715"
                anchors.right: parent.right
                anchors.rightMargin: 15
                anchors.top: parent.top
                anchors.topMargin: 5
            }

            Text {
                id: odoValue
                font.pixelSize: 50
                font.family: "Segment7"
                font.italic: true
                text: tripMode > 0 ? odoReading.toFixed(1) : odoReading.toFixed(0)
                color: "#ccccbb"
                anchors.right: parent.right
                anchors.rightMargin: 15
                anchors.top: parent.top
                anchors.topMargin: 5
            }
        }

        Grid {
            id: gearIndicators
            columns: 2
            columnSpacing: 25
            rowSpacing: -5
            width: 120
            // height: 675
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: topRow.bottom
            anchors.topMargin: 80

            Text {
                text: "P"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "P" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "R"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "R" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "N"
                color: "lime"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "N" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "D"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear !== "P" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "5" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "5"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "4" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "4"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "3" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "3"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "2" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "2"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }

            Item {
                Rectangle {
                    width: 20
                    height: width
                    radius: width
                    color: valueSource.gear === "1" ? "lime" : "#303030"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                width: 48; height: 56
            }

            Text {
                text: "1"
                color: "white"
                font.pixelSize: 48
                font.italic: true
                font.bold: true
            }
        }

        CircularGauge {
            id: tachometer

            width: 675
            height: 675
            anchors.leftMargin: -165
            anchors.topMargin: -5
            anchors.left: topRow.right
            anchors.top: topRow.bottom

            value: valueSource.rpm
            maximumValue: 9
            style: GaugeTachometer {}
        }

        CircularGauge {
            id: coolantGauge

            width: 350
            height: 350
            anchors.leftMargin: 75
            anchors.bottomMargin: 97.5
            anchors.left: tachometer.right
            anchors.bottom: tachometer.bottom
            value: coolantTemperature
            Behavior on value { SmoothedAnimation { velocity: 5 } }
            minimumValue: 75
            maximumValue: 125

            style: GaugeCoolant {
                iconColor: coolantTemperature >= 117 ? "red" : coolantTemperature >= 107 ? "orange" : coolantTemperature >= 80 ? "white" : "cyan"
            }
        }

        Item {
            id: skidIndicator
            anchors.bottom: coolantGauge.top
            anchors.bottomMargin: 15
            anchors.right: coolantGauge.horizontalCenter
            anchors.rightMargin: 45
            width: 58
            height: this.width
            visible: flashing & debugIcons

            Image {
                id: skidIcon
                source: "qrc:/images/skid-icon.png"
                fillMode: Image.PreserveAspectFit
            }

            ColorOverlay {
                anchors.fill: skidIcon
                source: skidIcon
                color: "orange"
            }
        }

        Item {
            id: tclOffIndicator
            anchors.right: skidIndicator.horizontalCenter
            anchors.rightMargin: 58
            anchors.bottom: skidIndicator.verticalCenter
            anchors.bottomMargin: this.height / 3
            width: 58
            height: 58
            opacity: debugIcons ? 1.0 : 0.0

            Text {
                font.pixelSize: 28
                font.bold: true
                lineHeight: 0.8
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "TCL\nOFF"
                color: "orange"
            }
        }

        Rectangle {
            id: ecoIndicator
            anchors.right: tclOffIndicator.horizontalCenter
            anchors.rightMargin: 58
            anchors.bottom: tclOffIndicator.verticalCenter
            anchors.bottomMargin: this.height / 3
            width: 58
            height: 58
            radius: 5
            color: "lime"
            opacity: debugIcons ? 1.0 : 0.0

            Text {
                font.pixelSize: 26
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "ECO"
                color: "black"
            }
        }

        Row {
            id: bottomLeftRow
            height: 58
            spacing: 30
            anchors.left: fuelGauge.horizontalCenter
            anchors.leftMargin: 50
            anchors.top: fuelGauge.bottom
            anchors.topMargin: 20

            Item {
                id: fuelLowIndicator
                width: 58
                height: this.width
                opacity: valueSource.fuel < 8.33 ? 1.0 : 0.0

                Image {
                    id: fuelLowIcon
                    source: "qrc:/images/fuel-icon.png"
                    fillMode: Image.PreserveAspectFit
                }

                ColorOverlay {
                    anchors.fill: fuelLowIcon
                    source: fuelLowIcon
                    color: "orange"
                }
            }

            Item {
                id: seatbeltIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: seatbeltIcon
                    source: "qrc:/images/seatbelt-icon.png"
                    fillMode: Image.PreserveAspectFit
                }

                ColorOverlay {
                    anchors.fill: seatbeltIcon
                    source: seatbeltIcon
                    color: "red"
                }
            }

            Item {
                id: srsIndicator
                width: 58
                height: 58
                opacity: debugIcons ? 1.0 : 0.0

                Text {
                    font.pixelSize: 28
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: "SRS"
                    color: "red"
                }
            }
        }

        Row {
            id: bottomCenterRow
            height: 58
            spacing: 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: gearIndicators.bottom
            anchors.topMargin: 50

            Item {
                id: doorOpenIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: doorOpenIcon
                    source: "qrc:/images/dooropen-icon.png"
                    fillMode: Image.PreserveAspectFit
                }

                ColorOverlay {
                    anchors.fill: doorOpenIcon
                    source: doorOpenIcon
                    color: "red"
                }
            }

            Item {
                id: absIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: absIcon
                    source: "qrc:/images/brake-icon.png"
                    fillMode: Image.PreserveAspectFit

                    Text {
                        font.pixelSize: 12
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: "ABS"
                    }
                }

                ColorOverlay {
                    anchors.fill: absIcon
                    source: absIcon
                    color: "orange"
                }
            }

            Item {
                id: brakeIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: brakeIcon
                    source: "qrc:/images/brake-icon.png"
                    fillMode: Image.PreserveAspectFit

                    Text {
                        font.pixelSize: 28
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: "!"
                    }
                }

                ColorOverlay {
                    anchors.fill: brakeIcon
                    source: brakeIcon
                    color: "red"
                }
            }

            Item {
                id: engineIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: engineIcon
                    source: "qrc:/images/engine-icon.png"
                    fillMode: Image.PreserveAspectFit
                }

                ColorOverlay {
                    anchors.fill: engineIcon
                    source: engineIcon
                    color: "orange"
                }
            }
        }

        Rectangle {
            id: spareIndicator1
            width: 58
            height: this.width
            anchors.right: bottomCenterRow.right
            anchors.bottom: bottomCenterRow.top
            anchors.bottomMargin: 10
            radius: 5
            color: "orange"
            opacity: debugIcons ? 1.0 : 0.0

            Text {
                font.pixelSize: 16
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "SPARE"
                color: "black"
            }
        }

        Column {
            id: aycStatusRow
            // height: 58
            spacing: 10
            anchors.horizontalCenter: tachometer.horizontalCenter
            anchors.top: tachometer.bottom
            anchors.topMargin: -140

            Rectangle {
                width: parent.width
                height: 15
                radius: 15
                color: ayc3Bars ? "lime" : "#303030"
            }

            Rectangle {
                width: parent.width
                height: 15
                radius: 15
                color: ayc2Bars ? "lime" : "#303030"
            }

            Rectangle {
                width: parent.width
                height: 15
                radius: 15
                color: ayc1Bars ? "lime" : "#303030"
            }

            Text {
                font.pixelSize: 60
                font.bold: true
                font.italic: true
                transform: Scale { yScale: 0.5}
                text: "AYC"
                color: "white"
            }
        }

        Item {
            id: oilTempIndicator
            width: 58
            height: this.width
            anchors.left: bottomRightRow.left
            anchors.bottom: bottomRightRow.top
            anchors.bottomMargin: 10
            opacity: debugIcons ? 1.0 : 0.0

            Image {
                id: oilTempIcon
                source: "qrc:/images/oiltemp-icon.png"
                fillMode: Image.PreserveAspectFit
            }

            ColorOverlay {
                anchors.fill: oilTempIcon
                source: oilTempIcon
                color: "orange"
            }
        }

        Row {
            id: bottomRightRow
            height: 58
            spacing: 40
            anchors.right: coolantGauge.horizontalCenter
            anchors.rightMargin: 90
            anchors.top: coolantGauge.bottom
            anchors.topMargin: 20

            Item {
                id: oilPressureIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: oilPressureIcon
                    source: "qrc:/images/oil-icon.png"
                    fillMode: Image.PreserveAspectFit
                }

                ColorOverlay {
                    anchors.fill: oilPressureIcon
                    source: oilPressureIcon
                    color: "red"
                }
            }

            Item {
                id: batteryIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: batteryIcon
                    source: "qrc:/images/battery-icon.png"
                    fillMode: Image.PreserveAspectFit
                }

                ColorOverlay {
                    anchors.fill: batteryIcon
                    source: batteryIcon
                    color: "red"
                }
            }

            Item {
                id: washerBottleIndicator
                width: 58
                height: this.width
                opacity: debugIcons ? 1.0 : 0.0

                Image {
                    id: washerBottleIcon
                    source: "qrc:/images/washerbottle-icon.png"
                    fillMode: Image.PreserveAspectFit
                }

                ColorOverlay {
                    anchors.fill: washerBottleIcon
                    source: washerBottleIcon
                    color: "orange"
                }
            }

            Item {
                id: aycIndicator
                width: 58
                height: 58
                opacity: debugIcons ? 1.0 : 0.0

                Text {
                    font.pixelSize: 28
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: "AYC"
                    color: "red"
                }
            }
        }
    }
}
