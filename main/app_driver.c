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
#include "cJSON.h"
#include <esp_rmaker_common_events.h>

#include <app_network.h>
#include <app_insights.h>

#include "app_main.h"
#include "mqtt_client.h"
#include "alarms_app.h"
#include "esp_rmaker_mqtt_glue.h"
#include "esp_rmaker_mqtt.h"
#include "esp_err.h"
#include "events_lcd.h"
#include "lv_factory_thermostat.h"


#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>
#include <esp_rmaker_console.h>
#include <esp_rmaker_ota.h>
#include <esp_rmaker_utils.h>

static const char *TAG = "app_driver";
extern esp_rmaker_device_t *thermostat_device;
float current_threshold = 21.5;
char *text_qrcode = NULL;

static status_app_t status_app;

TaskHandle_t thermostat_handle = NULL;

const esp_timer_create_args_t text_date_shot_timer_args = {
    .callback = &time_refresh,
    /* name is optional, but may help identify the timer when debugging */
    .name = "time refresh date text"
};

void timer_upgrade_cb(void *arg);

const esp_timer_create_args_t shot_upgrade_args = {

    .callback = &timer_upgrade_cb,
    .name = "Timer to upgrade"

};


static esp_timer_handle_t timer_date_text;
static esp_timer_handle_t timer_upgrade;




STATUS_RELAY get_status_relay() {

    return (gpio_get_level(CONFIG_RELAY_GPIO));
}





enum STATUS_RELAY IRAM_ATTR relay_operation(STATUS_RELAY op) {

	
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



    set_lcd_update_heating(op);


	return gpio_get_level(CONFIG_RELAY_GPIO);
}



void register_parameters() 

{

    esp_rmaker_param_t *param;

    /**
     * Create temperature param
     */
    esp_rmaker_device_add_param(thermostat_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Thermostat"));

    param = esp_rmaker_temperature_param_create(ESP_RMAKER_DEF_TEMPERATURE_NAME, DEFAULT_TEMPERATURE);
    esp_rmaker_device_add_param(thermostat_device, param);
    esp_rmaker_device_assign_primary_param(thermostat_device, param);

    /**
     * Create threshold param
     */
    //params->threshold = esp_rmaker_schedules_param_create(SETPOINT_TEMPERATURE, 10);
    ESP_LOGE(TAG, "CURRENT_THRESHOLD VALE %.1f", current_threshold);
    param = esp_rmaker_param_create(SETPOINT_TEMPERATURE, NULL, esp_rmaker_float(current_threshold), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_device_add_param(thermostat_device, param);
    esp_rmaker_param_add_ui_type(param, ESP_RMAKER_UI_SLIDER);
    esp_rmaker_param_add_bounds(param, esp_rmaker_float(10), esp_rmaker_float(30), esp_rmaker_float(0.5));
 


    
    /**
     * Create calibrate param
     */

    param = esp_rmaker_param_create(CALIBRATE, NULL, esp_rmaker_float(-2.0),PROP_FLAG_WRITE |  PROP_FLAG_READ);
    esp_rmaker_param_add_ui_type(param, ESP_RMAKER_UI_HIDDEN);
    esp_rmaker_device_add_param(thermostat_device, param);

    /**
     * Create read interval param
     */
    param = esp_rmaker_param_create(READ_INTERVAL, NULL, esp_rmaker_int(60), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_device_add_param(thermostat_device, param);

    /**
     * Create power param
     */
    param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_device_add_param(thermostat_device, param);

    /**
     * Create margin temperature. Its used to switch on/off thermostat in order direcction of temperature
     */
    param = esp_rmaker_param_create(MARGIN_TEMPERATURE, NULL, esp_rmaker_float(0.5), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_device_add_param(thermostat_device, param);

    /**
     * Create temperature sensor. If sensor is empty, sensor is into device. If sensor is a mac, sensor is remote.
     */

    param = esp_rmaker_param_create(ID_SENSOR, NULL, esp_rmaker_str(NULSENSOR), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_param_add_ui_type(param, ESP_RMAKER_UI_QR_SCAN);
    esp_rmaker_device_add_param(thermostat_device, param);

    /**
     * Create mode thermostat
     */
    static const char *list[] = {TEXT_STATUS_APP_ERROR, TEXT_STATUS_APP_AUTO, TEXT_STATUS_APP_MANUAL, TEXT_STATUS_APP_STARTING, TEXT_STATUS_APP_CONNECTING, TEXT_STATUS_APP_UPGRADING, TEXT_STATUS_APP_UNDEFINED};
    param = esp_rmaker_param_create(MODE, NULL, esp_rmaker_str(TEXT_STATUS_APP_STARTING), PROP_FLAG_READ);
    esp_rmaker_param_add_valid_str_list(param, list, 7);
    esp_rmaker_device_add_param(thermostat_device, param);

    /**
     * Create alarm sensor
     */
    param = esp_rmaker_param_create(ALARM, NULL, esp_rmaker_int(0), PROP_FLAG_READ);
    esp_rmaker_device_add_param(thermostat_device, param);


    esp_rmaker_system_serv_config_t system_serv_config = {
     .flags = SYSTEM_SERV_FLAGS_ALL,
     .reboot_seconds = 2,
     .reset_seconds = 2,
     .reset_reboot_seconds = 2
};

esp_rmaker_system_service_enable(&system_serv_config);


}






static void timer_delay_next_schedule(void *arg) {

    lv_update_lcd_schedule(true);
    ESP_LOGI(TAG, "UPDATE LCD SCHEDULE EJECUTADO DESPUES DE UNA OPERACION CON LOS SCHEDULES");

}




static void topic_cb (const char *topic, void *payload, size_t payload_len, void *priv_data) {

    cJSON *json;
    cJSON *schedules;
    esp_timer_handle_t timer_update_lcd;

    const esp_timer_create_args_t update_lcd_schedules_shot_timer_args = {
    .callback = &timer_delay_next_schedule,
    /* name is optional, but may help identify the timer when debugging */
    .name = "time refresh date text"
};

    
    json = cJSON_Parse((char*) payload);

    if (json == NULL) {
        ESP_LOGW(TAG, "El payload recibido no es json");
        return;
    }

    schedules = cJSON_GetObjectItem(json, "Schedule");
    if (schedules != NULL) {

        ESP_LOGW(TAG, "Se ha encontrado una operacion de schedules");
        esp_timer_create(&update_lcd_schedules_shot_timer_args, &timer_update_lcd);
        esp_timer_start_once(timer_update_lcd, 1000000);
    } else {
        ESP_LOGE(TAG, "No Se ha encontrado una operacion de schedules");
    }


    /**
     * Es necesario extraer la info para refrescar el schedule de la pantalla.
     * {"Schedule":{"Schedules":[{"id":"GO41","operation":"enable"}]}}
     */

    ESP_LOGE(TAG, "Se ha recibido informacion: %.*s", payload_len, (char*) payload);
    
    



}


void timer_upgrade_cb(void *arg) {

    static int cursor = 0;
    cursor++;
    set_lcd_update_upgrade_firmware("Actualizando...", cursor);

}





/* Event handler for catching RainMaker events */
void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{





    ESP_LOGW(TAG, "RECIBIDO EVENTO %s, EVENTID %d ", event_base, (int) event_id);
    
    if (event_base == RMAKER_EVENT) {
        switch (event_id) {
            case RMAKER_EVENT_INIT_DONE:
                ESP_LOGI(TAG, "RainMaker Initialised.");
                set_app_status(STATUS_CONNECTING);
                break;
            case RMAKER_EVENT_CLAIM_STARTED:
                //No lo he visto salir nunca
                ESP_LOGI(TAG, "RainMaker Claim Started.");
                break;
            case RMAKER_EVENT_CLAIM_SUCCESSFUL:
                //No lo he visto salir nunca
                ESP_LOGI(TAG, "RainMaker Claim Successful.");
                break;
            case RMAKER_EVENT_CLAIM_FAILED:
                ESP_LOGI(TAG, "RainMaker Claim Failed.");
                set_lcd_update_error_factory();
                break;
            case RMAKER_EVENT_LOCAL_CTRL_STARTED:
                ESP_LOGI(TAG, "Local Control Started.");
                //Esto debemos hacerlo si venimos del factory
                if (get_app_status() == STATUS_FACTORY) {

                    set_app_status(STATUS_CONNECTING);
                    set_lcd_update_qr_confirmed();
                    set_lcd_update_button_instalation(false);
                    lv_cancel_timer_factory();
                    if (!is_task_thermostat_active()) {
                        ESP_LOGW(TAG, "Se crea la tarea porque no estaba creada");
                        create_task_thermostat();
                    }
                    
                }
 
                free(text_qrcode);


                break;
            case RMAKER_EVENT_LOCAL_CTRL_STOPPED:
                ESP_LOGI(TAG, "Local Control Stopped.");
                break;
            default:
                ESP_LOGW(TAG, "Unhandled RainMaker Event: %"PRIi32, event_id);
        }
    } else if (event_base == RMAKER_COMMON_EVENT) {

 
        switch (event_id) {
        
            case RMAKER_EVENT_REBOOT:
                ESP_LOGI(TAG, "Rebooting in %d seconds.", *((uint8_t *)event_data));
                break;
            case RMAKER_EVENT_WIFI_RESET:
                ESP_LOGI(TAG, "Wi-Fi credentials reset.");
                break;
            case RMAKER_EVENT_FACTORY_RESET:
                ESP_LOGI(TAG, "Node reset to factory defaults.");
                break;
            case RMAKER_MQTT_EVENT_CONNECTED:
                ESP_LOGI(TAG, "MQTT Connected.");
                char *id_node = esp_rmaker_get_node_id();
                char topic[80] = {0};
                sprintf(topic, "node/%s/params/remote", id_node);
                ESP_LOGW(TAG, "Suscrito al topic: %s", topic);
                esp_err_t error = esp_rmaker_mqtt_subscribe(topic, topic_cb, 0, NULL);

                if (error == ESP_OK) {
                    ESP_LOGE(TAG, "Bien suscrito");
                } else {
                    ESP_LOGE(TAG, "Mal suscrito");
                }
                set_lcd_update_broker_status(true);
                set_alarm(MQTT_ALARM, ALARM_APP_OFF);
                set_app_status(STATUS_SYNC);
 

                break;
            case RMAKER_MQTT_EVENT_DISCONNECTED:
                ESP_LOGI(TAG, "MQTT Disconnected.");
                set_lcd_update_broker_status(false);
                set_alarm(MQTT_ALARM, ALARM_APP_ON);

                break;
            case RMAKER_MQTT_EVENT_PUBLISHED:
                ESP_LOGI(TAG, "MQTT Published. Msg id: %d.", *((int *)event_data));
                break;
            default:
                ESP_LOGW(TAG, "Unhandled RainMaker Common Event: %"PRIi32, event_id);
        }
    } else if (event_base == APP_NETWORK_EVENT) {
    
        switch (event_id) {
            case APP_NETWORK_EVENT_QR_DISPLAY:
                if (text_qrcode == NULL) {
                    text_qrcode = (char*) calloc(strlen(event_data) + 1, sizeof(char));
                }
                strncpy(text_qrcode, event_data, strlen(event_data));
                ESP_LOGI(TAG, "Provisioning QR : %s", text_qrcode);

                send_event_app_factory();

                break;
            case APP_NETWORK_EVENT_PROV_TIMEOUT:
                ESP_LOGI(TAG, "Provisioning Timed Out. Please reboot.");
                break;
            case APP_NETWORK_EVENT_PROV_RESTART:
                ESP_LOGI(TAG, "Provisioning has restarted due to failures.");
                break;
            default:
                ESP_LOGW(TAG, "Unhandled App Wi-Fi Event: %"PRIi32, event_id);
                break;
        }
    } else if (event_base == RMAKER_OTA_EVENT) {
        switch(event_id) {
            case RMAKER_OTA_EVENT_STARTING:
                ESP_LOGI(TAG, "Starting OTA.");
                remove_task_thermostat();
                esp_timer_create(&shot_upgrade_args, &timer_upgrade);
                lv_upgrade_firmware("Preparando OTA", 0);
                
                
                break;
            case RMAKER_OTA_EVENT_IN_PROGRESS:
                ESP_LOGI(TAG, "OTA is in progress.");
                esp_timer_start_periodic(timer_upgrade, 1000000);
                break;
            case RMAKER_OTA_EVENT_SUCCESSFUL:
                ESP_LOGI(TAG, "OTA successful.");
                esp_timer_stop(timer_upgrade);
                esp_timer_delete(timer_upgrade);
                lv_upgrade_firmware("Actualizado con exito", 100);

                break;
            case RMAKER_OTA_EVENT_FAILED:
                ESP_LOGI(TAG, "OTA Failed.");
                esp_timer_stop(timer_upgrade);
                esp_timer_delete(timer_upgrade);
                lv_upgrade_firmware("Fallo la actualizacion", 100);

                break;
            case RMAKER_OTA_EVENT_REJECTED:
                ESP_LOGI(TAG, "OTA Rejected.");
                break;
            case RMAKER_OTA_EVENT_DELAYED:
                ESP_LOGI(TAG, "OTA Delayed.");
                break;
            case RMAKER_OTA_EVENT_REQ_FOR_REBOOT:
                ESP_LOGI(TAG, "Firmware image downloaded. Please reboot your device to apply the upgrade.");
                break;
            default:
                ESP_LOGW(TAG, "Unhandled OTA Event: %"PRIi32, event_id);
                break;
        }
    } else {
        ESP_LOGW(TAG, "Invalid event received!");
    }
}



static bool get_current_date(uint32_t *hour, uint32_t *min, uint32_t *sec) {

    time_t now;
	struct tm fecha;
    time(&now);
    localtime_r(&now, &fecha);

    *hour = fecha.tm_hour;
    *min = fecha.tm_min;
    *sec = fecha.tm_sec;

    return true;


}


void update_time_valid(bool timevalid) {


    uint32_t hour;
    uint32_t min;
    uint32_t sec;
    uint32_t resto = 0;
    static bool sync = false;


    if (timevalid) {



        if (!sync) {
            get_current_date(&hour, &min, &sec);
            ESP_ERROR_CHECK(esp_timer_create(&text_date_shot_timer_args, &timer_date_text));
            resto = 60 - sec;
            ESP_ERROR_CHECK(esp_timer_start_once(timer_date_text, (resto * 1000000)));
            ESP_LOGI(TAG, "Actualizada la hora: %02d:%02d. Proximo intervalo :%d segundos", (int) hour, (int) min, (int) resto);

            sync = true;

            set_lcd_update_time(hour, min);
            lv_update_lcd_schedule(true);

        } 

    } else {
        set_lcd_update_time(-1, -1);
    }




}


char* get_date_now() {

	static char fecha_actual[6] = {0};

	time_t now;
	struct tm fecha;
	//ESP_LOGI(TAG, ""TRAZAR"ACTUALIZAR_HORA", INFOTRAZA);
    time(&now);
    localtime_r(&now, &fecha);


	sprintf(fecha_actual, "%02d:%02d",fecha.tm_min,fecha.tm_sec);

	return fecha_actual;

}



void time_refresh(void *arg) {

    uint32_t hour;
    uint32_t min;
    uint32_t sec;
    uint32_t interval;





    
    
    
    if (esp_sntp_get_sync_status() == SNTP_SYNC_STATUS_IN_PROGRESS) {

        set_lcd_update_time(-1, -1);
        ESP_LOGI(TAG, "Hora invalida");
        interval = 60;
    } else {
        get_current_date(&hour, &min, &sec);

        set_lcd_update_time(hour, min);
        interval = 60 - sec;

        lv_update_lcd_schedule(true);
        ESP_LOGI(TAG, "Actualizada la hora: %02d:%02d. proximo intervalo: %d", (int) hour, (int) min, (int) interval);
    }

    //get_next_schedule(name, &time_end);

    ESP_ERROR_CHECK(esp_timer_start_once(timer_date_text, (interval * 1000000)));

}


void event_handler_sync (struct timeval *tv) {

    ESP_LOGE(TAG, "Evento de sincronizacion");



    sntp_sync_status_t sync_status = sntp_get_sync_status();


   ESP_LOGE(TAG, "SYNSTATUS ES %d", sync_status);

   switch (sync_status) {

    case SNTP_SYNC_STATUS_RESET:
        ESP_LOGW(TAG, "La sincronizacion esta en estado reset");
        break;

    case SNTP_SYNC_STATUS_COMPLETED:
        ESP_LOGI(TAG, "La sincronizacion esta completada");
        update_time_valid(true);
        //event_app_t event;
        //event.event_app = EVENT_APP_TIME_VALID;
        send_event_app_time_valid();
        set_alarm(NTP_ALARM, ALARM_APP_OFF);

        break;


    case SNTP_SYNC_STATUS_IN_PROGRESS:  
        ESP_LOGE(TAG, "La sincronizacion esta en progreso");
        set_alarm(NTP_ALARM, ALARM_APP_ON);

    break; // Smooth time sync in progress.
    
   }

}


void reset_device() {

    esp_restart();


}


void factory_reset_device() {

    esp_rmaker_factory_reset(0,0);
}

float get_app_current_temperature() {

    esp_rmaker_param_t *param;
    param = esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_TEMPERATURE_NAME);
    return esp_rmaker_param_get_val(param)->val.f;
}

float get_app_current_threshold() {

    esp_rmaker_param_t *param;
    param = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
    return esp_rmaker_param_get_val(param)->val.f;

}


void create_task_thermostat() {

     xTaskCreatePinnedToCore(task_iotThermostat, "tarea_lectura_temperatura", CONFIG_RESOURCE_THERMOSTAT_TASK, (void*) NULL, 4, &thermostat_handle,0);
     ESP_LOGW(TAG, "Tarea thermostat task creada");
}


void remove_task_thermostat() {

    vTaskDelete(thermostat_handle);
    thermostat_handle = NULL;
    ESP_LOGW(TAG, "thermostat_task eliminada");
}

bool is_task_thermostat_active() {

    eTaskState status;

    if (thermostat_handle == NULL) {
        return false;
    }

    status = eTaskGetState(thermostat_handle);

    if ((status == eDeleted) || (status == eInvalid)) {

        ESP_LOGW(TAG, "La tarea no existe");
        return false;
    }
    return true;
}

char* status2mnemonic(status_app_t status) {

    static char mnemonic[30];

    switch(status) {

        case STATUS_FACTORY:
            strncpy(mnemonic, TEXT_STATUS_APP_FACTORY, 30);
        break;

        case STATUS_ERROR:
            strncpy(mnemonic, TEXT_STATUS_APP_ERROR, 30);
        break;

        case STATUS_AUTO:
           strncpy(mnemonic, TEXT_STATUS_APP_AUTO, 30);
        break;
        case STATUS_MANUAL:
           strncpy(mnemonic, TEXT_STATUS_APP_MANUAL, 30);

        break;

        case STATUS_STARTING:
           strncpy(mnemonic, TEXT_STATUS_APP_STARTING, 30);

        break;

        case STATUS_CONNECTING:
           strncpy(mnemonic, TEXT_STATUS_APP_CONNECTING, 30);

        break;

        case STATUS_SYNC:
           strncpy(mnemonic, TEXT_STATUS_APP_SYNCING, 30);

        break;

        case STATUS_UPGRADING:
           strncpy(mnemonic, TEXT_STATUS_APP_UPGRADING, 30);

        break;

        default:
            strncpy(mnemonic, "ERROR STATUS", 30);

        break;

    }

    return mnemonic;


}

void set_app_status(status_app_t status) {

    esp_rmaker_param_t *param;
    char* text_status;

    text_status = status2mnemonic(status);

    ESP_LOGW(TAG," ESTADO DE LA APLICACION: %s", text_status);
    set_lcd_update_text_mode(text_status);

    param = esp_rmaker_device_get_param_by_name(thermostat_device, MODE);
    esp_rmaker_param_update_and_report(param, esp_rmaker_str(text_status));

    status_app = status;

    switch(status) {

        case STATUS_FACTORY:
        
        break;

        case STATUS_ERROR:
        break;

        case STATUS_AUTO:
        break;
        case STATUS_MANUAL:
        break;

        case STATUS_STARTING:
        break;

        case STATUS_CONNECTING:
        break;

        case STATUS_SYNC:
        break;

        case STATUS_UPGRADING:
        break;



        default:
        break;




    }
}

status_app_t get_app_status() {

    return status_app;
}


void set_app_update_threshold(float threshold, bool reporting) {



    esp_rmaker_param_t *parameter;
    set_lcd_update_threshold_temperature(threshold);
    parameter = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
    
    if (reporting) {
        esp_rmaker_param_update_and_report(parameter, esp_rmaker_float(threshold));
    } else {
        esp_rmaker_param_update(parameter, esp_rmaker_float(threshold));
    }

    thermostat_action(get_app_current_temperature());

}