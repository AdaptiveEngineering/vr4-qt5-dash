import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    id: main
    visible: true
    visibility: "FullScreen"
    width: Screen.width
    height: Screen.height

    color: "#000000"
    title: "VR-4 Dash"

    property bool gpio_IGNITION

    property real dash_ECU_ENGINE_SPEED_RPM
    property real dash_ECU_MAP_KPA
    property real dash_ECU_MGP_KPA
    property real dash_ECU_BAROMETRIC_PRESSURE_KPA
    property real dash_ECU_THROTTLE_POSITION_PERCENT
    property real dash_ECU_INJECTOR_DUTY_CYCLE_PERCENT
    property real dash_ECU_SECOND_STAGE_INJECTOR_DUTY_CYCLE_PERCENT
    property real dash_ECU_INJECTOR_PULSE_WIDTH_MS
    property real dash_ECU_ENGINE_COOLANT_TEMPERATURE_DEGREES_C
    property real dash_ECU_INTAKE_AIR_TEMPERATURE_DEGRESS_C
    property real dash_ECU_BATTERY_VOLTAGE
    property real dash_ECU_MASS_AIR_FLOW_GRAMS_PER_SECOND
    property real dash_ECU_GEAR_POSITION
    property real dash_ECU_INJECTOR_TIMING_DEGREES
    property real dash_ECU_IGNITION_TIMING_DEGREES
    property real dash_ECU_CAM_INLET_POSITION_L_DEGREES
    property real dash_ECU_CAM_INLET_POSITION_R_DEGREES
    property real dash_ECU_CAM_EXHAUST_POSITION_L_DEGREES
    property real dash_ECU_CAM_EXHAUST_POSITION_R_DEGREES
    property real dash_ECU_LAMBDA_1_LAMBDA
    property real dash_ECU_LAMBDA_2_LAMBDA
    property real dash_ECU_TRIGGER_1_ERROR_COUNT
    property real dash_ECU_FAULT_CODES_COUNT
    property real dash_ECU_FUEL_PRESSURE_KPA
    property real dash_ECU_OIL_TEMPERATURE_DEGREES_C
    property real dash_ECU_OIL_PRESSURE_KPA
    property real dash_ECU_LEFT_FRONT_WHEEL_SPEED_KPH
    property real dash_ECU_LEFT_REAR_WHEEL_SPEED_KPH
    property real dash_ECU_RIGHT_FRONT_WHEEL_SPEED_KPH
    property real dash_ECU_RIGHT_REAR_WHEEL_SPEED_KPH
    property real dash_ECU_KNOCK_LEVEL_1_COUNT
    property real dash_ECU_KNOCK_LEVEL_2_COUNT
    property real dash_ECU_KNOCK_LEVEL_3_COUNT
    property real dash_ECU_KNOCK_LEVEL_4_COUNT
    property real dash_ECU_KNOCK_LEVEL_5_COUNT
    property real dash_ECU_KNOCK_LEVEL_6_COUNT
    property real dash_ECU_KNOCK_LEVEL_7_COUNT
    property real dash_ECU_KNOCK_LEVEL_8_COUNT
    property real dash_ECU_LIMIT_FLAGS_BITFIELD

    property string dash_ECU_FAULT_CODE_MESSAGES

    // Item {
    //     id: splash
    //     anchors.fill: parent

    //     Rectangle {
    //         anchors.fill: parent
    //         color: "#000000"
    //         visible: loader.opacity != 1
    //     }
    //     Image {
    //         source: "qrc:/images/vr4-digital-dash-preload.png"
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         anchors.verticalCenter: parent.verticalCenter
    //         visible: loader.opacity != 1
    //     }
    // }

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
    property bool debugIcons: false

    Timer {
        id: fastTimer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            flashing = !flashing
            // Delete below this line to end of block when done
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

    // Delete this section when done
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

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.AllButtons
        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                backgroundEnabled = !backgroundEnabled
            }
            else {
                debugIcons = true
            }
        }
    }

    Loader {
        id: loader
        active: true
        anchors.fill: parent
        opacity: +(backgroundEnabled | gpio_IGNITION)
        Behavior on opacity { SmoothedAnimation { velocity: 1 } }
        // NumberAnimation on opacity {
        //     from: 0
        //     to: 1
        //     duration: 1000
        // }
        source: "qrc:/qml/dashboard.qml"
    }
}
