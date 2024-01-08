#ifndef link_generic_dash_h
#define link_generic_dash_h

// #include <Arduino.h>
// #include "localisation.h"
#include <QtGlobal>

// Constants used by GenericDash multi-dimensional array - DO NOT CHANGE THESE
#define GenericDashFrames 13
#define GenericDashBytes 8

// List of known parameters sent via Generic Dash
enum GenericDashParameters {
    ECU_ENGINE_SPEED_RPM,
    ECU_MAP_KPA,
    ECU_MGP_KPA,
    ECU_BAROMETRIC_PRESSURE_KPA,
    ECU_THROTTLE_POSITION_PERCENT,
    ECU_INJECTOR_DUTY_CYCLE_PERCENT,
    ECU_SECOND_STAGE_INJECTOR_DUTY_CYCLE_PERCENT,
    ECU_INJECTOR_PULSE_WIDTH_MS,
    ECU_ENGINE_COOLANT_TEMPERATURE_DEGREES_C,
    ECU_INTAKE_AIR_TEMPERATURE_DEGRESS_C,
    ECU_BATTERY_VOLTAGE,
    ECU_MASS_AIR_FLOW_GRAMS_PER_SECOND,
    ECU_GEAR_POSITION,
    ECU_INJECTOR_TIMING_DEGREES,
    ECU_IGNITION_TIMING_DEGREES,
    ECU_CAM_INLET_POSITION_L_DEGREES,
    ECU_CAM_INLET_POSITION_R_DEGREES,
    ECU_CAM_EXHAUST_POSITION_L_DEGREES,
    ECU_CAM_EXHAUST_POSITION_R_DEGREES,
    ECU_LAMBDA_1_LAMBDA,
    ECU_LAMBDA_2_LAMBDA,
    ECU_TRIGGER_1_ERROR_COUNT,
    ECU_FAULT_CODES_COUNT,
    ECU_FUEL_PRESSURE_KPA,
    ECU_OIL_TEMPERATURE_DEGREES_C,
    ECU_OIL_PRESSURE_KPA,
    ECU_LEFT_FRONT_WHEEL_SPEED_KPH,
    ECU_LEFT_REAR_WHEEL_SPEED_KPH,
    ECU_RIGHT_FRONT_WHEEL_SPEED_KPH,
    ECU_RIGHT_REAR_WHEEL_SPEED_KPH,
    ECU_KNOCK_LEVEL_1_COUNT,
    ECU_KNOCK_LEVEL_2_COUNT,
    ECU_KNOCK_LEVEL_3_COUNT,
    ECU_KNOCK_LEVEL_4_COUNT,
    ECU_KNOCK_LEVEL_5_COUNT,
    ECU_KNOCK_LEVEL_6_COUNT,
    ECU_KNOCK_LEVEL_7_COUNT,
    ECU_KNOCK_LEVEL_8_COUNT,
    ECU_LIMIT_FLAGS_BITFIELD
};
const int Generic_Dash_Parameter_Count = 39;

// List of known limits flags sent as ECU_LIMIT_FLAGS_BITFIELD
enum GenericDashLimitFlags {
    LIMITS_FLAG_RPM_LIMIT,
    LIMITS_FLAG_MAP_LIMIT,
    LIMITS_FLAG_SPEED_LIMIT,
    LIMITS_FLAG_MAXIMUM_IGNITION_FLAG,
    LIMITS_FLAG_ANTI_LAG_IGNITION_CUT,
    LIMITS_FLAG_HIGH_VOLTAGE_SUPPLY_LIMIT,
    LIMITS_FLAG_OVERRUN_FLAG,
    LIMITS_FLAG_TRACTION_LIMIT,
    LIMITS_FLAG_LOW_VOLTAGE_SUPPLY_LIMIT,
    LIMITS_FLAG_LAUNCH_RPM_LIMIT,
    LIMITS_FLAG_WAKEUP_FLAG,
    LIMITS_FLAG_GP_RPM_LIMIT_1,
    LIMITS_FLAG_CL_STEPPER_LIMIT,
    LIMITS_FLAG_GP_RPM_LIMIT_2,
    LIMITS_FLAG_ETHROTTLE_LIMIT,
    LIMITS_FLAG_CYCLIC_IDLE_ACTIVE
};

// Function to get a specific value from the Generic Dash buffer
float getGenericDashValue(volatile unsigned char dataList[GenericDashFrames][GenericDashBytes], GenericDashParameters param);

// Function to get a specific limit flat from the Generic Dash Buffer
bool getGenericDashLimitFlag(volatile unsigned char dataList[GenericDashFrames][GenericDashBytes], GenericDashLimitFlags param);

#endif // link_generic_dash_h
