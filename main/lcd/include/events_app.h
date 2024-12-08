#include <string.h>
#include "strings.h"
#include <stdio.h>
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


typedef enum EVENT_TYPE_LCD {

    UPDATE_TIME,
    UPDATE_TEXT_MODE,
    UPDATE_LABEL_MODE,
    UPDATE_TEMPERATURE,
    UPDATE_WIFI_STATUS,
    UPDATE_BROKER_STATUS,
    UPDATE_HEATING,
    UPDATE_THRESHOLD_TEMPERATURE,
    UPDATE_SCHEDULE,
    UPDATE_ICON_ERRORS,
    UPDATE_TEXT_SCHEDULE,
    UPDATE_PERCENT,
    QR_CONFIRMED



}EVENT_TYPE_LCD;

typedef struct event_lcd_t {

    uint32_t par1;
    uint32_t par2;
    uint32_t par3;
    bool status;
    char* text;
    float value;
    EVENT_TYPE_LCD event_type;

}event_lcd_t;


void send_event(event_lcd_t event);
void receive_event(event_lcd_t event);
