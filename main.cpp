/*
 * main.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: gdbeckstein
 */

#include "platform/mbed_wait_api.h"
#include "platform/Callback.h"

#include "drivers/CAN.h"
#include "drivers/DigitalOut.h"

#include "OBD2.h"

mbed::CAN can_bus(MBED_CONF_TCAN4551_DEFAULT_TCAN_MISO, MBED_CONF_TCAN4551_DEFAULT_TCAN_MOSI);

mbed::DigitalOut led1(LED1, 1);
mbed::DigitalOut led2(LED2, 1);

OBD2Client obd2_client(can_bus);

// array of PID's to print values of
const int PIDS[] = {
  CALCULATED_ENGINE_LOAD,
  ENGINE_COOLANT_TEMPERATURE,
  ENGINE_RPM,
  VEHICLE_SPEED,
  AIR_INTAKE_TEMPERATURE,
  MAF_AIR_FLOW_RATE,
  THROTTLE_POSITION,
  RUN_TIME_SINCE_ENGINE_START,
  FUEL_TANK_LEVEL_INPUT,
  ABSOLULTE_BAROMETRIC_PRESSURE,
  ABSOLUTE_LOAD_VALUE,
  RELATIVE_THROTTLE_POSITION
};

const int NUM_PIDS = sizeof(PIDS) / sizeof(PIDS[0]);

void print_pid(int pid);

int main(void) {

    // Hook up LED blink handler for RX
    obd2_client.on_rx(mbed::Callback<void(void)>([] {
            led1 = !led1; // Toggle led1
    }));

    obd2_client.on_tx(mbed::Callback<void(void)>([] {
            led2 = !led2; // Toggle led2
    }));

    while(true) {
        printf("Attempting to connect to OBD2 CAN bus...");
        if(obd2_client.connect()) {
            printf("success!\r\n");
            break;
        } else {
            printf("failed!\r\n");
            wait_us(1E6); // Wait one second
        }
    }

    printf("Supported PIDs:\r\n");
    // Print out the names of all supported PIDs
    for(int pid = 0; pid < 96; pid++) {
        if(obd2_client.is_pid_supported(pid)) {
            printf("PID %i - %s\r\n", pid, OBD2Client::pid_name(pid).c_str());
        }
    }

    // Print out the VIN number and the ECU name
    printf("VIN Number: %s\r\n", obd2_client.vin_read().c_str());
    printf("ECU Name: %s\r\n", obd2_client.ecu_name_read().c_str());

    while(true) {
        for(int i = 0; i < NUM_PIDS; i++) {
            int pid = PIDS[i];

            print_pid(pid);
        }
        wait_us(1E6);
    }
}

void print_pid(int pid) {

    printf("%s = ", OBD2Client::pid_name(pid).c_str());

    float value = obd2_client.read_pid(pid);

    printf("%.2f %s\r\n", value, OBD2Client::pid_units(pid).c_str());

}


