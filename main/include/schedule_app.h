
#pragma once

#include <esp_schedule.h>
#include "esp_idf_version.h"
#include "esp_timer.h"
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <stdint.h>
#include <time.h>


typedef struct esp_schedule_t {
    char name[MAX_SCHEDULE_NAME_LEN + 1];
    esp_schedule_trigger_t trigger;
    uint32_t next_scheduled_time_diff;
    TimerHandle_t timer;
    esp_schedule_trigger_cb_t trigger_cb;
    esp_schedule_timestamp_cb_t timestamp_cb;
    void *priv_data;
    esp_schedule_validity_t validity;
} esp_schedule_t;


esp_err_t get_thermostat_schedules_app();
int get_next_schedule(uint32_t *time_end);
int get_last_schedule(uint32_t *time_end, float *threshold);
char* get_current_date(time_t now);
