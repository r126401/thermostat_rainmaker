

#include "events_app.h"
#include "app_main.h"
#include "schedule_app.h"
#include "thermostat_task.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "esp_log.h"
#include "esp_err.h"
#include "alarms_app.h"
#include "events_lcd.h"


#include "lv_main_thermostat.h"
#include "lv_factory_thermostat.h"
#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>
#include <esp_rmaker_console.h>
#include <esp_rmaker_ota.h>

xQueueHandle event_queue_app;
static const char *TAG = "events_app";
extern esp_rmaker_device_t *thermostat_device;
extern float current_threshold;



#include <string.h>
#include "strings.h"
#include <stdio.h>


static void send_alarm(bool status) {

    set_lcd_update_icon_errors(status);
}


static void send_event_app_alarm_off() {

    send_alarm(false);

}

static void send_event_app_alarm_on() {

    send_alarm(true);

}



char* event_app_2mnemonic(EVENT_APP type) {

    static char mnemonic[30];
    switch (type) 
    {

        case EVENT_APP_SETPOINT_THRESHOLD:
            strncpy(mnemonic, "EVENT_APP_SETPOINT_THRESHOLD", 30);
        break;

        case EVENT_APP_TIME_VALID:
            strncpy(mnemonic, "EVENT_APP_TIME_VALID", 30);
        break;
        case EVENT_APP_AUTO:
            strncpy(mnemonic, "EVENT_APP_AUTO", 30);
        break;

        case EVENT_APP_MANUAL:
            strncpy(mnemonic, "EVENT_APP_MANUAL", 30);
        break;
        case EVENT_APP_ALARM_OFF:
            strncpy(mnemonic, "EVENT_APP_ALARM_OFF", 30);
        break;
        case EVENT_APP_ALARM_ON:
            strncpy(mnemonic, "EVENT_APP_ALARM_ON", 30);
        break;


    }


        return mnemonic;
}



void delay_get_schedules(void *arg) {

    int index;
    uint32_t time_end;
    esp_rmaker_param_t *param;

    index = get_next_schedule(&time_end);
    lv_update_schedule(true, time_end, index);
    param = esp_rmaker_device_get_param_by_name(thermostat_device, MODE);

    if (index >= 0) {
        esp_rmaker_param_update_and_report(param, esp_rmaker_str(STATUS_APP_AUTO));
        set_lcd_update_text_mode(STATUS_APP_AUTO);
        
    } else {
        esp_rmaker_param_update_and_report(param, esp_rmaker_str(STATUS_APP_MANUAL));
        set_lcd_update_text_mode(STATUS_APP_MANUAL);
    }


    


    


}



void receive_event_app(event_app_t event) {

    esp_rmaker_param_t *param;
    char *status;


    switch (event.event_app) 
    {

        case EVENT_APP_SETPOINT_THRESHOLD:

            ESP_LOGI(TAG, "Recibido evento EVENT_APP_SETPOINT_THRESHOLD. Threshold = %.1f", event.value); 
            update_threshold(event.value, true);
            break;
        case EVENT_APP_TIME_VALID:
            
            param = esp_rmaker_device_get_param_by_name(thermostat_device, MODE);
            if (strcmp (esp_rmaker_param_get_val(param)->val.s, STATUS_APP_STARTING) == 0) {
                ESP_LOGW(TAG, "Vamos a cambiar de mode starting");
                esp_timer_handle_t timer_delay_get_schedule;

            const esp_timer_create_args_t delay_get_schedule_shot_timer_args = {
            .callback = &delay_get_schedules,
            /* name is optional, but may help identify the timer when debugging */
            .name = "get schedule"
            };
            esp_timer_create(&delay_get_schedule_shot_timer_args, &timer_delay_get_schedule);
            esp_timer_start_once(timer_delay_get_schedule, 10 * 1000000);

            }
            break;

        case EVENT_APP_MANUAL:
            param = esp_rmaker_device_get_param_by_name(thermostat_device, MODE);
            status = esp_rmaker_param_get_val(param)->val.s;


            if (strcmp(status, STATUS_APP_AUTO) == 0) {
                ESP_LOGW(TAG, "Vamos a cambiar al estado manual. Estamos en modo %s", status);

                esp_rmaker_param_update_and_report(param, esp_rmaker_str(STATUS_APP_MANUAL));
                if (get_status_relay() == OFF) {
                    ESP_LOGW(TAG, "Vamos a encender porque estaba apagado");
                    relay_operation(ON);
                } else {
                    ESP_LOGW(TAG, "Vamos a encender porque estaba encendido");
                    relay_operation(OFF);
                    }
                }

                lv_update_lcd_schedule(false);

            break;

        case EVENT_APP_AUTO:
            param = esp_rmaker_device_get_param_by_name(thermostat_device, MODE);
            status = esp_rmaker_param_get_val(param)->val.s;
            ESP_LOGW(TAG, "Vamos a cambiar al estado AUTO. Estamos en modo %s", status);

            if (strcmp(status, STATUS_APP_MANUAL) == 0) {
                //reportamos el paso a modo auto
                esp_rmaker_param_update_and_report(param, esp_rmaker_str(STATUS_APP_AUTO));
                // recogemos el valor que teniamos de umbral de temperatura del modo auto y lo ponemos
                //param = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
                //esp_rmaker_param_update(param, esp_rmaker_float(current_threshold));
                set_lcd_update_threshold_temperature(current_threshold);
                lv_update_lcd_schedule(true);
                param = esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_TEMPERATURE_NAME);
                thermostat_action(esp_rmaker_param_get_val(param)->val.f);
            }

        break;

        case EVENT_APP_ALARM_OFF:

        if (get_active_alarms() == 0) {

            send_event_app_alarm_off();


        }

        break;
        case EVENT_APP_ALARM_ON:
        
        if (get_active_alarms() == 0) {

            send_event_app_alarm_on();
        }

        break;


    }

    ESP_LOGW(TAG, "Retornamos despues de procesar la peticion");

}


void event_app_task(void *arg) {

	event_app_t event;


	event_queue_app = xQueueCreate(5, sizeof(event_app_t));

	for(;;) {
		ESP_LOGE(TAG, "ESPERANDO EVENTO DE APLICACION...Memoria libre: %d", (int) esp_get_free_heap_size());
		if (xQueueReceive(event_queue_app, &event,  portMAX_DELAY) == pdTRUE) {

			receive_event_app(event);


		} else {
			ESP_LOGE(TAG, "NO SE HA PODIDO PROCESAR LA PETICION");
		}

	}
	vTaskDelete(NULL);


}

void create_event_app_task() {



	xTaskCreatePinnedToCore(event_app_task, "event_app_task", CONFIG_RESOURCE_EVENT_TASK, NULL, 0, NULL,0);
	ESP_LOGW(TAG, "TAREA DE EVENTOS DE APLICACION CREADA CREADA");


}


void send_event_app(event_app_t event) {


	ESP_LOGW(TAG, " envio de evento app %s", event_app_2mnemonic(event.event_app));
	if ( xQueueSend(event_queue_app, &event, 0) != pdPASS) {
		ESP_LOGE(TAG, "no se ha podido enviar el evento");

	}

}


void send_event_app_alarm(EVENT_APP type) {

    event_app_t event;
    event.event_app = type;
    send_event_app(event);
    ESP_LOGW(TAG, "Enviada alarma %s", alarm2mnemonic(type));
}

void update_threshold(float threshold, bool reporting) {



    esp_rmaker_param_t *parameter;
    set_lcd_update_threshold_temperature(threshold);
    parameter = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
    
    if (reporting) {
        esp_rmaker_param_update_and_report(parameter, esp_rmaker_float(threshold));
    } else {
        esp_rmaker_param_update(parameter, esp_rmaker_float(threshold));
    }

    thermostat_action(get_current_temperature());

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
                current_threshold = val.val.f;
                esp_rmaker_param_update_and_report(param, val);
                update_threshold(val.val.f, true);
                lv_update_lcd_schedule(true);
            }
            break;

        case ESP_RMAKER_REQ_SRC_CLOUD:

            /**
             * Receive setpoint temperature. Change threshold in order activate/deactivate thermostat
             */
            ESP_LOGI(TAG, "Received SETPOINT_TEMPERATURE from cloud ");

            if (esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE) == param) {

                current_threshold = val.val.f;
                update_threshold(val.val.f, false);
                lv_update_lcd_schedule(true);   
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
                current_threshold = val.val.f;
                update_threshold(val.val.f, false);
                lv_update_lcd_schedule(true);
                
            }

            /**
             * Receive new calibrate to sensor from cloud.
             */
            

        if (esp_rmaker_device_get_param_by_name(thermostat_device, CALIBRATE) == param) {
                esp_rmaker_param_update(param, val);
                thermostat_action(val.val.f);
            }

            /**
             * Receive read interval parameter
             */

            if (esp_rmaker_device_get_param_by_name(thermostat_device, READ_INTERVAL) == param) {
                esp_rmaker_param_update(param, val);
            }
        break;

        default:
            ESP_LOGW(TAG, "Event no classified yet");
        break;

    }

    return ESP_OK;
}








