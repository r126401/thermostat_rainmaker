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
#define SETPOINT_TEMPERATURE "Umbral"
#define CALIBRATE "Calibrado"
#define READ_INTERVAL "intervalo de lectura"
#define MARGIN_TEMPERATURE "margen de temperatura"
#define ID_SENSOR "id_sensor"
#define MODE "Modo"
#define NULSENSOR "Null"
#define ALARM  "alarm"
#define AUTO   "AUTO"
#define SELECT_MODE "SELECTMODE"
#define HEATING "Caldera"

#define TEXT_STATUS_APP_FACTORY "SIN CONFIGURAR"
#define TEXT_STATUS_APP_ERROR "ERROR"
#define TEXT_STATUS_APP_AUTO "AUTO"
#define TEXT_STATUS_APP_MANUAL "MANUAL"
#define TEXT_STATUS_APP_STARTING "INICIALIZANDO"
#define TEXT_STATUS_APP_CONNECTING  "CONECTANDO"
#define TEXT_STATUS_APP_SYNCING "SINCRONIZANDO"
#define TEXT_STATUS_APP_UPGRADING "ACTUALIZANDO"
#define TEXT_STATUS_APP_UNDEFINED "UNDEFINED"






//extern esp_rmaker_device_t *thermostat_device;












typedef struct app_params_t 
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


} app_params_t;


typedef enum status_app_t {

   STATUS_FACTORY,
   STATUS_ERROR,
   STATUS_AUTO,
   STATUS_MANUAL,
   STATUS_STARTING,
   STATUS_CONNECTING,
   STATUS_SYNC,
   STATUS_UPGRADING

} status_app_t;



/**
 * @brief update time valid in display
 * 
 * @param timevalid indicate if the time is valid in the device
 */
void update_time_valid(bool timevalid);

/**
 * @brief Update lcd disply every period of refreshing. Used por esp_timer
 * 
 * @param arg nos used
 */
void time_refresh(void *arg);

/**
 * @brief Execute reset to device
 * 
 */
void reset_device();
/**
 * @brief Execute factory reset to device
 * 
 */
void factory_reset_device();


/**
 * @brief Register all parameter in use in application
 * 
 * @param params 
 */
void register_parameters();

void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data);

void event_handler_sync (struct timeval *tv) ;
void create_task_thermostat();
void remove_task_thermostat();
bool is_task_thermostat_active();
char* status2mnemonic(status_app_t status);
void set_app_update_threshold(float threshold, bool reporting);
float get_app_current_temperature();
float get_app_current_threshold();
void set_app_status(status_app_t status);
status_app_t get_app_status();