

#include "local_events.h"
#include "app_priv.h"
#include "thermostat_task.h"
#include "lv_main_thermostat.h"

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

#include "esp_err.h"

#include "schedule_app.h"
#include "events_app.h"

static const char *TAG = "local_events";




            

void update_threshold(float threshold, bool reporting) {

    
   ESP_LOGI(TAG, " Se va a modificar el threshold a valor %.1f", threshold);


    esp_rmaker_param_t *parameter;
    event_lcd_t event;
    event.event_type = UPDATE_THRESHOLD_TEMPERATURE;
    event.value = threshold;
    send_event(event);
    parameter = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
    thermostat_action(threshold);
    if (reporting) {
        esp_rmaker_param_update_and_report(parameter, esp_rmaker_float(threshold));
    } else {
        esp_rmaker_param_update(parameter, esp_rmaker_float(threshold));
    }
    

    




    ESP_LOGI(TAG, "Enviado nuevo threshold: %.1f", threshold);

}




/* Callback to handle commands received from the RainMaker cloud */
esp_err_t write_cb(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param,
            const esp_rmaker_param_val_t val, void *priv_data, esp_rmaker_write_ctx_t *ctx)
{


 
    if (ctx) {
        ESP_LOGE(TAG, "Received write request via : %s, param: %s", esp_rmaker_device_cb_src_to_str(ctx->src), esp_rmaker_param_get_name(param));
    }


    switch (ctx->src) {

        case ESP_RMAKER_REQ_SRC_SCHEDULE:

            ESP_LOGI(TAG, "Received start schedule ");
            if (param == esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE)){
                esp_rmaker_param_update_and_report(param, val);
                
                ESP_LOGI(TAG, "Enviado threshold al cliente despues de inicio del trigger");
                update_threshold(val.val.f, true);
                lv_update_lcd_schedule();

 
            }
 



            break;

        case ESP_RMAKER_REQ_SRC_CLOUD:

            /**
             * Receive setpoint temperature. Change threshold in order activate/deactivate thermostat
             */
            ESP_LOGI(TAG, "Received SETPOINT_TEMPERATURE from cloud ");

            if (esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE) == param) {

                update_threshold(val.val.f, false);
                lv_update_lcd_schedule();
                
            }





        break;

        case ESP_RMAKER_REQ_SRC_LOCAL:
            /**
             * Receive Power event. Activate/deactivate relay in remote
             */

            if (esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME) == param) {
                
                ESP_LOGI(TAG, "Received value = %s for %s - %s", val.val.b? "true" : "false", esp_rmaker_device_get_name(device), esp_rmaker_param_get_name(param));
                relay_operation(val.val.b);
                esp_rmaker_param_update_and_report(param, val);
                
            }

            /**
             * Receive setpoint temperature. Change threshold in order activate/deactivate thermostat
             */

            if (esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE) == param) {

                ESP_LOGI(TAG, "Received value threshold = %s for %s - %s",
                        val.val.f? "true" : "false", esp_rmaker_device_get_name(device),
                    esp_rmaker_param_get_name(param));
                update_threshold(val.val.f, false);
                lv_update_lcd_schedule();
                
            }

            /**
             * Receive new calibrate to sensor from cloud.
             */
            

        if (esp_rmaker_device_get_param_by_name(thermostat_device, CALIBRATE) == param) {
                ESP_LOGI(TAG, "Received value CALIBRATE = %s for %s - %s",
                        val.val.f? "true" : "false", esp_rmaker_device_get_name(device),
                        esp_rmaker_param_get_name(param));
                 esp_rmaker_param_update(param, val);
                 thermostat_action(val.val.f);
               
                
            }

            /**
             * Receive read interval parameter
             */

            if (esp_rmaker_device_get_param_by_name(thermostat_device, READ_INTERVAL) == param) {
                ESP_LOGI(TAG, "Received value READ_INTERVAL = %s for %s - %s",
                        val.val.i? "true" : "false", esp_rmaker_device_get_name(device),
                        esp_rmaker_param_get_name(param));
                esp_rmaker_param_update(param, val);
                
                
            }
        break;

        default:
        ESP_LOGW(TAG, "Event no classified yet");
        break;

    }






    return ESP_OK;
}






