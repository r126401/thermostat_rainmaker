#include <strings.h>
#include <string.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_timer.h"

#include "events_lcd.h"

#include "lvgl.h"
#include "lv_main_thermostat.h"
#include "lv_factory_thermostat.h"

static char *TAG = "events_lcd.c";
extern xQueueHandle event_queue;

char* event_lcd_2_mnemonic(EVENT_TYPE_LCD type_lcd) {

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



static void receive_lcd_event(event_lcd_t event) {


    //ESP_LOGW(TAG, "Recibido evento de tipo %s, %ld %ld %ld %d %s %.1f", event2mnemonic(event.event_type), event.par1, event.par2, event.par3, event.status, event.text, event.value);
    ESP_LOGE(TAG, "Recibido evento %s", event_lcd_2_mnemonic(event.event_type));
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
        lv_update_broker_status(event.status);

        break;

        case UPDATE_HEATING:

        lv_update_heating(event.status);

        break;

        case UPDATE_THRESHOLD_TEMPERATURE:

        lv_update_threshold_temperature(event.value);

        break;

        case UPDATE_SCHEDULE:

        lv_update_schedule(event.status, event.par1, event.par2);

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

void send_event_lcd(event_lcd_t event) {


	//ESP_LOGW(TAG, " envio de evento lcd %s", event2mnemonic(event.event_type));
	if ( xQueueSend(event_queue, &event,portMAX_DELAY) != pdPASS) {
		ESP_LOGE(TAG, "no se ha podido enviar el evento");

	}

}

void wait_event_lcd() {

    event_lcd_t event;

    if (xQueueReceive(event_queue, &event,  0) == pdTRUE) {
        
        receive_lcd_event(event);
    }

}

static void update_lcd_float(EVENT_TYPE_LCD type, float value) {

    event_lcd_t event_lcd;
    event_lcd.event_type = type;
    event_lcd.value = value;

    send_event_lcd(event_lcd);

}

static void update_lcd_int(EVENT_TYPE_LCD type, int par1, int par2, int par3) {

    event_lcd_t event_lcd;
    event_lcd.event_type = type;
    event_lcd.par1 = par1;
    event_lcd.par2 = par2;
    event_lcd.par3 = par3;

    send_event_lcd(event_lcd);

}

static void update_lcd_char(EVENT_TYPE_LCD type, char* text) {

    event_lcd_t event_lcd;
    event_lcd.event_type = type;
    event_lcd.text = text;


    send_event_lcd(event_lcd);

}

static void update_lcd_bool(EVENT_TYPE_LCD type, bool status) {

    event_lcd_t event_lcd;
    event_lcd.event_type = type;
    event_lcd.status = status;

    send_event_lcd(event_lcd);
    
}



void set_lcd_update_time(int par1, int par2) {

    update_lcd_int(UPDATE_TIME, par1, par2, -1);

}
void set_lcd_update_text_mode(char *text_mode) {

    update_lcd_char(UPDATE_TEXT_MODE, text_mode);

}
void set_lcd_update_label_mode(char *mode) {

    update_lcd_char(UPDATE_LABEL_MODE, mode);

}
void set_lcd_update_temperature(float temperature) {

    ESP_LOGW(TAG, "Temperatura a actualizar: %.1f", temperature);
    update_lcd_float(UPDATE_TEMPERATURE, temperature);

}
void set_lcd_update_wifi_status(bool status) {

    update_lcd_bool(UPDATE_WIFI_STATUS, status);

}
void set_lcd_update_broker_status(bool status) {

    update_lcd_bool(UPDATE_BROKER_STATUS, status);

}
void set_lcd_update_heating(bool status) {

    update_lcd_bool(UPDATE_HEATING, status);

}
void set_lcd_update_threshold_temperature(float threshold) {

    update_lcd_float(UPDATE_THRESHOLD_TEMPERATURE, threshold);

}
void set_lcd_update_schedule(bool status, int par1, int par2) {

    update_lcd_int(UPDATE_SCHEDULE, par1, par2, -1);

}

void set_lcd_update_text_schedule(int par1, int par2) {

    update_lcd_int(UPDATE_TEXT_SCHEDULE, par1, par2, -1);
}
void set_lcd_update_percent(float percent) {

    update_lcd_int(UPDATE_PERCENT, percent, -1, -1);

}
void set_lcd_update_qr_confirmed() {

    update_lcd_bool(QR_CONFIRMED, true);

}


void set_lcd_update_icon_errors(bool status) {

    update_lcd_bool(UPDATE_ICON_ERRORS, status);


}

