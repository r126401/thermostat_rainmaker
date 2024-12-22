/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#pragma once
#include <stdint.h>
#include <stdbool.h>

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>
#include <esp_rmaker_console.h>
#include <esp_rmaker_ota.h>

#include <esp_rmaker_common_events.h>

#define DEFAULT_POWER  false
// Labels to params.
#define DEFAULT_TEMPERATURE 21.0
#define SETPOINT_TEMPERATURE "threshold"
#define CALIBRATE "calibrate"
#define READ_INTERVAL "read_interval"
#define MARGIN_TEMPERATURE "margin_temperature"
#define ID_SENSOR "id_sensor"
#define MODE "mode"
#define NULSENSOR "Null"
#define ALARM  "alarm"
#define AUTO   "AUTO"


#define STATUS_APP_ERROR "ERROR"
#define STATUS_APP_AUTO "AUTO"
#define STATUS_APP_MANUAL "MANUAL"
#define STATUS_APP_STARTING "STARTING"
#define STATUS_APP_SYNCING "SYNCING"
#define STATUS_APP_UPGRADING "UPGRADING"
#define STATUS_APP_UNDEFINED "UNDEFINED"



typedef enum ESTADO_RELE {
    INDETERMINADO = -1,
    OFF = 0,
    ON = 1
}ESTADO_RELE;

typedef enum TIPO_ACCION_TERMOSTATO {
	NO_ACCIONAR_TERMOSTATO,
	ACCIONAR_TERMOSTATO,
   NINGUNA_ACCION
}TIPO_ACCION_TERMOSTATO;

typedef enum DEVICE_STATUS {

   DEVICE_OK,
   SENSOR_FAIL
} DEVICE_STATUS;


extern esp_rmaker_device_t *thermostat_device;
void app_driver_init(void);

bool app_driver_get_state(void);
enum ESTADO_RELE relay_operation(ESTADO_RELE op);
ESTADO_RELE get_status_relay();
void gpio_rele_in_out();








typedef struct app_params 
{
   esp_rmaker_param_t *mode;
   esp_rmaker_param_t *temperature;
   esp_rmaker_param_t *threshold;
   esp_rmaker_param_t *calibrate;
   esp_rmaker_param_t *read_interval;
   esp_rmaker_param_t *power;
   esp_rmaker_param_t *margin_temperature;
   esp_rmaker_param_t *sensor;
   esp_rmaker_param_t *alarm;
   esp_rmaker_param_t *programacion;


} app_params;


typedef enum status_app_t {

   STATUS_ERROR,
   STATUS_AUTO,
   STATUS_MANUAL,
   STATUS_STARTING,
   STATUS_SYNC,
   STATUS_UPGRADING

} status_app_t;





void update_time_valid(bool timevalid);
void time_refresh(void *arg);
void reset_device();
void factory_reset_device();
