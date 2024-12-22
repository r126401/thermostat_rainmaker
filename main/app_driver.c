/* Switch demo implementation using button and RGB LED
   
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <sdkconfig.h>

#include <iot_button.h>
#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_params.h> 

#include <app_reset.h>
#include "app_priv.h"
#include "esp_log.h"
#include "lv_main_thermostat.h"
#include "thermostat_task.h"
#include "events_app.h"
#include "lvgl.h"

static const char *TAG = "app_driver";

/* This is the button that is used for toggling the power */
#define BUTTON_GPIO          CONFIG_EXAMPLE_BOARD_BUTTON_GPIO
#define BUTTON_ACTIVE_LEVEL  0

/* This is the GPIO on which the power will be set */
#define OUTPUT_GPIO    CONFIG_EXAMPLE_OUTPUT_GPIO
static bool g_power_state = DEFAULT_POWER;
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<< CONFIG_RELAY_GPIO) | (1ULL << CONFIG_PIN_NUM_BK_LIGHT))


#define WIFI_RESET_BUTTON_TIMEOUT       3
#define FACTORY_RESET_BUTTON_TIMEOUT    10



ESTADO_RELE get_status_relay() {

    return (gpio_get_level(CONFIG_RELAY_GPIO));
}



void gpio_rele_in_out() {
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    ESP_LOGW(TAG, "gpio rele en E/S");

}

enum ESTADO_RELE IRAM_ATTR relay_operation(ESTADO_RELE op) {

    event_lcd_t event;
    event.event_type = UPDATE_HEATING;
	
	if (gpio_get_level(CONFIG_RELAY_GPIO) == OFF){
		if (op == ON) {
			gpio_set_level(CONFIG_RELAY_GPIO, op);
			ESP_LOGE(TAG, "Accion: OFF->ON");
            esp_rmaker_param_update_and_report(
                esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME),
                esp_rmaker_bool(op));

		} else {
			ESP_LOGE(TAG, "Accion: OFF->OFF");
			}
	} else {

		if (op == ON) {
			ESP_LOGE(TAG, "Accion: ON->ON");
		} else {
			gpio_set_level(CONFIG_RELAY_GPIO, op);
			ESP_LOGE(TAG, "Accion: ON->OFF");
            esp_rmaker_param_update_and_report(
                esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME),
                esp_rmaker_bool(op));

			}
	}

    if (op == ON) {
        event.status = true;
    } else {
        event.status = false;
    }

   send_event(event);

    //lv_update_heating(event.status);
    //lv_timer_handler();

	return gpio_get_level(CONFIG_RELAY_GPIO);
}


void app_driver_init()
{



    gpio_rele_in_out();
    relay_operation(false);
}



bool app_driver_get_state(void)
{
    return g_power_state;
}
