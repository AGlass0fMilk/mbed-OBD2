/*
 * Copyright (c) Sandeep Mistry. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 *
 * Modified and ported to Mbed OS by George Beckstein for Embedded Planet, Inc
 */

#ifndef OBD2_H
#define OBD2_H

#include "drivers/CAN.h"
#include "drivers/Timeout.h"

#include "platform/Callback.h"

#include <string>

typedef std::string String;

enum {
  PIDS_SUPPORT_01_20                                = 0x00,
  MONITOR_STATUS_SINCE_DTCS_CLEARED                 = 0x01,
  FREEZE_DTC                                        = 0x02,
  FUEL_SYSTEM_STATUS                                = 0x03,
  CALCULATED_ENGINE_LOAD                            = 0x04,
  ENGINE_COOLANT_TEMPERATURE                        = 0x05,
  SHORT_TERM_FUEL_TRIM_BANK_1                       = 0x06,
  LONG_TERM_FUEL_TRIM_BANK_1                        = 0x07,
  SHORT_TERM_FUEL_TRIM_BANK_2                       = 0x08,
  LONG_TERM_FUEL_TRIM_BANK_2                        = 0x09,
  FUEL_PRESSURE                                     = 0x0a,
  INTAKE_MANIFOLD_ABSOLUTE_PRESSURE                 = 0x0b,
  ENGINE_RPM                                        = 0x0c,
  VEHICLE_SPEED                                     = 0x0d,
  TIMING_ADVANCE                                    = 0x0e,
  AIR_INTAKE_TEMPERATURE                            = 0x0f,
  MAF_AIR_FLOW_RATE                                 = 0x10,
  THROTTLE_POSITION                                 = 0x11,
  COMMANDED_SECONDARY_AIR_STATUS                    = 0x12,
  OXYGEN_SENSORS_PRESENT_IN_2_BANKS                 = 0x13,
  OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM              = 0x14,
  OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM              = 0x15,
  OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM              = 0x16,
  OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM              = 0x17,
  OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM              = 0x18,
  OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM              = 0x19,
  OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM              = 0x1a,
  OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM              = 0x1b,
  OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO            = 0x1c,
  OXYGEN_SENSORS_PRESENT_IN_4_BANKS                 = 0x1d,
  AUXILIARY_INPUT_STATUS                            = 0x1e,
  RUN_TIME_SINCE_ENGINE_START                       = 0x1f,

  PIDS_SUPPORT_21_40                                = 0x20,
  DISTANCE_TRAVELED_WITH_MIL_ON                     = 0x21,
  FUEL_RAIL_PRESSURE                                = 0x22,
  FUEL_RAIL_GAUGE_PRESSURE                          = 0x23,
  OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x24,
  OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x25,
  OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x26,
  OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x27,
  OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x28,
  OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x29,
  OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2a,
  OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2b,
  COMMANDED_EGR                                     = 0x2c,
  EGR_ERROR                                         = 0x2d,
  COMMANDED_EVAPORATIVE_PURGE                       = 0x2e,
  FUEL_TANK_LEVEL_INPUT                             = 0x2f,
  WARM_UPS_SINCE_CODES_CLEARED                      = 0x30,
  DISTANCE_TRAVELED_SINCE_CODES_CLEARED             = 0x31,
  EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x32,
  ABSOLULTE_BAROMETRIC_PRESSURE                     = 0x33,
/*OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x34,
  OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x35,
  OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x36,
  OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x37,
  OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x38,
  OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x39,
  OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3a,
  OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3b,*/
  CATALYST_TEMPERATURE_BANK_1_SENSOR_1              = 0x3c,
  CATALYST_TEMPERATURE_BANK_2_SENSOR_1              = 0x3d,
  CATALYST_TEMPERATURE_BANK_1_SENSOR_2              = 0x3e,
  CATALYST_TEMPERATURE_BANK_2_SENSOR_2              = 0x3f,

  PIDS_SUPPORT_41_60                                = 0x40,
  MONITOR_STATUS_THIS_DRIVE_CYCLE                   = 0x41,
  CONTROL_MODULE_VOLTAGE                            = 0x42,
  ABSOLUTE_LOAD_VALUE                               = 0x43,
  FUEL_AIR_COMMANDED_EQUIVALENCE_RATE               = 0x44,
  RELATIVE_THROTTLE_POSITION                        = 0x45,
  AMBIENT_AIR_TEMPERATURE                           = 0x46,
  ABSOLUTE_THROTTLE_POSITION_B                      = 0x47,
  ABSOLUTE_THROTTLE_POSITION_C                      = 0x48,
  ABSOLUTE_THROTTLE_POSITION_D                      = 0x49,
  ABSOLUTE_THROTTLE_POSITION_E                      = 0x4a,
  ABSOLUTE_THROTTLE_POSITION_F                      = 0x4b,
  COMMANDED_THROTTLE_ACTUATOR                       = 0x4c,
  TIME_RUN_WITH_MIL_ON                              = 0x4d,
  TIME_SINCE_TROUBLE_CODES_CLEARED                  = 0x4e,
/*                                                  = 0x4f,
                                                    = 0x50,*/
  FUEL_TYPE                                         = 0x51,
  ETHANOL_FUEL_PERCENTAGE                           = 0x52,
  ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE               = 0x53,
/*EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x54,*/
/*                                                  = 0x55,
                                                    = 0x56,
                                                    = 0x57,
                                                    = 0x58,*/
  FUEL_RAIL_ABSOLUTE_PRESSURE                       = 0x59,
  RELATIVE_ACCELERATOR_PEDAL_POSITTION              = 0x5a,
  HYBRID_BATTERY_PACK_REMAINING_LIFE                = 0x5b,
  ENGINE_OIL_TEMPERATURE                            = 0x5c,
  FUEL_INJECTION_TIMING                             = 0x5d,
  ENGINE_FUEL_RATE                                  = 0x5e,
  EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED = 0x5f,

  // more PIDs can be added from: https://en.wikipedia.org/wiki/OBD-II_PIDs
};

// default timeout for a response in milliseconds
#define OBD2_DEFAULT_TIMEOUT 2000

class OBD2Client {
public:

    /**
     * Construct an OBD2 client with the given CAN interface
     * @param[in] interface CAN bus interface for the client to use
     */
    OBD2Client(mbed::CAN& interface);

    virtual ~OBD2Client();

    /**
     * Initialize the client and attempt to connect
     * @retval 0 on success, error otherwise
     */
    int connect();

    /**
     * Check if the connected ECU supports the given PID
     * @param[in] pid Desired PID
     * @retval true if given PID is supported by ECU
     */
    bool is_pid_supported(uint8_t pid);

    /**
     * Check if the given PID is reported in raw units
     * @param[in] pid Desired PID
     * @retval true if the library does NOT support converting the PID value
     */
    bool is_pid_value_raw(uint8_t pid);

    /**
     * Get the readable name of the given PID
     * @param[in] pid Desired PID
     * @retval Readable name of given PID
     */
    String pid_name(uint8_t pid);

    /**
     * Get the readable units of the given PID
     * @param[in] pid Desired PID
     * @retval Readable units of the given PID
     */
    String pid_units(uint8_t pid);

    /**
     * Get the value of the given PID
     * @param[in] pid Desired PID
     * @retval Returns the value of the PID as a float or NAN on error
     */
    float read_pid(uint8_t pid);

    /**
     * Get the value of the given PID in raw format
     * @param[in] pid Desired PID
     * @retval returns the value of the PID in raw format
     */
    uint32_t read_pid_raw(uint8_t pid);

    /**
     * Get the vehicle's VIN number
     * @retval VIN number or empty string on failure
     */
    String vin_read();

    /**
     * Get the name of the connected ECU
     * @retval Name of connected ECU, empty string on failure
     */
    String ecu_name_read();

    /**
     * Set the response timeout in milliseconds
     * @param[in] timeout Timeout in milliseconds
     */
    void set_timeout(unsigned long timeout);

    /**
     * Attach a callback to be executed when the CAN bus receives a message
     * @param[in] handler Handler to be called
     */
    void on_rx(mbed::Callback<void(void)> handler) {
        rx_cb = handler;
    }

    /**
     * Attach a callback to be executed when the CAN bus transmits a message
     * @param[in] handler Handler to be called
     */
    void on_tx(mbed::Callback<void(void)> handler) {
        tx_cb = handler;
    }

protected:
    int supported_pids_read();

    int pid_read(uint8_t mode, uint8_t pid, void* data, int length);

    void rx_handler();

    void tx_handler();

    void timeout_handler() {
        timeout_passed = true;
    }


protected:

    mbed::CAN can;                      /** CAN interface handle */
    int base_filter_handle;             /** Handle to base filter */
    int extended_filter_handle;         /** Handle to extended filter */
    mbed::Callback<void(void)> rx_cb;   /** Application RX callback */
    mbed::Callback<void(void)> tx_cb;   /** Application TX callback */

    volatile bool rx_flag;          /** RX interrupt happened */
    volatile bool tx_flag;          /** TX interrupt happened */
    volatile bool timeout_passed;   /** Timeout occurred */

    mbed::Timeout timeout;          /** Timeout ticker */


    unsigned long _responseTimeout;
    bool _useExtendedAddressing;
    unsigned long _lastPidResponseMillis;
    uint32_t _supportedPids[32];
};

#endif
