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
#include "events_app.h"
#include "lvgl.h"

static const char *TAG = "app_driver";

/* This is the button that is used for toggling the power */
#define BUTTON_GPIO          CONFIG_EXAMPLE_BOARD_BUTTON_GPIO
#define BUTTON_ACTIVE_LEVEL  0

/* This is the GPIO on which the power will be set */
#define OUTPUT_GPIO    CONFIG_EXAMPLE_OUTPUT_GPIO
static bool g_power_state = DEFAULT_POWER;
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<CONFIG_SENSOR_THERMOSTAT_GPIO) || (1ULL<< CONFIG_RELAY_GPIO)
#define GPIO_INPUT_PIN_SEL  (1ULL<<CONFIG_RELAY_GPIO) || (1ULL<<CONFIG_PIN_NUM_BK_LIGHT)
/* These values correspoind to H,S,V = 120,100,10 */
#define DEFAULT_RED     0
#define DEFAULT_GREEN   25
#define DEFAULT_BLUE    0

#define WIFI_RESET_BUTTON_TIMEOUT       3
#define FACTORY_RESET_BUTTON_TIMEOUT    10


static void push_btn_cb(void *arg)
{
    bool new_state = !g_power_state;
    relay_operation(new_state);
#ifdef CONFIG_EXAMPLE_ENABLE_TEST_NOTIFICATIONS
    /* This snippet has been added just to demonstrate how the APIs esp_rmaker_param_update_and_notify()
     * and esp_rmaker_raise_alert() can be used to trigger push notifications on the phone apps.
     * Normally, there should not be a need to use these APIs for such simple operations. Please check
     * API documentation for details.
     */
    if (new_state) {
        esp_rmaker_param_update_and_notify(
                esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME),
                esp_rmaker_bool(new_state));
    } else {
        esp_rmaker_param_update_and_report(
                esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME),
                esp_rmaker_bool(new_state));
        esp_rmaker_raise_alert("Switch was turned off");
    }
#else
    esp_rmaker_param_update_and_report(
            esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_POWER_NAME),
            esp_rmaker_bool(new_state));
    
    esp_rmaker_param_update_and_report(
            esp_rmaker_device_get_param_by_name(thermostat_device, "temperatura"),
            esp_rmaker_float(22.5));


#endif
}



void gpio_rele_in_out() {
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
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

    button_handle_t btn_handle = iot_button_create(BUTTON_GPIO, BUTTON_ACTIVE_LEVEL);
    if (btn_handle) {
        /* Register a callback for a button tap (short press) event */
        iot_button_set_evt_cb(btn_handle, BUTTON_CB_TAP, push_btn_cb, NULL);
        /* Register Wi-Fi reset and factory reset functionality on same button */
        app_reset_button_register(btn_handle, WIFI_RESET_BUTTON_TIMEOUT, FACTORY_RESET_BUTTON_TIMEOUT);
    }

    gpio_rele_in_out();
    relay_operation(false);
}



bool app_driver_get_state(void)
{
    return g_power_state;
}
