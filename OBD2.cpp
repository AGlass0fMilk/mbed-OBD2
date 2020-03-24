/*
 * Copyright (c) Sandeep Mistry. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 *
 * Modified and ported to Mbed OS by George Beckstein for Embedded Planet, Inc
 */
#include <math.h>

#include "OBD2.h"

#include "platform/mbed_wait_api.h"

const char PID_NAME_0x00[]  = "PIDs supported [01 - 20]";
const char PID_NAME_0x01[]  = "Monitor status since DTCs cleared";
const char PID_NAME_0x02[]  = "Freeze DTC";
const char PID_NAME_0x03[]  = "Fuel system status";
const char PID_NAME_0x04[]  = "Calculated engine load";
const char PID_NAME_0x05[]  = "Engine coolant temperature";
const char PID_NAME_0x06[]  = "Short term fuel trim — Bank 1";
const char PID_NAME_0x07[]  = "Long term fuel trim — Bank 1";
const char PID_NAME_0x08[]  = "Short term fuel trim — Bank 2";
const char PID_NAME_0x09[]  = "Long term fuel trim — Bank 2";
const char PID_NAME_0x0a[]  = "Fuel pressure";
const char PID_NAME_0x0b[]  = "Intake manifold absolute pressure";
const char PID_NAME_0x0c[]  = "Engine RPM";
const char PID_NAME_0x0d[]  = "Vehicle speed";
const char PID_NAME_0x0e[]  = "Timing advance";
const char PID_NAME_0x0f[]  = "Intake air temperature";
const char PID_NAME_0x10[]  = "MAF air flow rate";
const char PID_NAME_0x11[]  = "Throttle position";
const char PID_NAME_0x12[]  = "Commanded secondary air status";
const char PID_NAME_0x13[]  = "Oxygen sensors present (in 2 banks)";
const char PID_NAME_0x14[]  = "Oxygen Sensor 1 - Short term fuel trim";
const char PID_NAME_0x15[]  = "Oxygen Sensor 2 - Short term fuel trim";
const char PID_NAME_0x16[]  = "Oxygen Sensor 3 - Short term fuel trim";
const char PID_NAME_0x17[]  = "Oxygen Sensor 4 - Short term fuel trim";
const char PID_NAME_0x18[]  = "Oxygen Sensor 5 - Short term fuel trim";
const char PID_NAME_0x19[]  = "Oxygen Sensor 6 - Short term fuel trim";
const char PID_NAME_0x1a[]  = "Oxygen Sensor 7 - Short term fuel trim";
const char PID_NAME_0x1b[]  = "Oxygen Sensor 8 - Short term fuel trim";
const char PID_NAME_0x1c[]  = "OBD standards this vehicle conforms to";
const char PID_NAME_0x1d[]  = "Oxygen sensors present (in 4 banks)";
const char PID_NAME_0x1e[]  = "Auxiliary input status";
const char PID_NAME_0x1f[]  = "Run time since engine start";
const char PID_NAME_0x20[]  = "PIDs supported [21 - 40]";
const char PID_NAME_0x21[]  = "Distance traveled with malfunction indicator lamp (MIL) on";
const char PID_NAME_0x22[]  = "Fuel Rail Pressure (relative to manifold vacuum)";
const char PID_NAME_0x23[]  = "Fuel Rail Gauge Pressure (diesel, or gasoline direct injection)";
const char PID_NAME_0x24[]  = "Oxygen Sensor 1 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x25[]  = "Oxygen Sensor 2 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x26[]  = "Oxygen Sensor 3 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x27[]  = "Oxygen Sensor 4 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x28[]  = "Oxygen Sensor 5 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x29[]  = "Oxygen Sensor 6 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x2a[]  = "Oxygen Sensor 7 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x2b[]  = "Oxygen Sensor 8 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x2c[]  = "Commanded EGR";
const char PID_NAME_0x2d[]  = "EGR Error";
const char PID_NAME_0x2e[]  = "Commanded evaporative purge";
const char PID_NAME_0x2f[]  = "Fuel Tank Level Input";
const char PID_NAME_0x30[]  = "Warm-ups since codes cleared";
const char PID_NAME_0x31[]  = "Distance traveled since codes cleared";
const char PID_NAME_0x32[]  = "Evap. System Vapor Pressure";
const char PID_NAME_0x33[]  = "Absolute Barometric Pressure";
const char PID_NAME_0x34[]  = "Oxygen Sensor 1 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x35[]  = "Oxygen Sensor 2 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x36[]  = "Oxygen Sensor 3 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x37[]  = "Oxygen Sensor 4 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x38[]  = "Oxygen Sensor 5 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x39[]  = "Oxygen Sensor 6 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x3a[]  = "Oxygen Sensor 7 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x3b[]  = "Oxygen Sensor 8 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x3c[]  = "Catalyst Temperature: Bank 1, Sensor 1";
const char PID_NAME_0x3d[]  = "Catalyst Temperature: Bank 2, Sensor 1";
const char PID_NAME_0x3e[]  = "Catalyst Temperature: Bank 1, Sensor 2";
const char PID_NAME_0x3f[]  = "Catalyst Temperature: Bank 2, Sensor 2";
const char PID_NAME_0x40[]  = "PIDs supported [41 - 60]";
const char PID_NAME_0x41[]  = "Monitor status this drive cycle";
const char PID_NAME_0x42[]  = "Control module voltage";
const char PID_NAME_0x43[]  = "Absolute load value";
const char PID_NAME_0x44[]  = "Fuel–Air commanded equivalence ratio";
const char PID_NAME_0x45[]  = "Relative throttle position";
const char PID_NAME_0x46[]  = "Ambient air temperature";
const char PID_NAME_0x47[]  = "Absolute throttle position B";
const char PID_NAME_0x48[]  = "Absolute throttle position C";
const char PID_NAME_0x49[]  = "Absolute throttle position D";
const char PID_NAME_0x4a[]  = "Absolute throttle position E";
const char PID_NAME_0x4b[]  = "Absolute throttle position F";
const char PID_NAME_0x4c[]  = "Commanded throttle actuator";
const char PID_NAME_0x4d[]  = "Time run with MIL on";
const char PID_NAME_0x4e[]  = "Time since trouble codes cleared";
const char PID_NAME_0x4f[]  = "Maximum value for Fuel–Air equivalence ratio, oxygen sensor voltage, oxygen sensor current, and intake manifold absolute pressure";
const char PID_NAME_0x50[]  = "Maximum value for air flow rate from mass air flow sensor";
const char PID_NAME_0x51[]  = "Fuel Type";
const char PID_NAME_0x52[]  = "Ethanol fuel percentage";
const char PID_NAME_0x53[]  = "Absolute Evap system Vapor Pressure";
const char PID_NAME_0x54[]  = "Evap system vapor pressure";
const char PID_NAME_0x55[]  = "Short term secondary oxygen sensor trim";
const char PID_NAME_0x56[]  = "Long term secondary oxygen sensor trim";
const char PID_NAME_0x57[]  = "Short term secondary oxygen sensor trim";
const char PID_NAME_0x58[]  = "Long term secondary oxygen sensor trim";
const char PID_NAME_0x59[]  = "Fuel rail absolute pressure";
const char PID_NAME_0x5a[]  = "Relative accelerator pedal position";
const char PID_NAME_0x5b[]  = "Hybrid battery pack remaining life";
const char PID_NAME_0x5c[]  = "Engine oil temperature";
const char PID_NAME_0x5d[]  = "Fuel injection timing";
const char PID_NAME_0x5e[]  = "Engine fuel rate";
const char PID_NAME_0x5f[]  = "Emission requirements to which vehicle is designed";

const char* const PID_NAME_MAPPER[]  = {
  PID_NAME_0x00,
  PID_NAME_0x01,
  PID_NAME_0x02,
  PID_NAME_0x03,
  PID_NAME_0x04,
  PID_NAME_0x05,
  PID_NAME_0x06,
  PID_NAME_0x07,
  PID_NAME_0x08,
  PID_NAME_0x09,
  PID_NAME_0x0a,
  PID_NAME_0x0b,
  PID_NAME_0x0c,
  PID_NAME_0x0d,
  PID_NAME_0x0e,
  PID_NAME_0x0f,
  PID_NAME_0x10,
  PID_NAME_0x11,
  PID_NAME_0x12,
  PID_NAME_0x13,
  PID_NAME_0x14,
  PID_NAME_0x15,
  PID_NAME_0x16,
  PID_NAME_0x17,
  PID_NAME_0x18,
  PID_NAME_0x19,
  PID_NAME_0x1a,
  PID_NAME_0x1b,
  PID_NAME_0x1c,
  PID_NAME_0x1d,
  PID_NAME_0x1e,
  PID_NAME_0x1f,
  PID_NAME_0x20,
  PID_NAME_0x21,
  PID_NAME_0x22,
  PID_NAME_0x23,
  PID_NAME_0x24,
  PID_NAME_0x25,
  PID_NAME_0x26,
  PID_NAME_0x27,
  PID_NAME_0x28,
  PID_NAME_0x29,
  PID_NAME_0x2a,
  PID_NAME_0x2b,
  PID_NAME_0x2c,
  PID_NAME_0x2d,
  PID_NAME_0x2e,
  PID_NAME_0x2f,
  PID_NAME_0x30,
  PID_NAME_0x31,
  PID_NAME_0x32,
  PID_NAME_0x33,
  PID_NAME_0x34,
  PID_NAME_0x35,
  PID_NAME_0x36,
  PID_NAME_0x37,
  PID_NAME_0x38,
  PID_NAME_0x39,
  PID_NAME_0x3a,
  PID_NAME_0x3b,
  PID_NAME_0x3c,
  PID_NAME_0x3d,
  PID_NAME_0x3e,
  PID_NAME_0x3f,
  PID_NAME_0x40,
  PID_NAME_0x41,
  PID_NAME_0x42,
  PID_NAME_0x43,
  PID_NAME_0x44,
  PID_NAME_0x45,
  PID_NAME_0x46,
  PID_NAME_0x47,
  PID_NAME_0x48,
  PID_NAME_0x49,
  PID_NAME_0x4a,
  PID_NAME_0x4b,
  PID_NAME_0x4c,
  PID_NAME_0x4d,
  PID_NAME_0x4e,
  PID_NAME_0x4f,
  PID_NAME_0x50,
  PID_NAME_0x51,
  PID_NAME_0x52,
  PID_NAME_0x53,
  PID_NAME_0x54,
  PID_NAME_0x55,
  PID_NAME_0x56,
  PID_NAME_0x57,
  PID_NAME_0x58,
  PID_NAME_0x59,
  PID_NAME_0x5a,
  PID_NAME_0x5b,
  PID_NAME_0x5c,
  PID_NAME_0x5d,
  PID_NAME_0x5e,
  PID_NAME_0x5f,
};

const char PERCENTAGE[]  = "%";
const char KPA[]  = "kPa";
const char PA[]  = "Pa";
const char RPM[]  = "rpm";
const char KPH[]  = "km/h";
const char DEGREES_BEFORE_TDC[]  = "° before TDC";
const char GRAMS_PER_SECOND[]  = "grams/sec";
const char SECONDS[]  = "seconds";
const char RATIO[]  = "ratio";
const char COUNT[]  = "count";
const char KM[]  = "km";
const char VOLTS[]  = "V";
const char MINUTES[]  = "minutes";
const char GPS[]  = "g/s";
const char DEGREES[]  = "°";
const char DEGREES_CELCIUS[]  = "°C";
const char LPH[]  = "L/h";

const char* const PID_UNIT_MAPPER[]  = {
  NULL,
  NULL,
  NULL,
  NULL,
  PERCENTAGE,
  DEGREES_CELCIUS,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  KPA,
  KPA,
  RPM,
  KPH,
  DEGREES_BEFORE_TDC,
  DEGREES_CELCIUS,
  GRAMS_PER_SECOND,
  PERCENTAGE,
  NULL,
  NULL,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  NULL,
  NULL,
  NULL,
  SECONDS,
  NULL,
  KM,
  KPA,
  KPA,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  COUNT,
  KM,
  PA,
  KPA,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  DEGREES_CELCIUS,
  DEGREES_CELCIUS,
  DEGREES_CELCIUS,
  DEGREES_CELCIUS,
  NULL,
  NULL,
  VOLTS,
  PERCENTAGE,
  RATIO,
  PERCENTAGE,
  DEGREES_CELCIUS,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  MINUTES,
  MINUTES,
  NULL,
  GPS,
  NULL,
  PERCENTAGE,
  KPA,
  PA,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  KPA,
  PERCENTAGE,
  PERCENTAGE,
  DEGREES_CELCIUS,
  DEGREES,
  LPH,
  NULL,
};

OBD2Client::OBD2Client(mbed::CAN& interface) :
        can(interface), base_filter_handle(0), extended_filter_handle(0),
        rx_cb(nullptr), tx_cb(nullptr), rx_flag(false), tx_flag(false),
        timeout_passed(false), timeout(), _responseTimeout(OBD2_DEFAULT_TIMEOUT),
        _useExtendedAddressing(false), _lastPidResponseMillis(0) {
    memset(_supportedPids, 0x00, sizeof(_supportedPids));
}

OBD2Client::~OBD2Client() {
    can.attach(nullptr, mbed::CAN::RxIrq);
    can.attach(nullptr, mbed::CAN::TxIrq);
}

int OBD2Client::connect() {

    if (can.frequency(500E3)) {
        return 2;
    }

    /** Setup interrupt handlers */
    can.monitor(false);
    can.attach(mbed::callback(this, &OBD2Client::rx_handler), mbed::CAN::RxIrq);
    can.attach(mbed::callback(this, &OBD2Client::tx_handler), mbed::CAN::TxIrq);

    memset(_supportedPids, 0x00, sizeof(_supportedPids));

    // first try standard addressing
    _useExtendedAddressing = false;
    can.filter(0x7e8, 0x7FF, CANStandard);

    if (!supported_pids_read()) {
        // next try extended addressing
        _useExtendedAddressing = true;
        can.filter(0x18daf110, 0x1FFFFFFF, CANExtended);

        if (!supported_pids_read()) {
            return 1;
        }
    }

    return 0;
}

bool OBD2Client::is_pid_supported(uint8_t pid) {
    if (pid == 0) {
        return true;
    }

    return (_supportedPids[(pid - 1) / 0x20]
            & ((1UL << (31 - ((pid - 1) % 32))))) ? true : false;
}

bool OBD2Client::is_pid_value_raw(uint8_t pid) {
    switch (pid) {
    case PIDS_SUPPORT_01_20: // raw
    case MONITOR_STATUS_SINCE_DTCS_CLEARED: // raw
    case FREEZE_DTC: // raw
    case PIDS_SUPPORT_21_40: // raw
    case PIDS_SUPPORT_41_60: // raw
    case MONITOR_STATUS_THIS_DRIVE_CYCLE: // raw
    case FUEL_SYSTEM_STATUS: // raw
    case COMMANDED_SECONDARY_AIR_STATUS: // raw
    case OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO: // raw
    case OXYGEN_SENSORS_PRESENT_IN_2_BANKS: // raw
    case OXYGEN_SENSORS_PRESENT_IN_4_BANKS: // raw
    case AUXILIARY_INPUT_STATUS: // raw
    case FUEL_TYPE: // raw
    case EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED: // raw
        return true;

    default:
        return (pid > 0x5f);
    }
}

String OBD2Client::pid_name(uint8_t pid) {
    if (pid > 0x5f) {
        return "Unknown";
    }

    return PID_NAME_MAPPER[pid];
}

String OBD2Client::pid_units(uint8_t pid) {
    if (pid > 0x5f) {
        return "";
    }

    return PID_UNIT_MAPPER[pid];
}

float OBD2Client::read_pid(uint8_t pid) {
    if (!is_pid_supported(pid)) {
        return NAN;
    }

#define A value[0]
#define B value[1]
#define C value[2]
#define D value[3]
    uint8_t value[4];

    if (!pid_read(0x01, pid, &value, sizeof(value))) {
        return NAN;
    }

    switch (pid) {
    default:
    case PIDS_SUPPORT_01_20: // raw
    case MONITOR_STATUS_SINCE_DTCS_CLEARED: // raw
    case FREEZE_DTC: // raw
    case PIDS_SUPPORT_21_40: // raw
    case PIDS_SUPPORT_41_60: // raw
    case MONITOR_STATUS_THIS_DRIVE_CYCLE: // raw
        // NOTE: return value can lose precision!
        return ((uint32_t) A<< 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D);

        case FUEL_SYSTEM_STATUS: // raw
        case RUN_TIME_SINCE_ENGINE_START:
        case DISTANCE_TRAVELED_WITH_MIL_ON:
        case DISTANCE_TRAVELED_SINCE_CODES_CLEARED:
        case TIME_RUN_WITH_MIL_ON:
        case TIME_SINCE_TROUBLE_CODES_CLEARED:
        return (A * 256.0 + B);

        case CALCULATED_ENGINE_LOAD:
        case THROTTLE_POSITION:
        case COMMANDED_EGR:
        case COMMANDED_EVAPORATIVE_PURGE:
        case FUEL_TANK_LEVEL_INPUT:
        case RELATIVE_THROTTLE_POSITION:
        case ABSOLUTE_THROTTLE_POSITION_B:
        case ABSOLUTE_THROTTLE_POSITION_C:
        case ABSOLUTE_THROTTLE_POSITION_D:
        case ABSOLUTE_THROTTLE_POSITION_E:
        case ABSOLUTE_THROTTLE_POSITION_F:
        case COMMANDED_THROTTLE_ACTUATOR:
        case ETHANOL_FUEL_PERCENTAGE:
        case RELATIVE_ACCELERATOR_PEDAL_POSITTION:
        case HYBRID_BATTERY_PACK_REMAINING_LIFE:
        return (A / 2.55);

        case COMMANDED_SECONDARY_AIR_STATUS:// raw
        case OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO:// raw
        case OXYGEN_SENSORS_PRESENT_IN_2_BANKS:// raw
        case OXYGEN_SENSORS_PRESENT_IN_4_BANKS:// raw
        case AUXILIARY_INPUT_STATUS:// raw
        case FUEL_TYPE:// raw
        case EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED:// raw
        return (A);

        case OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM:
        case OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM:
        case OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM:
        case OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM:
        case OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM:
        case OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM:
        case OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM:
        case OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM:
        return ((B / 1.28) - 100.0);
        break;

        case ENGINE_COOLANT_TEMPERATURE:
        case AIR_INTAKE_TEMPERATURE:
        case AMBIENT_AIR_TEMPERATURE:
        case ENGINE_OIL_TEMPERATURE:
        return (A - 40.0);

        case SHORT_TERM_FUEL_TRIM_BANK_1:
        case LONG_TERM_FUEL_TRIM_BANK_1:
        case SHORT_TERM_FUEL_TRIM_BANK_2:
        case LONG_TERM_FUEL_TRIM_BANK_2:
        case EGR_ERROR:
        return ((A / 1.28) - 100.0);

        case FUEL_PRESSURE:
        return (A * 3.0);

        case INTAKE_MANIFOLD_ABSOLUTE_PRESSURE:
        case VEHICLE_SPEED:
        case WARM_UPS_SINCE_CODES_CLEARED:
        case ABSOLULTE_BAROMETRIC_PRESSURE:
        return (A);

        case ENGINE_RPM:
        return ((A * 256.0 + B) / 4.0);

        case TIMING_ADVANCE:
        return ((A / 2.0) - 64.0);

        case MAF_AIR_FLOW_RATE:
        return ((A * 256.0 + B) / 100.0);

        case FUEL_RAIL_PRESSURE:
        return ((A * 256.0 + B) * 0.079);

        case FUEL_RAIL_GAUGE_PRESSURE:
        case FUEL_RAIL_ABSOLUTE_PRESSURE:
        return ((A * 256.0 + B) * 10.0);

        case OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO:
        case OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO:
        case OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO:
        case OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO:
        case OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO:
        case OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO:
        case OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO:
        case OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3a:
        case 0x3b:
        return (((A * 256.0 + B) * 2.0) / 65536.0);

        case EVAP_SYSTEM_VAPOR_PRESSURE:
        return (((int16_t)(A * 256.0 + B)) / 4.0);

        case CATALYST_TEMPERATURE_BANK_1_SENSOR_1:
        case CATALYST_TEMPERATURE_BANK_2_SENSOR_1:
        case CATALYST_TEMPERATURE_BANK_1_SENSOR_2:
        case CATALYST_TEMPERATURE_BANK_2_SENSOR_2:
        return (((A * 256.0 + B) / 10.0) - 40.0);

        case CONTROL_MODULE_VOLTAGE:
        return ((A * 256.0 + B) / 1000.0);

        case ABSOLUTE_LOAD_VALUE:
        return ((A * 256.0 + B) / 2.55);

        case FUEL_AIR_COMMANDED_EQUIVALENCE_RATE:
        return (2.0 * (A * 256.0 + B) / 65536.0);

        case ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE:
        return ((A * 256.0 + B) / 200.0);

        case 0x54:
        return ((A * 256.0 + B) - 32767.0);

        case FUEL_INJECTION_TIMING:
        return (((A * 256.0 + B) / 128.0) - 210.0);

        case ENGINE_FUEL_RATE:
        return ((A * 256.0 + B) / 20.0);
    }
}

String OBD2Client::vin_read() {
    char vin[18];

    memset(vin, 0x00, sizeof(vin));

    if (!pid_read(0x09, 0x02, vin, 17)) {
        // failed
        return "";
    }

    return vin;
}

uint32_t OBD2Client::read_pid_raw(uint8_t pid) {
    if (!is_pid_supported(pid)) {
        return 0;
    }

#define A value[0]
#define B value[1]
#define C value[2]
#define D value[3]
    uint8_t value[4];

    if (!pid_read(0x01, pid, &value, sizeof(value))) {
        return 0;
    }

    switch (pid) {
    case COMMANDED_SECONDARY_AIR_STATUS:
    case OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO:
    case OXYGEN_SENSORS_PRESENT_IN_2_BANKS:
    case OXYGEN_SENSORS_PRESENT_IN_4_BANKS:
    case AUXILIARY_INPUT_STATUS:
    case FUEL_TYPE:
    case EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED:
        return (A);

        case FUEL_SYSTEM_STATUS:
        return ((uint32_t)A << 8 | (uint32_t)B);

        default:
        return ((uint32_t)A << 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D);
    }
}

String OBD2Client::ecu_name_read() {
    char ecuName[21];

    memset(ecuName, 0x00, sizeof(ecuName));

    if (!pid_read(0x09, 0x0a, ecuName, 20)) {
        // failed
        return "";
    }

    return ecuName;
}

void OBD2Client::set_timeout(unsigned long timeout) {
    _responseTimeout = timeout;
}

int OBD2Client::supported_pids_read() {
    for (int pid = 0x00; pid < 0xe0; pid += 0x20) {
        uint8_t value[4];

        if (pid_read(0x01, pid, value, sizeof(value)) != 4) {
            return 0;
        }

#define A value[0]
#define B value[1]
#define C value[2]
#define D value[3]
        _supportedPids[pid / 0x20] = ((uint32_t) A<< 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D << 0);

        if ((_supportedPids[pid / 0x20] & 0x00000001) == 0x00000000) {
            // no more
            break;
        }
    }

    return 1;
}

int OBD2Client::pid_read(uint8_t mode, uint8_t pid, void* data, int length) {

    /**
     * CAN-TP (the transport protocol in this case)
     * handles multi-frame packets by encoding the overall
     * length in the payload (data) of the first packet
     * in a multi-frame transfer
     *
     * Single Frame transfer format:
     * |-----------|------------|-------------|----------------------|
     * | Value     |    0x0     | Data Length |       (Varies)       |
     * |-----------|------------|-------------|----------------------|
     * | Bitfields | Bits 7...4 | Bits 3...0  |                      |
     * |-----------|--------------------------|----------------------|
     * | Byte Num  |          Byte 0          |    Bytes 1...7       |
     * |-----------|--------------------------|----------------------|
     *
     *  First Frame of multi-frame transfer format:
     * |-----------|------------|---------------------------|----------------|
     * | Value     |    0x1     | Len (11..8) | Len (7...0) |     (Varies)   |
     * |-----------|------------|-------------|-------------|----------------|
     * | Bitfields | Bits 7...4 | Bits 3...0  |             |                |
     * |-----------|--------------------------|-------------|----------------|
     * | Byte Num  |          Byte 0          |    Byte 1   | Bytes 2...7    |   |
     * |-----------|--------------------------|-------------|----------------|
     *
     *  Consecutive Frame of multi-frame transfer format:
     * |-----------|------------|----------------------------|
     * | Value     |    0x2     | Sequence Num | (Varies)    |
     * |-----------|------------|--------------|-------------|
     * | Bitfields | Bits 7...4 | Bits 3...0   |             |
     * |-----------|---------------------------|-------------|
     * | Byte Num  |          Byte 0           | Bytes 1...7 |
     * |-----------|---------------------------|-------------|
     *
     * There is another frame type (flow control) but I won't cover it here
     *
     * See more info at: https://piembsystech.com/can-tp-protocol/
     */

    // make sure at least 60 ms have passed since the last response
    // TODO - make this delay a timeout or something
    wait_us(60E3);

    // Format the message
    mbed::CANMessage tx_msg;
    tx_msg.id = 0x7df;         // 11-bit address by default
    if(_useExtendedAddressing) {
        tx_msg.id = 0x18db33f1;
    }
    tx_msg.len = 8;
    tx_msg.data[0] = 0x02; // number of additional bytes
    tx_msg.data[1] = mode;
    tx_msg.data[2] = pid;
    for(int i = 3; i < 8; i++) {
        tx_msg.data[i] = 0xCC; // Recommended to set unused bytes to 0xCC (ISO 15765-2)
    }

    tx_flag = false;

    //Attempt to write request to the CAN bus
    for(int retries = 10; retries > 0; retries--) {
        if(can.write(tx_msg)) {
            // send success
            break;
        } else if (retries <= 1) {
            return 0;
        }
    }

    /** Wait until the TX interrupt has occurred */
    while(!tx_flag) {
    }
    tx_flag = false;

    bool splitResponse = (length > 5);

    // Start the rx timeout
    timeout_passed = false;
    timeout.attach(mbed::callback(this, &OBD2Client::timeout_handler),
            _responseTimeout);

    // Attempt to read back a filtered message
    while(!timeout_passed) {
        mbed::CANMessage rx_msg;
        if(!can.read(rx_msg,
                (_useExtendedAddressing? extended_filter_handle : base_filter_handle))) {
            // Spin until we get a valid message
            continue;
        }

        // Make sure the message makes sense and reassemble packet

        // Super confusing due the way Arduino's CAN API works (get byte by byte)
        // TODO - rework
        int indx = 0;
        if(!((splitResponse ?
                ((rx_msg.data[indx++] == 0x10) && (rx_msg.data[indx++])) : rx_msg.data[indx++])
             &&  (rx_msg.data[indx++] == (mode | 0x40)) && (rx_msg.data[indx++]))) {
            // Invalid format, skip
            continue;
        }

        // Response is complete here, return
        if(!splitResponse) {
            memcpy(data, &rx_msg.data[indx], length);
            return length;
        }

        // Otherwise, copy the first 3 bytes
        memcpy(data, &rx_msg.data[indx], 3);

        wait_us(60E3);

        // Send the flow control frame to let the transmitter know we're ready
        tx_msg.data[0] = 0x30;
        memset(&tx_msg.data[1], 0, 7);

        tx_flag = false;

        // Send the request for the next chunk
        //Attempt to write request to the CAN bus
        for(int retries = 10; retries > 0; retries--) {
            if(can.write(tx_msg)) {
                // send success
                break;
            } else if (retries <= 1) {
                return 0;
            }
        }

        /** Wait until the TX interrupt has occurred */
        while(!tx_flag) {
        }
        tx_flag = false;

        // Wait for a response
        while(!timeout_passed) {
            if(!can.read(rx_msg,
              (_useExtendedAddressing? extended_filter_handle : base_filter_handle))) {
                // Skip the rest until we get a valid message
                continue;
            }

            // Verify sequence number
            if(!(rx_msg.data[0] == (0x21 + 1))) {
                continue;
            }

            // Copy the data into the buffer
            memcpy(&data[3], rx_msg.data, length-3);
            return length;
        }
    }
    return 0;
}

void OBD2Client::rx_handler() {
    rx_flag = true;
    if(rx_cb) {
        rx_cb();
    }
}

void OBD2Client::tx_handler() {
    tx_flag = true;
    if(tx_cb) {
        tx_cb();
    }
}


