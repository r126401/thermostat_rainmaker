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







typedef enum EVENT_APP {

    EVENT_APP_UP_THRESHOLD,
    EVENT_APP_DOWN_THRESHOLD,
    EVENT_APP_SETPOINT_THRESHOLD,
    EVENT_APP_TIME_VALID,
    EVENT_APP_AUTO,
    EVENT_APP_MANUAL,
    EVENT_APP_ALARM_ON,
    EVENT_APP_ALARM_OFF
}EVENT_APP;

typedef struct event_app_t {

    float value;
    EVENT_APP event_app;
} event_app_t;


void create_event_app_task();
void send_event_app(event_app_t event);



void send_event_app_alarm(EVENT_APP type);


