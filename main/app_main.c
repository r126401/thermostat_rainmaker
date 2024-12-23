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



#include "alarms_app.h"
#include "app_main.h"
#include "events_lcd.h"
#include <esp_rmaker_common_events.h>
#include <app_network.h>
#include <app_insights.h>
#include "app_main.h"
#include "mqtt_client.h"
#include "esp_rmaker_mqtt_glue.h"
#include "esp_rmaker_mqtt.h"
#include "thermostat_task.h"
#include "rgblcd.h"
#include "lv_main_thermostat.h"
#include "lv_factory_thermostat.h"
#include "events_app.h"
#include "schedule_app.h"


#define NAME_DEVICE "Thermostat"




static const char *TAG = "app_main";
esp_rmaker_device_t *thermostat_device;



app_params_t params;








void init_app()
{

    //app_params params;
    //event_lcd_t event;


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

        //send_event_app_alarm(WIFI_ALARM,ALARM_APP_OFF );
        //event.event_type = UPDATE_WIFI_STATUS;
        //event.status = true;
        //send_event_lcd(event);
        set_lcd_update_wifi_status(true);
        set_alarm(WIFI_ALARM, ALARM_APP_OFF);
        
    }

    

}






void app_main() {



    init_alarms();
    create_event_app_task();
    init_lcdrgb();
    set_lcd_update_text_mode(STATUS_APP_STARTING);

    xTaskCreatePinnedToCore(task_iotThermostat, "tarea_lectura_temperatura", 4096, (void*) &params, 4, NULL,0);
    init_app();
    sntp_set_time_sync_notification_cb(event_handler_sync);








 
   ESP_LOGE(TAG, "FIN DE LA APLICACION");

   
}




