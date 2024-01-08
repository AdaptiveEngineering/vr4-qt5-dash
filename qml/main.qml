import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    id: root
    visible: true
    visibility: "FullScreen"
    width: Screen.width
    height: Screen.height

    color: "#000000"
    title: "VR-4 Dash"

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

    Item {
        id: splash
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "#000000"
        }
        Text {
            text: "VR  4"
            color: "red"
            font.family: "VR4"
            font.pixelSize: 320
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Loader {
        id: loader
        active: false
        asynchronous: true
        anchors.fill: parent
        visible: status == Loader.Ready
        onLoaded: splash.visible = false
        source: "qrc:/qml/dashboard.qml"
    }

    Timer {
        id: loaderTimer
        interval: 1000
        running: true
        onTriggered: { loader.active = true }
    }
}
