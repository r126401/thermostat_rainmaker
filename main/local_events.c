

#include "local_events.h"
#include "app_main.h"
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
#include "events_lcd.h"

static const char *TAG = "local_events";

