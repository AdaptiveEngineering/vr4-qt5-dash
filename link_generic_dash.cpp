#include "link_generic_dash.h"

// #include <Arduino.h>
// #include "localisation.h"
#include <QtGlobal>
#include <cstring>

// Dash parameters in the format "Friendly Name|Units of measurement|Decimal Places|Too Low Value|Good Value|Warning Value|Critical Value"
const char *GenericDashParameterNames[] = {
    "Engine Speed|RPM|0|0|600|6000|7000|8000",
    "Manifold Abs. Pres.|kPa|0|0|30|175|225|300",
    "Manifold Gauge Pres.|kPa|0|-100|-30|75|125|200",
    "Barometric Pressure|kPa|0|50|75|105|110|120",
    "Throttle Position|%|1|0|0.1|85|95|100",
    "Injector Duty Cycle|%|2|0|1|80|90|100",
    "Secondary Injector DC|%|2|0|0|80|90|100",
    "Injector Pulse Width|ms|3|0|1|4|5|6",
    "Engine Coolant Temp|°C|0|50|80|100|105|110",
    "Intake Air Temp|°C|0|-20|0|50|60|70",
    "Battery Voltage|V|2|11|12|15|16|17",
    "Mass Air Flow|g/s|0|0|0|5|10|15",
    "Gear Position| |0|0|0|99|99|5",
    "Injector Timing|°|0|0|320|999|999|320",
    "Ignition Timing|°|0|0|20|30|50|60",
    "Cam Inlet Position L|°|0|0|0|99|99|100",
    "Cam Inlet Position R|°|0|0|0|99|99|100",
    "Cam Exhaust Position L|°|0|0|0|99|99|100",
    "Cam Exhaust Position R|°|0|0|0|99|99|100",
    "Lambda Sensor 1|&lambda;|3|0.7|0.75|1.0|1.05|1.1",
    "Lambda Sensor 2|&lambda;|3|0.7|0.75|1.0|1.05|1.1",
    "Trigger 1 Errors|total|0|0|0|1|2|10",
    "Fault Codes|total|0|0|0|1|1|10",
    "Fuel Pressure|kPa|0|200|300|350|450|600",
    "Oil Temperature|°C|0|50|90|125|140|190",
    "Oil Pressure|kPa|0|50|150|350|500|600",
    "FL Wheel Speed|KPH|0|0|0|160|250|300",
    "RL Wheel Speed|KPH|0|0|0|160|250|300",
    "FR Wheel Speed|KPH|0|0|0|160|250|300",
    "RR Wheel Speed|KPH|0|0|0|160|250|300",
    "Knock Level Cyl 1|level|0|0|10|450|600|1000",
    "Knock Level Cyl 2|level|0|0|10|450|600|1000",
    "Knock Level Cyl 3|level|0|0|10|450|600|1000",
    "Knock Level Cyl 4|level|0|0|10|450|600|1000",
    "Knock Level Cyl 5|level|0|0|10|450|600|1000",
    "Knock Level Cyl 6|level|0|0|10|450|600|1000",
    "Knock Level Cyl 7|level|0|0|10|450|600|1000",
    "Knock Level Cyl 8|level|0|0|10|450|600|1000",
    "Limit Flags| |0|0|0|1|1|65535"
};

// Limit flags in the format "Friendly Name|Units of measurement|Too Low Value|Good Value|Warning Value|Critical Value"
const char *GenericDashLimitFlagsNames[] = {
    "RPM Limit| |0|0|0|1|1",
    "MAP Limit| |0|0|0|1|1",
    "Speed Limit| |0|0|0|1|2",
    "Max Ign Timing| |0|0|0|1|1",
    "Anti-Lag Ign Cut| |0|0|0|1|2",
    "ECU High Voltage| |0|0|0|1|1",
    "Overrun| |0|0|0|1|2",
    "Traction Limit| |0|0|0|1|2",
    "ECU Low Voltage| |0|0|0|1|1",
    "Launch RPM Limit| |0|0|0|1|2",
    "Wakeup| |0|0|0|1|2",
    "GP RPM Limit 1| |0|0|0|1|1",
    "Max ISC Steps| |0|0|0|1|1",
    "GP RPM Limit 2| |0|0|0|1|1",
    "E-Throttle Limit| |0|0|0|1|1",
    "Cyclic Idle Active| |0|0|0|1|2",
};

// Link ECU Fault Codes - Must be kept in lockstep with enum LinkECUFaultCodes
const char *LinkECUFaultCodeStrings[] {
	"No Fault",
	"RPM limit reached",
	"MAP limit reached",
	"Ethanol Sensor Fault",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"An Volt 1 above Error High Value",
	"An Volt 1 below Error Low Value",
	"An Volt 1 Signal Error",
	"An Volt 2 above Error High Value",
	"An Volt 2 below Error Low Value",
	"An Volt 2 Signal Error",
	"An Volt 3 above Error High Value",
	"An Volt 3 below Error Low Value",
	"An Volt 3 Signal Error",
	"An Volt 4 above Error High Value",
	"An Volt 4 below Error Low Value",
	"An Volt 4 Signal Error",
	"An Volt 5 above Error High Value",
	"An Volt 5 below Error Low Value",
	"An Volt 5 Signal Error",
	"An Volt 6 above Error High Value",
	"An Volt 6 below Error Low Value",
	"An Volt 6 Signal Error",
	"An Volt 7 above Error High Value",
	"An Volt 7 below Error Low Value",
	"An Volt 7 Signal Error",
	"An Volt 8 above Error High Value",
	"An Volt 8 below Error Low Value",
	"An Volt 8 Signal Error",
	"An Volt 9 above Error High Value",
	"An Volt 9 below Error Low Value",
	"An Volt 9 Signal Error",
	"An Volt 10 above Error High Value",
	"An Volt 10 below Error Low Value",
	"An Volt 10 Signal Error",
	"An Volt 11 above Error High Value",
	"An Volt 11 below Error Low Value",
	"An Volt 11 Signal Error",
	"An Temperature 1 above Error High Value",
	"An Temperature 1 below Error Low Value",
	"An Temperature 1 Signal Error",
	"An Temperature 2 above Error High Value",
	"An Temperature 2 below Error Low Value",
	"An Tempperature 2 Signal Error",
	"An Temperature 3 above Error High Value",
	"An Temperature 3 below Error Low Value",
	"An Temperature 3 Signal Error",
	"An Temperature 4 above Error High Value",
	"An Temperature 4 below Error Low Value",
	"An Temperature 4 Signal Error",
	"Consult Link Dealership",
	"MAP Above Fault Code Value",
	"MAP Signal Error",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"ECT Above Fault Code Value",
	"ECT Signal Error",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"Consult Link Dealership",
	"E-Throttle 1 Max %DC Limit",
	"E-Throttle 1 Min %DC Limit",
	"Aux 9/10 Supply Error - E-Throttle",
	"Analog 5V Supply Error - E-Throttle (E-Throttle Sensor Supply Voltage)",
	"Aux 9/10 Supply Error - E-Throttle",
	"Analog 5V Supply Error",
	"E-Throttle 1 TPS /Target Error",
	"TPS(main) /TPS(sub) tracking Error",
	"APS(main) /APS(sub) tracking Error",
	"TPS(Main) Fault - E-Throttle.",
	"TPS(Sub) Fault - E-Throttle",
	"TPS(Main) Above Fault Code Value",
	"TPS(Sub) Above Fault Code Value",
	"TPS(Main) Not Selected",
	"TPS(Sub) Not Selected",
	"Aux9/10 E-Throttle IC Over Temperature / Under Voltage",
	"APS(Main) Fault - E-Throttle.",
	"APS(Sub) Fault - E-Throttle",
	"See Link Manual",
	"APS(Sub) Above Fault Code Value",
	"APS(Main) Not Selected",
	"APS(Sub) Not Selected",
	"Consult Link Dealership",
	"APS CAN Signal Lost",
	"E-Throttle 2 Max %DC Limit",
	"E-Throttle 2 Min %DC Limit",
	"E-Throttle 2 TPS 2 /Target Error",
	"TPS 2 (Main) Fault - E-Throttle 2",
	"TPS 2 (Sub) Fault - E-Throttle 2",
	"TPS 2 (Main) / TPS 2 (Sub) tracking Error",
	"Aux 17-20 Supply Error",
	"Aux 17-20 Supply Error - E-Throttle",
	"An Volt 12 above Error High Value",
	"An Volt 12 below Error Low Value",
	"An Volt 12 Signal Error",
	"An Volt 13 above Error High Value",
	"An Volt 13 below Error Low Value",
	"An Volt 13 Signal Error",
	"An Volt 14 above Error High Value",
	"An Volt 14 below Error Low Value",
	"An Volt 14 Signal Error",
	"An Volt 15 above Error High Value",
	"An Volt 15 below Error Low Value",
	"An Volt 15 Signal Error",
	"An Volt 16 above Error High Value",
	"An Volt 16 below Error Low Value",
	"An Volt 16 Signal Error",
	"Analog 5V Supply Error - E-Throttle 2 (E-Throttle 2 Sensor Supply Voltage)",
	"Aux 17-20 E-Throttle IC Over Temperature / Under Voltage",
	"DI Fuel Pump Control Low Pressure Fault",
	"DI Fuel Pump Control High Pressure Fault",
	"Ethrottle Control Error",
	"Ethrottle No Relay Selected",
	"Maximum Injector Duty Cycle Reached",
	"DI Driver Fault"
};

const char LinkECUFaultCodeUnknownErrorString[] = "Consult Link Dealership";

float getGenericDashValue(volatile unsigned char dataList[GenericDashFrames][GenericDashBytes], GenericDashParameters param) {
    switch (param) {
    case ECU_ENGINE_SPEED_RPM:
        return (signed int)((dataList[0][3] << 8) + (dataList[0][2] << 0));
        break;
    case ECU_MAP_KPA:
        return (signed int)((dataList[0][5] << 8) + (dataList[0][4] << 0));
        break;
    case ECU_MGP_KPA:
        return (signed int)((dataList[0][7] << 8) + (dataList[0][6] << 0)) - 100;
        break;
    case ECU_BAROMETRIC_PRESSURE_KPA:
        return (signed int)((dataList[1][3] << 8) + (dataList[1][2] << 0)) * 0.1;
        break;
    case ECU_THROTTLE_POSITION_PERCENT:
        return (signed int)((dataList[1][5] << 8) + (dataList[1][4] << 0)) * 0.1;
        break;
    case ECU_INJECTOR_DUTY_CYCLE_PERCENT:
        return (signed int)((dataList[1][7] << 8) + (dataList[1][6] << 0)) * 0.1;
        break;
    case ECU_SECOND_STAGE_INJECTOR_DUTY_CYCLE_PERCENT:
        return (signed int)((dataList[2][3] << 8) + (dataList[2][2] << 0)) * 0.1;
        break;
    case ECU_INJECTOR_PULSE_WIDTH_MS:
        return (signed int)((dataList[2][5] << 8) + (dataList[2][4] << 0)) * 0.001;
        break;
    case ECU_ENGINE_COOLANT_TEMPERATURE_DEGREES_C:
        return (signed int)((dataList[2][7] << 8) + (dataList[2][6] << 0)) - 50;
        break;
    case ECU_INTAKE_AIR_TEMPERATURE_DEGRESS_C:
        return (signed int)((dataList[3][3] << 8) + (dataList[3][2] << 0)) - 50;
        break;
    case ECU_BATTERY_VOLTAGE:
        return (signed int)((dataList[3][5] << 8) + (dataList[3][4] << 0)) * 0.01;
        break;
    case ECU_MASS_AIR_FLOW_GRAMS_PER_SECOND:
        return (signed int)((dataList[3][7] << 8) + (dataList[3][6] << 0)) * 0.1;
        break;
    case ECU_GEAR_POSITION:
        return (signed int)((dataList[4][3] << 8) + (dataList[4][2] << 0));
        break;
    case ECU_INJECTOR_TIMING_DEGREES:
        return (signed int)((dataList[4][5] << 8) + (dataList[4][4] << 0));
        break;
    case ECU_IGNITION_TIMING_DEGREES:
        return (signed int)(((dataList[4][7] << 8) + (dataList[4][6] << 0)) * 0.1) - 100;
        break;
    case ECU_CAM_INLET_POSITION_L_DEGREES:
        return (signed int)((dataList[5][3] << 8) + (dataList[5][2] << 0)) * 0.1;
        break;
    case ECU_CAM_INLET_POSITION_R_DEGREES:
        return (signed int)((dataList[5][5] << 8) + (dataList[5][4] << 0)) * 0.1;
        break;
    case ECU_CAM_EXHAUST_POSITION_L_DEGREES:
        return (signed int)((dataList[5][7] << 8) + (dataList[5][6] << 0)) * -0.1;
        break;
    case ECU_CAM_EXHAUST_POSITION_R_DEGREES:
        return (signed int)((dataList[6][3] << 8) + (dataList[6][2] << 0)) * -0.1;
        break;
    case ECU_LAMBDA_1_LAMBDA:
        return (signed int)((dataList[6][5] << 8) + (dataList[6][4] << 0)) * 0.001;
        break;
    case ECU_LAMBDA_2_LAMBDA:
        return (signed int)((dataList[6][7] << 8) + (dataList[6][6] << 0)) * 0.001;
        break;
    case ECU_TRIGGER_1_ERROR_COUNT:
        return (signed int)((dataList[7][3] << 8) + (dataList[7][2] << 0));
        break;
    case ECU_FAULT_CODES_COUNT:
        return (signed int)((dataList[7][5] << 8) + (dataList[7][4] << 0));
        break;
    case ECU_FUEL_PRESSURE_KPA:
        return (signed int)((dataList[7][7] << 8) + (dataList[7][6] << 0));
        break;
    case ECU_OIL_TEMPERATURE_DEGREES_C:
        return (signed int)((dataList[8][3] << 8) + (dataList[8][2] << 0)) - 50;
        break;
    case ECU_OIL_PRESSURE_KPA:
        return (signed int)((dataList[8][5] << 8) + (dataList[8][4] << 0));
        break;
    case ECU_LEFT_FRONT_WHEEL_SPEED_KPH:
        return (signed int)((dataList[8][7] << 8) + (dataList[8][6] << 0)) * 0.1;
        break;
    case ECU_LEFT_REAR_WHEEL_SPEED_KPH:
        return (signed int)((dataList[9][3] << 8) + (dataList[9][2] << 0)) * 0.1;
        break;
    case ECU_RIGHT_FRONT_WHEEL_SPEED_KPH:
        return (signed int)((dataList[9][5] << 8) + (dataList[9][4] << 0)) * 0.1;
        break;
    case ECU_RIGHT_REAR_WHEEL_SPEED_KPH:
        return (signed int)((dataList[9][7] << 8) + (dataList[9][6] << 0)) * 0.1;
        break;
    case ECU_KNOCK_LEVEL_1_COUNT:
        return (signed int)((dataList[10][3] << 8) + (dataList[10][2] << 0)) * 5;
        break;
    case ECU_KNOCK_LEVEL_2_COUNT:
        return (signed int)((dataList[10][5] << 8) + (dataList[10][4] << 0)) * 5;
        break;
    case ECU_KNOCK_LEVEL_3_COUNT:
        return (signed int)((dataList[10][7] << 8) + (dataList[10][6] << 0)) * 5;
        break;
    case ECU_KNOCK_LEVEL_4_COUNT:
        return (signed int)((dataList[11][3] << 8) + (dataList[11][2] << 0)) * 5;
        break;
    case ECU_KNOCK_LEVEL_5_COUNT:
        return (signed int)((dataList[11][5] << 8) + (dataList[11][4] << 0)) * 5;
        break;
    case ECU_KNOCK_LEVEL_6_COUNT:
        return (signed int)((dataList[11][7] << 8) + (dataList[11][6] << 0)) * 5;
        break;
    case ECU_KNOCK_LEVEL_7_COUNT:
        return (signed int)((dataList[12][3] << 8) + (dataList[12][2] << 0)) * 5;
        break;
    case ECU_KNOCK_LEVEL_8_COUNT:
        return (signed int)((dataList[12][5] << 8) + (dataList[12][4] << 0)) * 5;
        break;
    case ECU_LIMIT_FLAGS_BITFIELD:
        return (signed int)((dataList[12][7] << 8) + (dataList[12][6] << 0));
        break;
    default:
        return -1;
        break;
    }
}

bool getGenericDashLimitFlag(volatile unsigned char dataList[GenericDashFrames][GenericDashBytes], GenericDashLimitFlags param) {
    quint16 flags = (quint16)getGenericDashValue(dataList, ECU_LIMIT_FLAGS_BITFIELD);
    return (bool)((flags >> (int)param) & 0x1);
}

QString getLinkECUFaultCode(LinkECUFaultCodes param) {
	if ((param < 0) || (param >= Link_ECU_Fault_Code_Count)) {
        return QString(LinkECUFaultCodeUnknownErrorString);
	} else {
        return QString(LinkECUFaultCodeStrings[param]);
	}
}
