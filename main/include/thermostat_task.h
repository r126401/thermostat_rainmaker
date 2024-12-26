
#pragma once

#include "esp_err.h"




typedef enum STATUS_RELAY {
    INDETERMINADO = -1,
    OFF = 0,
    ON = 1
}STATUS_RELAY;

typedef enum THERMOSTAT_ACTION {
	NO_TOGGLE_THERMOSTAT,
	TOGGLE_THERMOSTAT,
   NO_ACTION_THERMOSTAT
}THERMOSTAT_ACTION;

typedef enum DEVICE_STATUS {

   DEVICE_OK,
   SENSOR_FAIL
} DEVICE_STATUS;





void task_iotThermostat();
THERMOSTAT_ACTION thermostat_action(float current_temperature);
STATUS_RELAY get_status_relay();
enum STATUS_RELAY relay_operation(STATUS_RELAY op);
#define TRAZAR "%s:%s:%d-->"
#define INFOTRAZA get_current_date(-1), __func__, __LINE__

