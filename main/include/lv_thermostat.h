/*
 * codigo.h
 *
 *  Created on: 3 jun 2023
 *      Author: t126401
 */

#ifndef LV_SRC_INCLUDE_LV_THERMOSTAT_H_

#define LV_SRC_INCLUDE_LV_THERMOSTAT_H_ 1

//#define _DEFAULT_SOURCE /* needed for usleep() */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "lvgl.h"
#include "lv_examples.h"
#include "lv_demos.h"

#include "esp_lcd_panel_io.h"






void lv_set_style_screen(lv_obj_t *display);
void lv_set_style_layout_notification();
void lv_create_layout_nofitification();
void lv_create_layout_temperature();
void lv_set_style_status_application();
void lv_create_status_aplication();
void lv_screen_thermostat();
void lv_update_alarm_device();
void lv_status_device();
void lv_set_style_layout_temperature();
void lv_set_style_threshold();
void lv_create_layout_threshold();
void lv_update_status_application(char *status);
void lv_update_heating();
void lv_create_heating_icon();
void lv_create_layout_buttons_threshold();
void lv_set_style_layout_buttons_threshold();
void lv_create_layout_schedule();
void lv_set_style_layout_schedule();
void lv_set_style_bar_schedule();
void lv_update_bar_schedule(, bool show);
void lv_update_threshold(, bool permanent);
void example_lvgl_demo_ui(lv_disp_t *disp);
void lv_update_device();
void lv_update_error_temperature();
void lv_update_temperature();
bool lv_update_hour(char* hour);
void lv_update_relay(ESTADO_RELE relay);
void lv_configure_smartconfig();
void lv_normal_boot();
void lv_factory_boot();
void lv_paint_sub_status_app(SUB_STATUS_APP status);

#endif /* LV_SRC_INCLUDE_LV_THERMOSTAT_H_ */
