/*

#include "events_app.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "esp_log.h"
#include "esp_err.h"

#include "lv_main_thermostat.h"
#include "lv_factory_thermostat.h"

extern xQueueHandle event_queue;
static const char *TAG = "events_app";


#include <string.h>
#include "strings.h"
#include <stdio.h>

char* event2mnemonic(EVENT_TYPE_LCD type_lcd) {

    static char mnemonic[50];
    switch (type_lcd) 
    {

        case UPDATE_TIME:
        strncpy(mnemonic, "UPDATE_TIME", 30);

        break;

        case UPDATE_TEXT_MODE:

        strncpy(mnemonic, "UPDATE_TEXT_MODE", 30);

        break;

        case UPDATE_LABEL_MODE:

        strncpy(mnemonic, "UPDATE_LABEL_MODE", 30);

        break;

        case UPDATE_TEMPERATURE:

        strncpy(mnemonic, "UPDATE_TEMPERTAURE", 30);

        break;

        case UPDATE_WIFI_STATUS:

        strncpy(mnemonic, "UPDATE_WIFI_STATUS", 30);

        break;

        case UPDATE_BROKER_STATUS:
        strncpy(mnemonic, "UPDATE_BROKER_STATUS", 30);

        break;

        case UPDATE_HEATING:

        strncpy(mnemonic, "UPDATE_HEATING", 30);

        break;

        case UPDATE_THRESHOLD_TEMPERATURE:

        strncpy(mnemonic, "UPDATE_THRESHOLD_TEMPERATURE", 30);

        break;

        case UPDATE_SCHEDULE:

       strncpy(mnemonic, "UPDATE_SCHEDULE", 30);
        break;

        case UPDATE_ICON_ERRORS:

        strncpy(mnemonic, "UPDATE_ICON_ERRORS", 30);

        break;

        case UPDATE_TEXT_SCHEDULE:
        strncpy(mnemonic, "UPDATE_TEXT_SCHEDULE", 30);

        break;

        case UPDATE_PERCENT:

        strncpy(mnemonic, "UPDATE_PERCENT", 30);
        
        break;

        case QR_CONFIRMED:

        strncpy(mnemonic, "QR_CONFIRMED", 30);
    }

        return mnemonic;
}



void receive_event(event_lcd_t event) {


    //ESP_LOGW(TAG, "Recibido evento de tipo %s, %ld %ld %ld %d %s %.1f", event2mnemonic(event.event_type), event.par1, event.par2, event.par3, event.status, event.text, event.value);
    ESP_LOGE(TAG, "Recibido evento %s", event2mnemonic(event.event_type));
    switch (event.event_type) {

        case UPDATE_TIME:
        lv_update_time(event.par1, event.par2);

        break;

        case UPDATE_TEXT_MODE:

        lv_update_text_mode(event.text);

        break;

        case UPDATE_LABEL_MODE:

        lv_update_label_mode(event.text);

        break;

        case UPDATE_TEMPERATURE:

        lv_update_temperature(event.value);

        break;

        case UPDATE_WIFI_STATUS:

        lv_update_wifi_status(event.status);

        break;

        case UPDATE_BROKER_STATUS:
        ESP_LOGE(TAG, "BROKER STATUS");
        lv_update_broker_status(event.status);

        break;

        case UPDATE_HEATING:

        lv_update_heating(event.status);

        break;

        case UPDATE_THRESHOLD_TEMPERATURE:

        lv_update_threshold_temperature(event.value);

        break;

        case UPDATE_SCHEDULE:

        lv_update_schedule(event.par1, event.par2, event.par3);

        break;

        case UPDATE_ICON_ERRORS:

        lv_update_icon_errors(event.status);

        break;

        case UPDATE_TEXT_SCHEDULE:
        lv_update_text_schedule(event.par1, event.par2);

        break;

        case UPDATE_PERCENT:

        lv_update_percent(event.par1);
        
        break;

        case QR_CONFIRMED:

        lv_qrcode_confirmed();
        break;



        default:

        ESP_LOGE(TAG, "COMANDO NO IMPLEMENTADO EN LCD");

        break;

    }


}


void event_task(void *arg) {

	event_lcd_t event;


	event_queue = xQueueCreate(1, sizeof(event_lcd_t));

	for(;;) {
		ESP_LOGI(TAG, "ESPERANDO EVENTO...Memoria libre: %d", (int) esp_get_free_heap_size());
		if (xQueueReceive(event_queue, &event,  portMAX_DELAY) == pdTRUE) {

			receive_event(event);


		} else {
			ESP_LOGE(TAG, "NO SE HA PODIDO PROCESAR LA PETICION");
		}

	}
	vTaskDelete(NULL);


}

void create_event_task() {



	xTaskCreatePinnedToCore(event_task, "event_task", 1024*4, NULL, 2, NULL,0);
	ESP_LOGW(TAG, "TAREA DE EVENTOS DE LCD CREADA");


}


void send_event(event_lcd_t event) {


	ESP_LOGW(TAG, " envio de evento lcd %s", event2mnemonic(event.event_type));
	if ( xQueueSend(event_queue, &event,portMAX_DELAY) != pdPASS) {
		ESP_LOGE(TAG, "no se ha podido enviar el evento");

	}

}
*/