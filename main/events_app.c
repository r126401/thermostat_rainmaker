

#include "events_app.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "esp_log.h"
#include "esp_err.h"

#include "lv_main_thermostat.h"
#include "lv_factory_thermostat.h"

xQueueHandle event_queue_app;
static const char *TAG = "events_app";


#include <string.h>
#include "strings.h"
#include <stdio.h>


char* event2mnemonic(EVENT_TYPE_LCD type_lcd) {

    static char mnemonic[31];
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

char* event_app_2mnemonic(EVENT_APP type) {

    static char mnemonic[30];
    switch (type) 
    {

        case EVENT_APP_UP_THRESHOLD:
        strncpy(mnemonic, "EVENT_APP_UP_THRESHOLD", 30);
        break;

        case EVENT_APP_DOWN_THRESHOLD:
        strncpy(mnemonic, "EVENT_APP_DOWN_THRESHOLD", 30);
        break;

        case EVENT_APP_SETPOINT_THRESHOLD:
        strncpy(mnemonic, "EVENT_APP_SETPOINT_THRESHOLD", 30);
    }


        return mnemonic;
}



void receive_event_app(event_app_t event) {


    switch (event.event_app) 
    {

        case EVENT_APP_UP_THRESHOLD:

        ESP_LOGI(TAG, "Recibido evento threshold up");

        break;

        case EVENT_APP_DOWN_THRESHOLD:

        ESP_LOGI(TAG, "Recibido evento threshold down");

        break;

        case EVENT_APP_SETPOINT_THRESHOLD:

        ESP_LOGI(TAG, "Recibido evento EVENT_APP_SETPOINT_THRESHOLD. Threshold = %.1f", event.value); 
        break;


    }

}


void event_app_task(void *arg) {

	event_app_t event;


	event_queue_app = xQueueCreate(5, sizeof(event_app_t));

	for(;;) {
		ESP_LOGI(TAG, "ESPERANDO EVENTO DE APLICACION...Memoria libre: %d", (int) esp_get_free_heap_size());
		if (xQueueReceive(event_queue_app, &event,  portMAX_DELAY) == pdTRUE) {

			receive_event_app(event);


		} else {
			ESP_LOGE(TAG, "NO SE HA PODIDO PROCESAR LA PETICION");
		}

	}
	vTaskDelete(NULL);


}

void create_event_app_task() {



	xTaskCreatePinnedToCore(event_app_task, "event_app_task", 1024*4, NULL, 2, NULL,0);
	ESP_LOGW(TAG, "TAREA DE EVENTOS DE APLICACION CREADA CREADA");


}


void send_event_app(event_app_t event) {


	ESP_LOGW(TAG, " envio de evento lcd %s", event_app_2mnemonic(event.event_app));
	if ( xQueueSend(event_queue_app, &event, portMAX_DELAY) != pdPASS) {
		ESP_LOGE(TAG, "no se ha podido enviar el evento");

	}

}


