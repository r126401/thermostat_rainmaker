/*
 * codigo.c
 *
 *  Created on: 3 jun 2023
 *      Author: t126401
 */



#include "lv_thermostat.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "lvgl.h"
#include "esp_log.h"
#include "esp_err.h"

#include "time.h"

#include "lv_rgb_main.h"
#include "lv_factory_reset.h"

#include "app_priv.h"



/*/
#ifndef CONFIG_LCD_H_RES

#define CONFIG_LCD_H_RES 800
#define CONFIG_LCD_V_RES 480

#endif
*/
//#define CONFIG_LV_DISPLAY_WIDTH 480
//#define CONFIG_LV_DISPLAY_height 272

lv_obj_t *lv_main_screen;
lv_obj_t *lv_layout_notification;
lv_obj_t *lv_layout_temperature;
lv_obj_t *lv_layout_threshold;
lv_obj_t *lv_layout_buttons_threshold;
lv_obj_t *lv_layout_schedule;
lv_obj_t *lv_text_temperature;
lv_obj_t *lv_icon_themometer;
lv_obj_t *lv_icon_heating;
lv_obj_t *lv_icon_threshold;
lv_obj_t *lv_icon_button_reset;
lv_obj_t *lv_text_threshold;
lv_obj_t *lv_text_status_application;
lv_obj_t *lv_text_from_schedule;
lv_obj_t *lv_text_to_schedule;
lv_obj_t *lv_text_smartconfig;
lv_obj_t *lv_text_icon_wifi;
lv_obj_t *lv_text_icon_reset;
lv_obj_t *lv_progress_schedule;


lv_style_t lv_style_layout_temperature;
lv_style_t lv_style_layout_threshold;
lv_style_t lv_style_status_application;
lv_style_t lv_style_main_screen;
lv_style_t lv_style_layout_notification;
lv_style_t lv_style_lv_layout_buttons_threshold;
lv_style_t lv_style_button_threshold;
lv_style_t lv_style_button_reset_app;
lv_style_t lv_style_layout_schedule;
lv_style_t lv_style_bar_schedule;
lv_style_t lv_style_button_icon_wifi;
lv_style_t lv_style_button_action;


lv_obj_t *lv_date_text;
lv_obj_t *lv_icon_broker_status;
lv_obj_t *lv_icon_device_status_wifi;
lv_obj_t *lv_icon_waiting_response;
lv_obj_t *lv_icon_action_upgrade;
lv_obj_t *lv_icon_ntp;
lv_obj_t *lv_icon_alarm;
lv_obj_t *lv_button_up_threshold;
lv_obj_t *lv_button_down_threshold;
lv_obj_t *lv_button_reset_app;
lv_obj_t *lv_button_action;
lv_obj_t *lv_icon_up_threshold;
lv_obj_t *lv_icon_down_threshold;
lv_obj_t *lv_icon_wifi;
lv_obj_t *lv_icon_reset;
lv_obj_t *lv_icon_action;

LV_IMG_DECLARE(ic_action_online);
LV_IMG_DECLARE(ic_action_offline);
LV_IMG_DECLARE(ic_wifi_on);
LV_IMG_DECLARE(ic_wifi_off);
LV_IMG_DECLARE(ic_action_waiting_response);
LV_IMG_DECLARE(ic_action_upgrade);
LV_IMG_DECLARE(ic_ntp_off);
LV_IMG_DECLARE(ic_warning);
LV_IMG_DECLARE(ic_heating);
LV_IMG_DECLARE(ic_thermometer);
LV_IMG_DECLARE(ic_threshold);
LV_IMG_DECLARE(ic_up_threshold);
LV_IMG_DECLARE(ic_down_threshold);
LV_IMG_DECLARE(ic_reset);
LV_IMG_DECLARE(ic_action_thermostat);
LV_IMG_DECLARE(ic_sun);
LV_IMG_DECLARE(ic_moon);

//LV_FONT_CUSTOM_DECLARE(lv_font_led_30);
LV_FONT_DECLARE(russo48);
LV_FONT_DECLARE(russo36);
LV_FONT_DECLARE(russo100);





lv_theme_t *th;

static const char *TAG = "lv_thermostat";





void lv_set_style_screen(lv_obj_t *display) {


	lv_theme_default_init(lv_obj_get_disp(lv_scr_act()),  /*Use the DPI, size, etc from this display*/
					lv_color_hex(0x0534F0), lv_color_hex(0x0534F0),   /*Primary and secondary palette*/
			                                        true,    /*Light or dark mode*/
			                                        &lv_font_montserrat_16); /*Small, normal, large fonts*/


	lv_style_init(&lv_style_main_screen);
	lv_obj_add_style(lv_main_screen, &lv_style_main_screen, LV_STATE_DEFAULT);


}


void lv_general_style(lv_style_t *style) {

	lv_style_set_pad_all(style, 0);
	lv_style_set_bg_opa(style, LV_OPA_TRANSP);
    lv_style_set_border_width(style, 0);



}




void lv_set_style_layout_notification() {



	lv_style_init(&lv_style_layout_notification);
	lv_obj_add_style(lv_layout_notification, &lv_style_layout_notification, LV_STATE_DEFAULT);
	lv_obj_set_style_base_dir(lv_layout_notification, LV_BASE_DIR_RTL, 1);
    lv_style_set_bg_opa(&lv_style_layout_notification, LV_OPA_TRANSP);
    lv_style_set_bg_color(&lv_style_layout_notification, lv_color_hex(0));
    lv_style_set_bg_grad_color(&lv_style_layout_notification, lv_color_hex(0x0534F0));
    lv_style_set_bg_grad_dir(&lv_style_layout_notification, LV_GRAD_DIR_HOR);
    lv_style_set_border_width(&lv_style_layout_notification, 0);

}



void lv_create_layout_nofitification() {


	//creating objects
	lv_layout_notification = lv_obj_create(lv_main_screen);
	
	lv_date_text = lv_label_create(lv_main_screen);
	lv_label_set_text_fmt(lv_date_text, "--:--");
	lv_label_set_long_mode(lv_date_text, 3);
	lv_obj_set_pos(lv_date_text, CONFIG_LCD_H_RES/2, 0);

	//style objects
	lv_set_style_layout_notification();
	lv_obj_set_style_pad_all(lv_layout_notification, 5, LV_PART_MAIN);
	lv_obj_set_style_text_font(lv_date_text, &lv_font_montserrat_26, LV_STATE_DEFAULT);


	//position objects

	lv_obj_set_pos(lv_layout_notification,0, 0);
	lv_obj_set_flex_flow(lv_layout_notification, LV_FLEX_FLOW_ROW_REVERSE);
	lv_obj_set_flex_align(lv_layout_notification, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END);
	lv_obj_align(lv_date_text, LV_ALIGN_TOP_MID, 0, 0);


	//size objects
	lv_obj_set_size(lv_layout_notification, CONFIG_LCD_H_RES, LV_SIZE_CONTENT);

	//callback functions


	//Icono conexion del dispositivo
	lv_icon_device_status_wifi = lv_img_create(lv_layout_notification);
	lv_img_set_src(lv_icon_device_status_wifi, &ic_wifi_off);

	//icono conexion al broker
	lv_icon_broker_status = lv_img_create(lv_layout_notification);
	lv_img_set_src(lv_icon_broker_status, &ic_action_offline);



	lv_icon_action_upgrade = lv_img_create(lv_layout_notification);
	lv_icon_ntp = lv_img_create(lv_layout_notification);
	lv_img_set_src(lv_icon_ntp, &ic_ntp_off);
	lv_icon_alarm = lv_img_create(lv_layout_notification);
	lv_img_set_src(lv_icon_alarm, &ic_warning);




}


void lv_set_lv_style_button_reset_app() {
	lv_style_init(&lv_style_button_reset_app);
	lv_style_set_pad_all(&lv_style_button_reset_app, 0);
	lv_style_set_bg_opa(&lv_style_button_reset_app, LV_OPA_TRANSP);
    lv_style_set_border_width(&lv_style_button_reset_app, 0);
	lv_obj_add_style(lv_button_reset_app, &lv_style_button_reset_app, LV_STATE_DEFAULT);

}



void lv_set_lv_style_button_action() {
	lv_style_init(&lv_style_button_action);
	lv_style_set_pad_all(&lv_style_button_action, 0);
	lv_style_set_bg_opa(&lv_style_button_action, LV_OPA_TRANSP);
    lv_style_set_border_width(&lv_style_button_action, 0);
	lv_obj_add_style(lv_button_action, &lv_style_button_action, LV_STATE_DEFAULT);

}




void lv_create_layout_temperature() {

	//char temperature[10];

	//create objects
	lv_layout_temperature = lv_obj_create(lv_main_screen);
	lv_icon_themometer = lv_img_create(lv_layout_temperature);
	lv_img_set_src(lv_icon_themometer, &ic_thermometer);
	lv_text_temperature = lv_label_create(lv_layout_temperature);
	//sprintf(temperature, "%.1f", datosApp->termostato.tempActual);
	lv_label_set_text(lv_text_temperature, "--.- ºC");

	//style objects
	lv_obj_set_style_text_font(lv_text_temperature, &russo48, LV_PART_MAIN);
	lv_set_style_layout_temperature();

	//position objects
	lv_obj_center(lv_text_temperature);
	lv_obj_align_to(lv_layout_temperature, lv_layout_notification, LV_ALIGN_OUT_BOTTOM_LEFT, CONFIG_LCD_H_RES/4 , CONFIG_LCD_V_RES/4);
	lv_obj_set_flex_align(lv_layout_temperature, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

	//size objects
	lv_obj_set_size(lv_layout_temperature, LV_SIZE_CONTENT, LV_SIZE_CONTENT);


	//callback functions

}

void lv_set_style_status_application() {

	lv_style_init(&lv_style_status_application);
	lv_style_set_text_font(&lv_style_status_application, &lv_font_montserrat_22);
	if (lv_text_status_application != NULL) {
		lv_obj_add_style(lv_text_status_application, &lv_style_status_application, LV_STATE_DEFAULT);
	}
	lv_style_set_pad_all(&lv_style_status_application, 0);
	lv_style_set_bg_opa(&lv_style_status_application, LV_OPA_TRANSP);
    lv_style_set_border_width(&lv_style_status_application, 0);

	//lv_obj_align_to(lv_text_status_application, lv_layout_temperature, LV_ALIGN_OUT_TOP_MID, 0, 0);



}

void lv_create_status_aplication() {

	lv_text_status_application = lv_label_create(lv_main_screen);
	lv_obj_align_to(lv_text_status_application, lv_layout_temperature, LV_ALIGN_OUT_TOP_LEFT, 50,-30);
	lv_set_style_status_application();
	lv_label_set_text(lv_text_status_application, " ");



}








void lv_status_device() {

	lv_update_alarm_device();
}

void lv_set_style_layout_temperature() {

	lv_style_init(&lv_style_layout_temperature);
	lv_obj_add_style(lv_layout_temperature, &lv_style_layout_temperature, LV_STATE_DEFAULT);
	lv_style_set_text_font(&lv_style_layout_temperature, &lv_font_montserrat_48);
	lv_obj_clear_flag(lv_layout_temperature, LV_OBJ_FLAG_SCROLLABLE);
    lv_style_set_bg_opa(&lv_style_layout_temperature, LV_OPA_TRANSP);
    lv_style_set_border_width(&lv_style_layout_temperature, 0);
    lv_style_set_pad_all(&lv_style_layout_temperature, 0);



}

void lv_set_style_threshold() {

	lv_style_init(&lv_style_layout_threshold);
	lv_obj_add_style(lv_layout_threshold, &lv_style_layout_threshold, LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(lv_layout_threshold, &russo36, LV_PART_MAIN);
	lv_obj_clear_flag(lv_layout_threshold, LV_OBJ_FLAG_SCROLLABLE);
    lv_style_set_bg_opa(&lv_style_layout_threshold, LV_OPA_TRANSP);
    lv_style_set_border_width(&lv_style_layout_threshold, 0);
    lv_style_set_pad_all(&lv_style_layout_threshold, 0);



}


void lv_create_layout_threshold() {

	lv_layout_threshold =  lv_obj_create(lv_main_screen);
	lv_obj_align_to(lv_layout_threshold, lv_layout_temperature, LV_ALIGN_OUT_BOTTOM_LEFT, 15, 20);
	lv_obj_set_flex_align(lv_layout_threshold, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_icon_threshold = lv_img_create(lv_layout_threshold);
	lv_img_set_src(lv_icon_threshold, &ic_threshold);
	lv_text_threshold = lv_label_create(lv_layout_threshold);
	lv_set_style_threshold();
	lv_obj_set_size(lv_layout_threshold, LV_SIZE_CONTENT, LV_SIZE_CONTENT);





}



void lv_update_status_application(char *status) {


	if (lv_text_status_application != NULL) {
		lv_label_set_text(lv_text_status_application, status);
	}


}

void lv_create_heating_icon() {

	lv_icon_heating = lv_img_create(lv_main_screen);
	lv_img_set_src(lv_icon_heating, &ic_heating);

	lv_obj_set_pos(lv_icon_heating, lv_pct(10), lv_pct(30));



}

void lv_set_status_heating(enum ESTADO_RELE rele) {

	if (rele == ON) {

		lv_obj_clear_flag(lv_icon_heating, LV_OBJ_FLAG_HIDDEN);
	} else {
		lv_obj_add_flag(lv_icon_heating, LV_OBJ_FLAG_HIDDEN);
	}




}


void lv_set_style_buttons_threshold() {

	lv_style_init(&lv_style_button_threshold);
	lv_obj_add_style(lv_button_up_threshold, &lv_style_button_threshold, LV_STATE_DEFAULT);
	lv_obj_add_style(lv_button_down_threshold, &lv_style_button_threshold, LV_STATE_DEFAULT);
	//lv_obj_add_style(lv_button_reset_app, &lv_style_button_threshold, LV_STATE_DEFAULT);
	lv_style_set_pad_all(&lv_style_button_threshold, 0);
	lv_style_set_border_width(&lv_style_button_threshold, 0);



}

static void event_handler_factory_reset(lv_event_t *event) {

	ESP_LOGE(TAG, ""TRAZAR"VAMOS A EJECUTAR EL RESET DE FABRICA", INFOTRAZA);
	lv_obj_t *button = lv_event_get_current_target(event);

	if (lv_msgbox_get_active_btn(button) == 0) {
		ESP_LOGW(TAG, ""TRAZAR"EL BOTON PULSADO ES ACEPTAR", INFOTRAZA);
		send_event_device(__func__, EVENT_FACTORY_BUTTON);
	}else {
		ESP_LOGW(TAG, ""TRAZAR"EL BOTON PULSADO ES CANCELAR", INFOTRAZA);
	}
	
	
	lv_msgbox_close(button);
	ESP_LOGW(TAG, ""TRAZAR"MSGBOX CERRADA", INFOTRAZA);





}


static void lv_msgbox_confirm_factory() {

	static const char * btns[] = {"Aceptar", "Cancelar", ""};
	lv_obj_t *box = lv_msgbox_create(lv_main_screen, "Factory reset", "Si aceptas, se perderan todos los datos del dispositivo", btns, true);
	lv_obj_add_event_cb(box, event_handler_factory_reset, LV_EVENT_RELEASED, box);
	lv_obj_center(box);



}


static void event_handler_up_threshold(lv_event_t *event) {

	send_event_device(__func__,EVENT_UP_THRESHOLD);
	ESP_LOGI("HOLA", "HE PULSADO ARRIBA");

}


static void event_handler_down_threshold(lv_event_t *event) {


	send_event_device(__func__,EVENT_DOWN_THRESHOLD);
	ESP_LOGI("HOLA", "HE PULSADO ABAJO");

}



static void event_handler_button_reset(lv_event_t *event) {

	static bool pulsado = false;

	
	switch (event->code) {
		case LV_EVENT_LONG_PRESSED:
			ESP_LOGE(TAG, ""TRAZAR"PULSADO BOTON LONG RESET", INFOTRAZA);
			lv_msgbox_confirm_factory();
			pulsado = true;
			break;
		case LV_EVENT_RELEASED:
			if (pulsado) {
				ESP_LOGE(TAG, ""TRAZAR" NO SE HACE NADA PULSADO BOTON RESET", INFOTRAZA);
				
			} else {
				ESP_LOGE(TAG, ""TRAZAR"PULSADO BOTON RESET", INFOTRAZA);
				send_event_device(__func__, EVENT_RESET_BUTTON);
			}
			pulsado = false;
			
			break;
		default:
			ESP_LOGE(TAG, ""TRAZAR"OTRO EVENTO DEL BOTON RESET", INFOTRAZA);
			break;
	}

			
	
	
}



static void event_handler_button_action(lv_event_t *event) {
	ESP_LOGI(TAG, ""TRAZAR"PULSADO BOTON ACTION_BUTTON", INFOTRAZA);
	send_event_device(__func__, EVENT_ACTION_BUTTON);
}


void lv_create_layout_buttons_threshold() {


	lv_layout_buttons_threshold = lv_obj_create(lv_main_screen);
	lv_set_style_layout_buttons_threshold();
	lv_obj_set_flex_flow(lv_layout_buttons_threshold, LV_FLEX_FLOW_COLUMN);

	lv_button_reset_app = lv_btn_create(lv_main_screen);
	lv_button_up_threshold = lv_btn_create(lv_layout_buttons_threshold);
	lv_button_action = lv_btn_create(lv_layout_buttons_threshold);
	lv_button_down_threshold = lv_btn_create(lv_layout_buttons_threshold);



	lv_obj_add_event_cb(lv_button_up_threshold, event_handler_up_threshold, LV_EVENT_CLICKED, datosApp);
	lv_obj_add_event_cb(lv_button_down_threshold, event_handler_down_threshold, LV_EVENT_CLICKED, datosApp);
	lv_obj_add_event_cb(lv_button_reset_app, event_handler_button_reset, LV_EVENT_RELEASED, datosApp);
	lv_obj_add_event_cb(lv_button_reset_app, event_handler_button_reset, LV_EVENT_LONG_PRESSED, datosApp);

	lv_obj_add_event_cb(lv_button_action, event_handler_button_action, LV_EVENT_CLICKED, datosApp);




	lv_icon_up_threshold = lv_img_create(lv_button_up_threshold);
	lv_icon_down_threshold = lv_img_create(lv_button_down_threshold);
	lv_icon_button_reset = lv_img_create(lv_button_reset_app);
	lv_icon_action = lv_img_create(lv_button_action);


	lv_img_set_src(lv_icon_down_threshold, &ic_down_threshold);

	lv_img_set_src(lv_icon_up_threshold, &ic_up_threshold);
	lv_img_set_src(lv_icon_button_reset, &ic_reset);
	lv_img_set_src(lv_icon_action, &ic_action_thermostat);



	lv_obj_set_size(lv_layout_buttons_threshold, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	lv_obj_set_size(lv_button_reset_app, 48, 48);
	lv_obj_set_size(lv_button_action, 48, 48);



	lv_obj_set_pos(lv_button_reset_app, 0,0);
	lv_obj_set_pos(lv_layout_buttons_threshold,lv_pct(87) , lv_pct(20));
	lv_set_style_buttons_threshold();
	lv_set_lv_style_button_reset_app();
	lv_set_lv_style_button_action();



}
void lv_set_style_layout_buttons_threshold() {

	lv_style_init(&lv_style_lv_layout_buttons_threshold);
	lv_obj_add_style(lv_layout_buttons_threshold, &lv_style_lv_layout_buttons_threshold, LV_STATE_DEFAULT);
	lv_style_set_pad_all(&lv_style_lv_layout_buttons_threshold, 0);
	lv_style_set_border_width(&lv_style_lv_layout_buttons_threshold, 2);
	lv_style_set_border_color(&lv_style_lv_layout_buttons_threshold, lv_color_hex(0xcccccc));

}


void lv_create_layout_schedule() {


	lv_layout_schedule = lv_obj_create(lv_main_screen);
	lv_obj_set_flex_flow(lv_layout_schedule, LV_FLEX_FLOW_ROW);
	lv_text_from_schedule = lv_label_create(lv_layout_schedule);
	lv_progress_schedule = lv_bar_create(lv_layout_schedule);
	lv_text_to_schedule = lv_label_create(lv_layout_schedule);
	lv_label_set_text(lv_text_from_schedule, "07:00");
	lv_label_set_text(lv_text_to_schedule, "18:50");
	lv_obj_set_size(lv_layout_schedule, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	lv_obj_align_to(lv_layout_schedule, lv_main_screen, LV_ALIGN_BOTTOM_MID, 0, 20);
	lv_set_style_layout_schedule();
	lv_bar_set_range(lv_progress_schedule, 0, 100);
	lv_update_bar_schedule(datosApp, false);
	lv_set_style_bar_schedule();




}

void lv_set_style_layout_schedule() {

	lv_style_init(&lv_style_layout_schedule);
	lv_obj_add_style(lv_layout_schedule, &lv_style_layout_schedule, LV_STATE_DEFAULT);
    lv_style_set_bg_opa(&lv_style_layout_schedule, LV_OPA_TRANSP);
    lv_style_set_border_width(&lv_style_layout_schedule, 0);
    lv_style_set_pad_all(&lv_style_layout_schedule, 0);
    lv_set_style_bar_schedule();

}

void lv_set_style_bar_schedule() {

	lv_style_init(&lv_style_bar_schedule);
	lv_obj_add_style(lv_progress_schedule, &lv_style_bar_schedule, LV_STATE_DEFAULT);


}


void lv_update_bar_schedule(bool show) {


	struct tm current_schedule;
	time_t next_interval;
	time_t begin_interval;
	time_t now;
	esp_err_t error;
	int active_schedule;
	int duration;

	int progress;



	//pendiente determinar si el schedule esta activo o no
	if (show == false) {
		lv_obj_add_flag(lv_layout_schedule, LV_OBJ_FLAG_HIDDEN);
		ESP_LOGI(TAG, "ESCONDEMOS EL LAYOUT SCHEDULE");

		return;
	}





	struct tm fecha;
	//ESP_LOGI(TAG, ""TRAZAR"ACTUALIZAR_HORA", INFOTRAZA);
    time(&now);
    localtime_r(&now, &fecha);


	error = calcular_programa_activo(datosApp, &next_interval);

	active_schedule = datosApp->datosGenerales->nProgramaCandidato;


	current_schedule = datosApp->datosGenerales->programacion[active_schedule].programacion;
	begin_interval = mktime(&current_schedule);
	duration = datosApp->datosGenerales->programacion[active_schedule].duracion;

	if (error != ACTIVE_SCHEDULE) {
		ESP_LOGE(TAG, "SALIDA NO PREVISTA EN LV_UPDATE_BAR_SCHEDULE");
	}

	if (next_interval >= duration) {
		next_interval = begin_interval + duration;

	}


	ESP_LOGI(TAG, "intervalo inicio :%lld, intervalo fin : %lld y hora actual %lld", begin_interval, next_interval, now);
	progress = (now - begin_interval)* 100 / (next_interval - begin_interval);
	lv_label_set_text_fmt(lv_text_from_schedule, "%02d:%02d", current_schedule.tm_hour, current_schedule.tm_min);
	localtime_r(&next_interval, &fecha);
	lv_label_set_text_fmt(lv_text_to_schedule, "%02d:%02d", fecha.tm_hour, fecha.tm_min);
	ESP_LOGE(TAG, "PROGRESS: %d, %02d:%02d to %02d:%02d", progress, current_schedule.tm_hour, current_schedule.tm_min, fecha.tm_hour, fecha.tm_min);

	lv_obj_set_style_text_font(lv_text_from_schedule, &lv_font_montserrat_20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(lv_text_to_schedule, &lv_font_montserrat_20, LV_STATE_DEFAULT);
	lv_obj_clear_flag(lv_layout_schedule, LV_OBJ_FLAG_HIDDEN);
	lv_bar_set_value(lv_progress_schedule, progress, LV_ANIM_OFF);

}



void lv_update_alarm_device() {



	// ALARMA WIFI
/*
	if (lv_icon_device_status_wifi != NULL) {
		if (datosApp->alarmas[ALARM_WIFI].estado_alarma == ALARM_ON) {
			ESP_LOGE(TAG, "ALARMA WIFI ACTIVA");
			lv_img_set_src(lv_icon_device_status_wifi, &ic_wifi_off);
			lv_img_set_src(lv_icon_broker_status, &ic_action_offline);

		} else {
			lv_img_set_src(lv_icon_device_status_wifi, &ic_wifi_on);
		}
	}

	//ALARMA MQTT
	if (lv_icon_broker_status != NULL) {
		if(datosApp->alarmas[ALARM_MQTT].estado_alarma == ALARM_ON) {
			ESP_LOGE(TAG, "ALARMA MQTT ACTIVA");
			lv_img_set_src(lv_icon_broker_status, &ic_action_offline);

			} else {
				lv_img_set_src(lv_icon_broker_status, &ic_action_online);
			}
	}

	//ALARMA NTP
	if (lv_icon_ntp != NULL) {
		if (datosApp->alarmas[ALARM_NTP].estado_alarma == ALARM_ON) {
			lv_obj_clear_flag(lv_icon_ntp, LV_OBJ_FLAG_HIDDEN);
		} else {
			lv_obj_add_flag(lv_icon_ntp, LV_OBJ_FLAG_HIDDEN);
		}
	}

	if (lv_icon_alarm != NULL) {
		if (datosApp->alarmas[ALARM_DEVICE].estado_alarma == ALARM_ON) {

			lv_obj_clear_flag(lv_icon_alarm, LV_OBJ_FLAG_HIDDEN);
		} else {
			lv_obj_add_flag(lv_icon_alarm, LV_OBJ_FLAG_HIDDEN);
		}
	}
*/
}



static void event_handler_screen(lv_event_t *event) {


	//backlight_on();

}



void lv_normal_boot() {

	lv_obj_clear_flag(lv_layout_notification, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(lv_text_status_application, LV_OBJ_FLAG_HIDDEN);


}

void lv_factory_boot() {

	lv_obj_add_flag(lv_layout_notification, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(lv_text_status_application, LV_OBJ_FLAG_HIDDEN);


}


void lv_screen_thermostat() {

	enum ESTADO_RELE estado = ON;




	  //creating objects
	  lv_main_screen = lv_obj_create(NULL);
	  //lv_main_screen = lv_scr_act();
	  lv_scr_load(lv_main_screen);
	  lv_create_layout_nofitification(datosApp);
	  lv_create_layout_temperature(datosApp);
	  lv_create_layout_threshold(datosApp);
	  lv_create_status_aplication(datosApp);
	  lv_create_heating_icon(datosApp);
	  lv_create_layout_buttons_threshold(datosApp);
	  lv_create_layout_schedule(datosApp);
	  //style objects

	  lv_set_style_screen(lv_main_screen);

	  //position objects

	  //size objects

	  //callback functions
		lv_obj_add_event_cb(lv_main_screen, event_handler_screen, LV_EVENT_CLICKED, datosApp);

	 lv_update_alarm_device(datosApp);
	//lv_status_device(datosApp);
	lv_set_status_heating(datosApp, estado);
	lv_update_threshold(datosApp, true);


	//lv_update_temperature(datosApp);

}






void lv_update_device() {

	ESP_LOGI(TAG, ""TRAZAR"LV_UPDATE_DEVICE", INFOTRAZA);



}

static void lv_update_temp_threshold(float parameter, lv_obj_t *obj) {

	char data[10];

	if (obj != NULL) {

		if (parameter == -1000) {
			ESP_LOGE(TAG, "TEMPERATURA ACTUAL NO DISPONIBLE");
			lv_label_set_text_fmt(obj, "--.- ºC");
		} else {
			ESP_LOGI(TAG, ""TRAZAR"PINTAMOS LA TEMPERATURA ACTUAL: %.1f", INFOTRAZA, parameter);
			sprintf(data, "%.1f", parameter);
			lv_label_set_text_fmt(obj, "%s ºC", data);
		}

	} else {
		ESP_LOGE(TAG, ""TRAZAR"LA TEMPERATURA TODAVIA ES NULA:", INFOTRAZA);
	}
}

bool lv_update_hour(char* hour) {



	if ((lv_date_text != NULL) && (hour != NULL)){
		lv_label_set_text(lv_date_text, hour);
		ESP_LOGI(TAG, ""TRAZAR"hora actualizada: %s", INFOTRAZA, hour);
		return true;

	} else {
		ESP_LOGW(TAG, ""TRAZAR"No se puede actualizar la hora en el display", INFOTRAZA);
		return false;
	}
}

void lv_update_temperature() {

	lv_update_temp_threshold(datosApp->termostato.tempActual, lv_text_temperature);

}

void lv_update_threshold(bool permanent) {

	if (lv_text_threshold != NULL) {
		if (permanent) {
			lv_obj_set_style_text_color(lv_text_threshold, lv_color_hex(0x0534F0), LV_PART_MAIN);

		} else {
			lv_obj_set_style_text_color(lv_text_threshold, lv_color_hex(0xDEFF00), LV_PART_MAIN);
		}
	}


	lv_update_temp_threshold(datosApp->termostato.tempUmbral, lv_text_threshold);


}


void lv_update_relay(ESTADO_RELE relay) {


	if (lv_icon_heating != NULL) {
		if (relay == ON) {
			lv_obj_clear_flag(lv_icon_heating, LV_OBJ_FLAG_HIDDEN);

		} else {
			lv_obj_add_flag(lv_icon_heating, LV_OBJ_FLAG_HIDDEN);
		}
	}

}



static void event_handler_smartconfig(lv_event_t *event) {

	static bool pulse = false;

	if (!pulse) {
		pulse = true;
		ESP_LOGI(TAG, ""TRAZAR"event_handler_smartconfig", INFOTRAZA);
		send_event(__func__,EVENT_SMARTCONFIG_START);
		lv_obj_add_flag(lv_icon_wifi, LV_OBJ_FLAG_HIDDEN);
		lv_create_screen_factory();


	}
}


void lv_set_style_button_icon_wifi() {

	lv_style_init(&lv_style_button_icon_wifi);
	lv_general_style(&lv_style_button_icon_wifi);



}

// Función para animar el cambio de color del icono
static void color_animation(void *btn, int32_t value)
{
    // Cambia el tono de rojo (0xFF0000) a verde (0x00FF00)
    //lv_obj_set_style_local_image_recolor(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, value);
	lv_obj_set_style_text_color(btn, lv_color_hex(value), LV_PART_MAIN);
	



}


void animation_icon_wifi() {



    // Define un objeto de animación
    lv_anim_t a;
    lv_anim_init(&a);

    // Configura la animación
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)color_animation);
	lv_anim_set_var(&a, lv_text_icon_wifi);
	lv_anim_set_values(&a, -20, 40);
    //lv_anim_set_values(&a, lv_color_hex(0xFF0000), lv_color_hex(0x00FF00));  // Rojo a verde
    lv_anim_set_time(&a, 100);  // Duración de la animación en milisegundos
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);  // Repetir infinitamente

    // Inicia la animación
    lv_anim_start(&a);



}


void lv_configure_smartconfig() {


	ESP_LOGW(TAG, ""TRAZAR" LV CONFIGURACION WIFI", INFOTRAZA);
	//creating objects

	if (lv_icon_wifi == NULL) {
		ESP_LOGW(TAG, ""TRAZAR" Vamos a crear el objeto lv_icon_wifi", INFOTRAZA);
		lv_icon_wifi = lv_btn_create(lv_main_screen);
		lv_text_icon_wifi = lv_label_create(lv_icon_wifi);

	ESP_LOGW(TAG, ""TRAZAR" Vamos a esconder el objeto lv_icon_wifi", INFOTRAZA);
	lv_obj_clear_flag(lv_icon_wifi, LV_OBJ_FLAG_HIDDEN);
	lv_label_set_text(lv_text_icon_wifi, LV_SYMBOL_WIFI);

	}

	//style objects
	lv_set_style_status_application();

	lv_obj_add_style(lv_icon_wifi, &lv_style_status_application, LV_STATE_DEFAULT);
	lv_obj_add_style(lv_text_icon_wifi, &lv_style_status_application, LV_STATE_DEFAULT);

	//position objects
	lv_obj_set_pos(lv_icon_wifi, lv_pct(10), lv_pct(60));
	//size objects
	lv_obj_set_size(lv_icon_wifi, 48,48);

	//callback functions
	lv_obj_add_event_cb(lv_icon_wifi, event_handler_smartconfig, LV_EVENT_CLICKED, NULL);

	lv_obj_set_style_text_color(lv_text_icon_wifi, lv_color_hex(0xFF0000), LV_PART_MAIN);
	//animation_icon_wifi();

}


void lv_paint_sub_status_app(SUB_STATUS_APP status) {



	switch (status)
	{
	case NORMAL_SUB_STATUS:
		lv_img_set_src(lv_icon_action, &ic_action_thermostat);
		break;
	case MOON_SUB_STATUS:
		lv_img_set_src(lv_icon_action, &ic_moon);
		break;
	case SUN_SUB_STATUS:
		lv_img_set_src(lv_icon_action, &ic_sun);
		break;
	default:
		break;
	}

	

}





