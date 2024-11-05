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

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>
#include <esp_rmaker_console.h>
#include <esp_rmaker_ota.h>

#include <esp_rmaker_common_events.h>

#include <app_network.h>
#include <app_insights.h>

#include "app_priv.h"
#include "mqtt_client.h"
#include "esp_rmaker_mqtt_glue.h"
#include "esp_rmaker_mqtt.h"

#include "thermostat_task.h"


#define NAME_DEVICE "Thermostat"

static const char *TAG = "app_main";
esp_rmaker_device_t *thermostat_device;








/* Callback to handle commands received from the RainMaker cloud */
static esp_err_t write_cb(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param,
            const esp_rmaker_param_val_t val, void *priv_data, esp_rmaker_write_ctx_t *ctx)
{

    if (ctx) {
        ESP_LOGI(TAG, "Received write request via : %s, param: %s", esp_rmaker_device_cb_src_to_str(ctx->src), esp_rmaker_param_get_name(param));
    }
    if (strcmp(esp_rmaker_param_get_name(param), ESP_RMAKER_DEF_POWER_NAME) == 0) {
        ESP_LOGI(TAG, "Received value = %s for %s - %s",
                val.val.b? "true" : "false", esp_rmaker_device_get_name(device),
                esp_rmaker_param_get_name(param));
        app_driver_set_state(val.val.b);
        esp_rmaker_param_update(param, val);
        
    }
    return ESP_OK;
}
/* Event handler for catching RainMaker events */
static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{





    
    if (event_base == RMAKER_EVENT) {
        switch (event_id) {
            case RMAKER_EVENT_INIT_DONE:
                ESP_LOGI(TAG, "RainMaker Initialised.");
                break;
            case RMAKER_EVENT_CLAIM_STARTED:
                ESP_LOGI(TAG, "RainMaker Claim Started.");
                break;
            case RMAKER_EVENT_CLAIM_SUCCESSFUL:
                ESP_LOGI(TAG, "RainMaker Claim Successful.");
                break;
            case RMAKER_EVENT_CLAIM_FAILED:
                ESP_LOGI(TAG, "RainMaker Claim Failed.");
                break;
            case RMAKER_EVENT_LOCAL_CTRL_STARTED:
                ESP_LOGI(TAG, "Local Control Started.");
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
                break;
            case RMAKER_MQTT_EVENT_DISCONNECTED:
                ESP_LOGI(TAG, "MQTT Disconnected.");
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


void register_parameters(app_params *params) 

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
 
    params->threshold = esp_rmaker_param_create(SETPOINT_TEMPERATURE, NULL, esp_rmaker_float(35.0), PROP_FLAG_READ | PROP_FLAG_WRITE);
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
    static const char *list[] = {"AUTO", "MANUAL"};
    params->mode = esp_rmaker_param_create(MODE, NULL, esp_rmaker_str(""), PROP_FLAG_READ | PROP_FLAG_WRITE);
    esp_rmaker_param_add_valid_str_list(params->mode, list, 2);
    esp_rmaker_device_add_param(thermostat_device, params->mode);

    /**
     * Create alarm sensor
     */
    params->alarm = esp_rmaker_param_create(ALARM, NULL, esp_rmaker_int(0), PROP_FLAG_READ);
    esp_rmaker_device_add_param(thermostat_device, params->alarm);


/* Add the write callback for the device. We aren't registering any read callback yet as
     * it is for future use.
     */
    esp_rmaker_device_add_cb(thermostat_device, write_cb, NULL);  

}

void app_main()
{

    app_params params;


    /* Initialize Application specific hardware drivers and
     * set initial state.
     */
    esp_rmaker_console_init();
    app_driver_init();
    
    app_driver_set_state(DEFAULT_POWER);

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



    /* Create a Thermotat device.
     * You can optionally use the helper API esp_rmaker_thermostat_device_create() to
     * avoid writing code for adding the name and power parameters.
     */
    thermostat_device = esp_rmaker_device_create(NAME_DEVICE, ESP_RMAKER_DEVICE_THERMOSTAT, NULL);

    /* Register all parameters
     *     
     */

    register_parameters(&params);
    
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


    /* Start the ESP RainMaker Agent */
    esp_rmaker_start();

    err = app_network_set_custom_mfg_data(MGF_DATA_DEVICE_TYPE_SWITCH, MFG_DATA_DEVICE_SUBTYPE_SWITCH);
    /* Start the Wi-Fi.
     * If the node is provisioned, it will start connection attempts,
     * else, it will start Wi-Fi provisioning. The function will return
     * after a connection has been successfully established
     */


    err = app_network_start(POP_TYPE_RANDOM);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Could not start Wifi. Aborting!!!");
        vTaskDelay(5000/portTICK_PERIOD_MS);
        abort();
    }
    
    xTaskCreate(task_iotThermostat, "tarea_lectura_temperatura", CONFIG_RESOURCE_APP_TASK, (void*) &params, 1, NULL);

}
