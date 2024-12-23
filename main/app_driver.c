/* Switch demo implementation using button and RGB LED
   
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <sdkconfig.h>
#include <iot_button.h>
#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_params.h> 
#include "esp_log.h"
#include "lv_main_thermostat.h"
#include "thermostat_task.h"
#include "events_app.h"
#include "app_main.h"


static const char *TAG = "app_driver";
extern esp_rmaker_device_t *thermostat_device;
float current_threshold = 21.5;






ESTADO_RELE get_status_relay() {

    return (gpio_get_level(CONFIG_RELAY_GPIO));
}





enum ESTADO_RELE IRAM_ATTR relay_operation(ESTADO_RELE op) {

    event_lcd_t event;
    event.event_type = UPDATE_HEATING;
	
	if (gpio_get_level(CONFIG_RELAY_GPIO) == OFF){
		if (op == ON) {
			gpio_set_level(CONFIG_RELAY_GPIO, op);
			ESP_LOGE(TAG, "Accion: OFF->ON");
            esp_rmaker_param_update_and_report(
                esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME),
                esp_rmaker_bool(op));

		} else {
			ESP_LOGE(TAG, "Accion: OFF->OFF");
			}
	} else {

		if (op == ON) {
			ESP_LOGE(TAG, "Accion: ON->ON");
		} else {
			gpio_set_level(CONFIG_RELAY_GPIO, op);
			ESP_LOGE(TAG, "Accion: ON->OFF");
            esp_rmaker_param_update_and_report(
                esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME),
                esp_rmaker_bool(op));

			}
	}

    if (op == ON) {
        event.status = true;
    } else {
        event.status = false;
    }

   send_event(event);

    //lv_update_heating(event.status);
    //lv_timer_handler();

	return gpio_get_level(CONFIG_RELAY_GPIO);
}



void register_parameters(app_params_t *params) 

{


    /**
     * Create temperature param
     */
    esp_rmaker_device_add_param(thermostat_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Thermostat"));

    params->temperature = esp_rmaker_temperature_param_create(ESP_RMAKER_DEF_TEMPERATURE_NAME, DEFAULT_TEMPERATURE);
    esp_rmaker_device_add_param(thermostat_device, params->temperature);
    esp_rmaker_device_assign_primary_param(thermostat_device, params->temperature);

    /**
     * Create threshold param
     */
    //params->threshold = esp_rmaker_schedules_param_create(SETPOINT_TEMPERATURE, 10);
    ESP_LOGE(TAG, "CURRENT_THRESHOLD VALE %.1f", current_threshold);
    params->threshold = esp_rmaker_param_create(SETPOINT_TEMPERATURE, NULL, esp_rmaker_float(current_threshold), PROP_FLAG_READ | PROP_FLAG_WRITE | PROP_FLAG_PERSIST);
    esp_rmaker_device_add_param(thermostat_device, params->threshold);
    esp_rmaker_param_add_ui_type(params->threshold, ESP_RMAKER_UI_SLIDER);
    esp_rmaker_param_add_bounds(params->threshold, esp_rmaker_float(10), esp_rmaker_float(30), esp_rmaker_float(0.5));
 


    
    /**
     * Create calibrate param
     */

    params->calibrate = esp_rmaker_param_create(CALIBRATE, NULL, esp_rmaker_float(-2.0),PROP_FLAG_WRITE |  PROP_FLAG_READ);
    esp_rmaker_param_add_ui_type(params->calibrate, ESP_RMAKER_UI_HIDDEN);
    esp_rmaker_device_add_param(thermostat_device, params->calibrate);

    /**
     * Create read interval param
     */
    params->read_interval = esp_rmaker_param_create(READ_INTERVAL, NULL, esp_rmaker_int(60), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_device_add_param(thermostat_device, params->read_interval);

    /**
     * Create power param
     */
    params->power = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_device_add_param(thermostat_device, params->power);

    /**
     * Create margin temperature. Its used to switch on/off thermostat in order direcction of temperature
     */
    params->margin_temperature = esp_rmaker_param_create(MARGIN_TEMPERATURE, NULL, esp_rmaker_float(0.5), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_device_add_param(thermostat_device, params->margin_temperature);

    /**
     * Create temperature sensor. If sensor is empty, sensor is into device. If sensor is a mac, sensor is remote.
     */

    params->sensor = esp_rmaker_param_create(ID_SENSOR, NULL, esp_rmaker_str(NULSENSOR), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_param_add_ui_type(params->sensor, ESP_RMAKER_UI_QR_SCAN);
    esp_rmaker_device_add_param(thermostat_device, params->sensor);

    /**
     * Create mode thermostat
     */
    static const char *list[] = {STATUS_APP_ERROR, STATUS_APP_AUTO, STATUS_APP_MANUAL, STATUS_APP_STARTING, STATUS_APP_SYNCING, STATUS_APP_UPGRADING, STATUS_APP_UNDEFINED};
    params->mode = esp_rmaker_param_create(MODE, NULL, esp_rmaker_str(STATUS_APP_STARTING), PROP_FLAG_READ);
    esp_rmaker_param_add_valid_str_list(params->mode, list, 7);
    esp_rmaker_device_add_param(thermostat_device, params->mode);

    /**
     * Create alarm sensor
     */
    params->alarm = esp_rmaker_param_create(ALARM, NULL, esp_rmaker_int(0), PROP_FLAG_READ);
    esp_rmaker_device_add_param(thermostat_device, params->alarm);


    esp_rmaker_system_serv_config_t system_serv_config = {
     .flags = SYSTEM_SERV_FLAGS_ALL,
     .reboot_seconds = 2,
     .reset_seconds = 2,
     .reset_reboot_seconds = 2
};

esp_rmaker_system_service_enable(&system_serv_config);


}
