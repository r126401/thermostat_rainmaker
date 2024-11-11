/*
 * lv_factory_reset.c
 *
 *  Created on: 8 jun 2023
 *      Author: t126401
 */
/*
#include <include/datosapp.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include <include/lv_factory_reset.h>

*/


#include "lv_factory_reset.h"
#include <stdlib.h>
#include "lv_tools.h"
#include "esp_log.h"
#include "esp_system.h"

lv_obj_t *lv_screen_factory;
lv_obj_t *lv_text_area_factory;
lv_obj_t *lv_img_app;
lv_obj_t *lv_imgbtn_reset;
lv_obj_t *lv_text_reset;



lv_style_t	lv_style_factory_screen;
lv_style_t	lv_style_text_area_factory;
lv_style_t	lv_style_button_reset;

LV_IMG_DECLARE(ic_app);
LV_IMG_DECLARE(ic_action_reset);

static const char *TAG = "lv_factory_reset";

void lv_screen_factory_reset() {


	  lv_create_screen_factory();
	  ESP_LOGW(TAG, "PANTALLA FACTORY RESET CREADA");

}



void lv_set_style_factory_screen() {

	lv_style_init(&lv_style_factory_screen);
	lv_theme_default_init(lv_obj_get_disp(lv_scr_act()),  /*Use the DPI, size, etc from this display*/
					lv_color_hex(0x0534F0), lv_color_hex(0x0534F0),   /*Primary and secondary palette*/
			                                        true,    /*Light or dark mode*/
			                                        &lv_font_montserrat_16); /*Small, normal, large fonts*/
	lv_obj_add_style(lv_screen_factory, &lv_style_factory_screen, LV_PART_MAIN);


}


void lv_set_style_text_area_factory() {

	lv_style_init(&lv_style_text_area_factory);
	lv_obj_add_style(lv_text_area_factory, &lv_style_text_area_factory, LV_STATE_DEFAULT);

    lv_style_set_bg_opa(&lv_style_text_area_factory, LV_OPA_COVER);
    lv_style_set_bg_color(&lv_style_text_area_factory, lv_color_hex(0));
    lv_style_set_bg_grad_color(&lv_style_text_area_factory, lv_color_hex(0x0534F0));
    lv_style_set_bg_grad_dir(&lv_style_text_area_factory, LV_GRAD_DIR_VER);
    lv_style_set_line_width(&lv_style_text_area_factory, 0);



}
void lv_set_style_button_reset() {



}


static void event_handler_reset(lv_event_t *event) {

	if(lv_text_reset == NULL) {
		lv_text_reset = lv_label_create(lv_screen_factory);
		lv_obj_set_pos(lv_text_reset, 180, 20);
		lv_label_set_text(lv_text_reset, "Reiniciando...");
		esp_restart();


	}
}


static void event_handler_focused(lv_event_t *e) {

	lv_obj_clear_state(lv_text_area_factory, LV_STATE_FOCUSED);


}


void lv_create_screen_factory() {



	//create objects
	lv_screen_factory = lv_obj_create(NULL);
	lv_scr_load(lv_screen_factory);
	lv_create_text_area();
	lv_textarea_add_text(lv_text_area_factory, "PUESTA EN SERVICIO...\n\n");
	lv_textarea_add_text(lv_text_area_factory, "Por favor, abre la aplicacion MyHomeIot e instala un nuevo dispositivo.\n\n");
	lv_textarea_add_text(lv_text_area_factory, "Una vez instalado el dispositivo se conectara a la red y comenzara a funcionar.");

	lv_img_app = lv_img_create(lv_screen_factory);
	lv_img_set_src(lv_img_app, &ic_app);

	lv_imgbtn_reset = lv_imgbtn_create(lv_screen_factory);
	lv_imgbtn_set_src(lv_imgbtn_reset, LV_IMGBTN_STATE_RELEASED, &ic_action_reset, NULL, NULL);





	//style objects
	lv_set_style_factory_screen();

	//position objects
	lv_textarea_set_align(lv_text_area_factory, LV_TEXT_ALIGN_CENTER);
	lv_obj_set_pos(lv_img_app, lv_pct(5), lv_pct(5));
	lv_obj_set_pos(lv_imgbtn_reset, lv_pct(85) , lv_pct(5));



	//sizing objects
	lv_obj_set_size(lv_text_area_factory, lv_pct(60), LV_SIZE_CONTENT);

	// callback funtcions
	lv_obj_add_event_cb(lv_imgbtn_reset, event_handler_reset, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(lv_text_area_factory, event_handler_focused, LV_EVENT_FOCUSED, NULL);
















}
void lv_create_text_area(){

	//creamos el text_area

	lv_text_area_factory = lv_textarea_create(lv_screen_factory);
	//lv_obj_center(lv_text_area_factory);
	lv_obj_set_pos(lv_text_area_factory, lv_pct(20), lv_pct(5));
	lv_set_style_text_area_factory();
	lv_obj_clear_state(lv_text_area_factory, LV_STATE_FOCUSED);

}

void lv_smartconfig_notify() {



	ESP_LOGI(TAG, " Pintamos que estamos en smartconfig...");


}






