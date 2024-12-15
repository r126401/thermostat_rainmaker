

#include "local_events.h"
#include "app_priv.h"
#include "thermostat_task.h"

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







/* Callback to handle commands received from the RainMaker cloud */
esp_err_t write_cb(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param,
            const esp_rmaker_param_val_t val, void *priv_data, esp_rmaker_write_ctx_t *ctx)
{


    esp_rmaker_param_t *parameter;
    uint32_t time_end;
    event_lcd_t event;
    uint32_t index;
    



 
    if (ctx) {
        ESP_LOGE(TAG, "Received write request via : %s, param: %s", esp_rmaker_device_cb_src_to_str(ctx->src), esp_rmaker_param_get_name(param));
    }


    switch (ctx->src) {

        case ESP_RMAKER_REQ_SRC_SCHEDULE:

            ESP_LOGI(TAG, "Received start schedule ");
            esp_rmaker_param_update_and_report(param, val);
            index = get_next_schedule(&time_end);
            event.event_type = UPDATE_SCHEDULE;
            event.par1 = time_end;
            event.par2 = index;
            send_event(event);
            



            break;

        case ESP_RMAKER_REQ_SRC_CLOUD:

            /**
             * Receive setpoint temperature. Change threshold in order activate/deactivate thermostat
             */
            ESP_LOGI(TAG, "Received SETPOINT_TEMPERATURE from cloud ");
            if (strcmp(esp_rmaker_param_get_name(param), SETPOINT_TEMPERATURE) == 0) {
                ESP_LOGI(TAG, "Received value threshold = %s for %s - %s",
                        val.val.f? "true" : "false", esp_rmaker_device_get_name(device),
                        esp_rmaker_param_get_name(param));
                parameter = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
                thermostat_action(esp_rmaker_param_get_val(parameter)->val.f);
                esp_rmaker_param_update(param, val);
                
            }





        break;

        case ESP_RMAKER_REQ_SRC_LOCAL:

            if (strcmp(esp_rmaker_param_get_name(param), ESP_RMAKER_DEF_POWER_NAME) == 0) {

            /**
             * Receive Power event. Activate/deactivate relay in remote
             */
            ESP_LOGI(TAG, "Received value = %s for %s - %s", val.val.b? "true" : "false", esp_rmaker_device_get_name(device), esp_rmaker_param_get_name(param));
            relay_operation(val.val.b);
            esp_rmaker_param_update(param, val);
            }

            /**
             * Receive setpoint temperature. Change threshold in order activate/deactivate thermostat
             */


            if (strcmp(esp_rmaker_param_get_name(param), SETPOINT_TEMPERATURE) == 0) {
                ESP_LOGI(TAG, "Received value threshold = %s for %s - %s",
                        val.val.f? "true" : "false", esp_rmaker_device_get_name(device),
                        esp_rmaker_param_get_name(param));
                parameter = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
                thermostat_action(esp_rmaker_param_get_val(parameter)->val.f);
                esp_rmaker_param_update(param, val);
                
            }

            /**
             * Receive new calibrate to sensor from cloud.
             */

        if (strcmp(esp_rmaker_param_get_name(param), CALIBRATE) == 0) {
                ESP_LOGI(TAG, "Received value CALIBRATE = %s for %s - %s",
                        val.val.f? "true" : "false", esp_rmaker_device_get_name(device),
                        esp_rmaker_param_get_name(param));
                parameter = esp_rmaker_device_get_param_by_name(thermostat_device, CALIBRATE);
                thermostat_action(esp_rmaker_param_get_val(parameter)->val.f);
                esp_rmaker_param_update(param, val);
                
            }

            /**
             * Receive read interval parameter
             */

        if (strcmp(esp_rmaker_param_get_name(param), READ_INTERVAL) == 0) {
                ESP_LOGI(TAG, "Received value CALIBRATE = %s for %s - %s",
                        val.val.i? "true" : "false", esp_rmaker_device_get_name(device),
                        esp_rmaker_param_get_name(param));
                parameter = esp_rmaker_device_get_param_by_name(thermostat_device, READ_INTERVAL);
                thermostat_action(esp_rmaker_param_get_val(parameter)->val.i);
                esp_rmaker_param_update(param, val);
                
            }
        break;

        default:
        ESP_LOGW(TAG, "Event no classified yet");
        break;

    }






    return ESP_OK;
}






