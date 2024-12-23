/* Switch Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include <inttypes.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <esp_sntp.h>
#include <esp_timer.h>
#include <esp_err.h>


#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>
#include <esp_rmaker_console.h>
#include <esp_rmaker_ota.h>
#include <esp_rmaker_utils.h>
#include "alarms_app.h"


#include "cJSON.h"






#include <esp_rmaker_common_events.h>

#include <app_network.h>
#include <app_insights.h>

#include "app_priv.h"
#include "mqtt_client.h"
#include "esp_rmaker_mqtt_glue.h"
#include "esp_rmaker_mqtt.h"

#include "thermostat_task.h"
#include "local_events.h"
#include "rgblcd.h"
#include "lv_main_thermostat.h"
#include "lv_factory_thermostat.h"
#include "events_app.h"
#include "schedule_app.h"


#define NAME_DEVICE "Thermostat"

float current_threshold = 21.5;


static const char *TAG = "app_main";
esp_rmaker_device_t *thermostat_device;
static esp_timer_handle_t timer_date_text;



const esp_timer_create_args_t text_date_shot_timer_args = {
    .callback = &time_refresh,
    /* name is optional, but may help identify the timer when debugging */
    .name = "time refresh date text"
};

char *text_qrcode;
app_params_t params;


static void timer_delay_next_schedule(void *arg) {

    lv_update_lcd_schedule(true);
    ESP_LOGI(TAG, "UPDATE LCD SCHEDULE EJECUTADO DESPUES DE UNA OPERACION CON LOS SCHEDULES");

}



void topic_cb (const char *topic, void *payload, size_t payload_len, void *priv_data) {

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
        ESP_LOGE(TAG, "NO Se ha encontrado una operacion de schedules");
    }


    /**
     * Es necesario extraer la info para refrescar el schedule de la pantalla.
     * {"Schedule":{"Schedules":[{"id":"GO41","operation":"enable"}]}}
     */

    ESP_LOGE(TAG, "Se ha recibido informacion: %.*s", payload_len, (char*) payload);
    
    



}



/* Event handler for catching RainMaker events */
static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{

    event_lcd_t event_lcd;



    ESP_LOGW(TAG, "RECIBIDO EVENTO %s, EVENTID %d ", event_base, (int) event_id);
    
    if (event_base == RMAKER_EVENT) {
        switch (event_id) {
            case RMAKER_EVENT_INIT_DONE:
                ESP_LOGI(TAG, "RainMaker Initialised.");
                break;
            case RMAKER_EVENT_CLAIM_STARTED:
                ESP_LOGI(TAG, "RainMaker Claim Started.");
                event_lcd.event_type = QR_CONFIRMED;
                send_event(event_lcd);
                break;
            case RMAKER_EVENT_CLAIM_SUCCESSFUL:
                ESP_LOGI(TAG, "RainMaker Claim Successful.");
                break;
            case RMAKER_EVENT_CLAIM_FAILED:
                ESP_LOGI(TAG, "RainMaker Claim Failed.");
                break;
            case RMAKER_EVENT_LOCAL_CTRL_STARTED:
                ESP_LOGI(TAG, "Local Control Started.");
                event_lcd.event_type = QR_CONFIRMED;
                send_event(event_lcd);

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
                event_lcd.event_type = UPDATE_BROKER_STATUS;
                event_lcd.status = true;
                send_event(event_lcd);
                set_alarm(MQTT_ALARM, ALARM_APP_OFF);
 

                break;
            case RMAKER_MQTT_EVENT_DISCONNECTED:
                ESP_LOGI(TAG, "MQTT Disconnected.");
                event_lcd.event_type = UPDATE_BROKER_STATUS;
                event_lcd.status = false;
                send_event(event_lcd);
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
                ESP_LOGI(TAG, "Provisioning QR : %s", (char *)event_data);
                if (text_qrcode == NULL) {
                    text_qrcode = (char*) calloc(strlen(event_data) + 1, sizeof(char));
                }
                create_instalation_button();
                strncpy(text_qrcode, event_data, strlen(event_data));

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
                break;
            case RMAKER_OTA_EVENT_IN_PROGRESS:
                ESP_LOGI(TAG, "OTA is in progress.");
                break;
            case RMAKER_OTA_EVENT_SUCCESSFUL:
                ESP_LOGI(TAG, "OTA successful.");
                break;
            case RMAKER_OTA_EVENT_FAILED:
                ESP_LOGI(TAG, "OTA Failed.");
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
    esp_rmaker_param_add_ui_type(params->threshold, ESP_RMAKER_UI_SLIDER);
    esp_rmaker_param_add_bounds(params->threshold, esp_rmaker_float(0), esp_rmaker_float(40), esp_rmaker_float(0.5));
    esp_rmaker_device_add_param(thermostat_device, params->threshold);



    
    /**
     * Create calibrate param
     */

    params->calibrate = esp_rmaker_param_create(CALIBRATE, NULL, esp_rmaker_float(-2.0),PROP_FLAG_WRITE |  PROP_FLAG_READ);
    esp_rmaker_device_add_param(thermostat_device, params->calibrate);

    /**
     * Create read interval param
     */
    params->read_interval = esp_rmaker_param_create(READ_INTERVAL, NULL, esp_rmaker_int(20), PROP_FLAG_READ | PROP_FLAG_WRITE);
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




}


void init_app()
{

    //app_params params;
    event_lcd_t event;



    /* Initialize Application specific hardware drivers and
     * set initial state.
     */
    


    esp_rmaker_console_init();
    //app_driver_init();

    ESP_LOGE(TAG, "PASO 1");

    /* Initialize NVS. */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    /* Initialize Wi-Fi. Note that, this should be called before esp_rmaker_node_init()
     */
    app_network_init();

    ESP_LOGE(TAG, "PASO 2");

    /* Register an event handler to catch RainMaker events */
    ESP_ERROR_CHECK(esp_event_handler_register(RMAKER_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(RMAKER_COMMON_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(APP_NETWORK_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(RMAKER_OTA_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));

   
    

    
 

    /* Initialize the ESP RainMaker Agent.
     * Note that this should be called after app_network_init() but before app_nenetworkk_start()
     * */
    esp_rmaker_config_t rainmaker_cfg = {
        .enable_time_sync = false,
    };
    esp_rmaker_node_t *node = esp_rmaker_node_init(&rainmaker_cfg, "ESP RainMaker Device", "thermostat");
    if (!node) {
        ESP_LOGE(TAG, "Could not initialise node. Aborting!!!");
        vTaskDelay(5000/portTICK_PERIOD_MS);
        abort();
    }

    ESP_LOGE(TAG, "PASO 3");

    /* Create a Thermotat device.
     * You can optionally use the helper API esp_rmaker_thermostat_device_create() to
     * avoid writing code for adding the name and power parameters.
     */
    thermostat_device = esp_rmaker_device_create(NAME_DEVICE, ESP_RMAKER_DEVICE_THERMOSTAT, NULL);

    /* Register all parameters
     *     
     */

   register_parameters(&params);

   


    /* Add the write callback for the device. We aren't registering any read callback yet as
     * it is for future use.
     */
    esp_rmaker_device_add_cb(thermostat_device, write_cb, NULL);  

    ESP_LOGE(TAG, "PASO 4");

    
    /* Add this switch device to the node */
    esp_rmaker_node_add_device(node, thermostat_device);

    /* Enable OTA */
    esp_rmaker_ota_enable_default();

    /* Enable timezone service which will be require for setting appropriate timezone
     * from the phone apps for scheduling to work correctly.
     * For more information on the various ways of setting timezone, please check
     * https://rainmaker.espressif.com/docs/time-service.html.
     */
    esp_rmaker_timezone_service_enable();

    /* Enable scheduling. */
    esp_rmaker_schedule_enable();

    /* Enable Scenes */
    esp_rmaker_scenes_enable();

    /* Enable Insights. Requires CONFIG_ESP_INSIGHTS_ENABLED=y */
    app_insights_enable();

    ESP_LOGE(TAG, "PASO 5");
    /* Start the ESP RainMaker Agent */
    esp_rmaker_start();

    err = app_network_set_custom_mfg_data(MGF_DATA_DEVICE_TYPE_SWITCH, MFG_DATA_DEVICE_SUBTYPE_SWITCH);
    /* Start the Wi-Fi.
     * If the node is provisioned, it will start connection attempts,
     * else, it will start Wi-Fi provisioning. The function will return
     * after a connection has been successfully established
     */

    ESP_LOGE(TAG, "PASO 6");


    err = app_network_start(POP_TYPE_RANDOM);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Could not start Wifi. Aborting!!!");
        vTaskDelay(5000/portTICK_PERIOD_MS);
        abort();
    } else {
        event.event_type = UPDATE_WIFI_STATUS;
        event.status = true;
        send_event(event);
        set_alarm(WIFI_ALARM, ALARM_APP_OFF);
        
    }
    
    ESP_LOGE(TAG, "PASO 7");
    //xTaskCreatePinnedToCore(task_iotThermostat, "tarea_lectura_temperatura", 4096, (void*) &params, 4, NULL,0);
    

    

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

void time_refresh(void *arg) {

    uint32_t hour;
    uint32_t min;
    uint32_t sec;
    uint32_t interval;


    event_lcd_t event;


    
    
    
    if (esp_sntp_get_sync_status() == SNTP_SYNC_STATUS_IN_PROGRESS) {
        event.event_type = UPDATE_TIME;
        event.par1 = -1;
        event.par2 = -1;
        send_event(event);
        ESP_LOGI(TAG, "Hora invalida");
        interval = 60;
    } else {
        event.event_type = UPDATE_TIME;
        get_current_date(&hour, &min, &sec);
        event.par1 = hour;
        event.par2 = min;
        send_event(event);
        interval = 60 - sec;

        lv_update_lcd_schedule(true);
        ESP_LOGI(TAG, "Actualizada la hora: %02d:%02d. proximo intervalo: %d", (int) hour, (int) min, (int) interval);
    }

    //get_next_schedule(name, &time_end);

    ESP_ERROR_CHECK(esp_timer_start_once(timer_date_text, (interval * 1000000)));

}




void update_time_valid(bool timevalid) {


    uint32_t hour;
    uint32_t min;
    uint32_t sec;
    uint32_t resto = 0;
    static bool sync = false;
    event_lcd_t event;
    event.event_type = UPDATE_TIME;

    if (timevalid) {



        if (!sync) {
            get_current_date(&hour, &min, &sec);
            ESP_ERROR_CHECK(esp_timer_create(&text_date_shot_timer_args, &timer_date_text));
            resto = 60 - sec;
            ESP_ERROR_CHECK(esp_timer_start_once(timer_date_text, (resto * 1000000)));
            ESP_LOGI(TAG, "Actualizada la hora: %02d:%02d. Proximo intervalo :%d segundos", (int) hour, (int) min, (int) resto);

            sync = true;
            event.par1 = hour;
            event.par2 = min;
            send_event(event);

            lv_update_lcd_schedule(true);

        } 

    } else {
        event.par1 = -1;
        event.par2 = -1;
        send_event(event);
    }




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
        event_app_t event;
        event.event_app = EVENT_APP_TIME_VALID;
        send_event_app(event);
        set_alarm(NTP_ALARM, ALARM_APP_OFF);

        break;


    case SNTP_SYNC_STATUS_IN_PROGRESS:  
        ESP_LOGE(TAG, "La sincronizacion esta en progreso");
        set_alarm(NTP_ALARM, ALARM_APP_ON);

    break; // Smooth time sync in progress.
    
   }

}


void app_main() {

    event_lcd_t event_lcd;
    char mode[50] = {0};
    init_alarms();
    create_event_app_task();
    init_lcdrgb();

    event_lcd.event_type = UPDATE_TEXT_MODE;
    strcpy(mode, STATUS_APP_STARTING);
    event_lcd.text = mode;
    send_event(event_lcd);

    xTaskCreatePinnedToCore(task_iotThermostat, "tarea_lectura_temperatura", 4096, (void*) &params, 4, NULL,0);
    init_app();
    sntp_set_time_sync_notification_cb(event_handler_sync);








 
   ESP_LOGE(TAG, "FIN DE LA APLICACION");

   
}


void reset_device() {

    esp_restart();


}


void factory_reset_device() {

    esp_rmaker_factory_reset(0,0);
}

