



#include "esp_log.h"
#include "esp_err.h"
#include "nvs.h"
#include "schedule_app.h"
#include "events_app.h"
#include <strings.h>
#include <string.h>

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>
#include <esp_rmaker_console.h>
#include <esp_rmaker_ota.h>









static const char *TAG = "schedule_app";


void update_lcd_schedule() {

    event_lcd_t event;
    int index;
    uint32_t hour;



    event.event_type = UPDATE_SCHEDULE;
    event.status = true;
    index = get_next_schedule(&hour);
    event.par1 = hour;
    event.par2 = index;
    send_event(event);

}





char* write_date(time_t now) {

	static char fecha_actual[120] = {0};

	//time_t now;
	struct tm fecha;
	//ESP_LOGI(TAG, ""TRAZAR"ACTUALIZAR_HORA", INFOTRAZA);
    //time(&now);
    localtime_r(&now, &fecha);


	sprintf(fecha_actual, "%02d/%02d/%04d %02d:%02d:%02d",
			fecha.tm_mday,
    		fecha.tm_mon + 1,
			fecha.tm_year + 1900,
			fecha.tm_hour,
			fecha.tm_min,
			fecha.tm_sec);

	return fecha_actual;

}


uint32_t get_next_schedule(uint32_t *time_end) {

    esp_rmaker_schedule_t *list;
    esp_schedule_t *schedule = NULL;
    esp_schedule_t *next_schedule = NULL;
    uint32_t diff = -1;
    bool init_diff = true;
    uint32_t index = -1;



    list = esp_rmaker_get_schedule_list();

    if (list == NULL) {
        ESP_LOGW(TAG, "No hay schedules configurados");
        return index;
    }


    while (list != NULL) {

        schedule = (esp_schedule_t*) list->handle;

        ESP_LOGI(TAG, "schedule %s, index %ld", schedule->name, list->index);
        if (schedule->next_scheduled_time_diff != 0) {
            if (init_diff) {
                init_diff = false;
                diff = schedule->next_scheduled_time_diff;
                index = list->index;
                next_schedule = schedule;
            } else {
                if (diff > schedule->next_scheduled_time_diff) {
                    diff = schedule->next_scheduled_time_diff;
                    index = list->index;
                    next_schedule = schedule;
                }
            }
        } else {
            ESP_LOGW(TAG, "El schedule %s esta inactivo", schedule->name);
        }

        list = list->next;
    }

    
    *time_end = next_schedule->trigger.next_scheduled_time_utc;
    ESP_LOGE(TAG, "El proximo schedule es : %s, fecha fin: %ld, index %ld", next_schedule->name, *time_end, index);



    return index;

}

esp_err_t get_thermostat_schedules_app() {

    esp_rmaker_schedule_t *list_schedules;
    esp_schedule_t *schedule;



    list_schedules = esp_rmaker_get_schedule_list();
    if (list_schedules != NULL) {

        while(list_schedules != NULL) {
            char action[40];

            schedule = (esp_schedule_t*) list_schedules->handle;
            
            strncpy(action, (char*) list_schedules->action.data, list_schedules->action.data_len);

            ESP_LOGE(TAG, "SCHEDULES: name = %s, action = %s, temporizador = %ld", list_schedules->name, action, schedule->next_scheduled_time_diff);
            
            list_schedules = list_schedules->next;
        }

        
    } else {
        ESP_LOGE(TAG, "SCHEDULES SON NULOS");
    }

    return ESP_OK;
}