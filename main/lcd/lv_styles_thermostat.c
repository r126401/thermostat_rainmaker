
#include "lv_styles_thermostat.h"
#include "lvgl.h"

#define LV_COLOR_BUTTON_RESET 0xE0E623
lv_style_t style_buttons;

LV_IMAGE_DECLARE(img_skew_strip);



void set_style_buttons() {

    lv_style_init(&style_buttons);
    lv_style_set_radius(&style_buttons, 10);
    lv_style_set_bg_opa(&style_buttons, LV_OPA_TRANSP);
    lv_style_set_bg_color(&style_buttons, lv_palette_lighten(LV_PALETTE_BLUE, 3));
    lv_style_set_bg_grad_color(&style_buttons, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&style_buttons, LV_GRAD_DIR_VER);
    lv_style_set_text_color(&style_buttons, lv_color_hex(LV_COLOR_BUTTON_RESET));
    lv_style_set_pad_all(&style_buttons, 0);
    lv_style_set_text_font(&style_buttons, &lv_font_montserrat_48);




}


void set_style_layout_schedule() {

    lv_style_init(&style_layout_schedule);
    lv_style_set_bg_opa(&style_layout_schedule, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_layout_schedule, 0);

}


void set_style_layout_notification() {

        lv_style_init(&style_layout_notification);
	//lv_obj_add_style(lv_layout_notification, &style_layout_notification, LV_STATE_DEFAULT);
	//lv_obj_set_style_base_dir(lv_layout_notification, LV_BASE_DIR_RTL, 1);
        lv_style_set_bg_opa(&style_layout_notification, LV_OPA_TRANSP);
        lv_style_set_bg_color(&style_layout_notification, lv_color_hex(0));
        lv_style_set_bg_grad_color(&style_layout_notification, lv_color_hex(0x0534F0));
        lv_style_set_bg_grad_dir(&style_layout_notification, LV_GRAD_DIR_HOR);
        lv_style_set_border_width(&style_layout_notification, 0);
        lv_style_set_text_font(&style_layout_notification, &lv_font_montserrat_24);
        lv_style_set_text_color(&style_layout_notification, lv_color_hex(LV_COLOR_TEXT_NOTIFICATION));

}

void set_style_threshold() {

	lv_style_init(&style_layout_threshold);
    lv_style_set_text_font(&style_layout_threshold, &russo36);
	//lv_obj_set_style_text_font(layout_threshold, &russo36, LV_PART_MAIN);
    lv_style_set_bg_opa(&style_layout_threshold, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_layout_threshold, 0);
    lv_style_set_pad_all(&style_layout_threshold, 0);
    lv_style_set_text_color(&style_layout_threshold, lv_color_hex(LV_COLOR_TEXT_NOTIFICATION));



}

void set_style_layout_temperature() {

	lv_style_init(&style_layout_temperature);
	lv_style_set_text_font(&style_layout_temperature, &lv_font_montserrat_48);
	//lv_obj_clear_flag(lv_layout_temperature, LV_OBJ_FLAG_SCROLLABLE);
    lv_style_set_bg_opa(&style_layout_temperature, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_layout_temperature, 0);
    lv_style_set_pad_all(&style_layout_temperature, 0);



}

void set_style_layout_button_threshold() {

	lv_style_init(&style_layout_buttons_threshold);
	lv_style_set_bg_opa(&style_layout_buttons_threshold, LV_OPA_TRANSP);
	lv_style_set_pad_all(&style_layout_buttons_threshold,10);
	lv_style_set_border_width(&style_layout_buttons_threshold, 0);


}


void set_style_buttons_threshold() {

    /*Init the style_buttons_threshold for the default state*/

    lv_style_init(&style_buttons_threshold);

    lv_style_set_radius(&style_buttons_threshold, 3);

    lv_style_set_bg_opa(&style_buttons_threshold, LV_OPA_20);
    lv_style_set_bg_color(&style_buttons_threshold, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style_buttons_threshold, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_dir(&style_buttons_threshold, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style_buttons_threshold, LV_OPA_40);
    lv_style_set_border_width(&style_buttons_threshold, 5);
    lv_style_set_border_color(&style_buttons_threshold, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style_buttons_threshold, 5);
    lv_style_set_shadow_color(&style_buttons_threshold, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_offset_y(&style_buttons_threshold, 5);

    lv_style_set_outline_opa(&style_buttons_threshold, LV_OPA_COVER);
    lv_style_set_outline_color(&style_buttons_threshold, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style_buttons_threshold, lv_color_white());
    lv_style_set_pad_all(&style_buttons_threshold, 10);

	lv_style_set_text_font(&style_buttons_threshold, &lv_font_montserrat_20);

    /*Init the pressed style*/

    lv_style_init(&style_buttons_threshold_pressed);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_buttons_threshold_pressed, 30);
    lv_style_set_outline_opa(&style_buttons_threshold_pressed, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_buttons_threshold_pressed, 5);
    lv_style_set_shadow_offset_y(&style_buttons_threshold_pressed, 3);
    lv_style_set_bg_color(&style_buttons_threshold_pressed, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_color(&style_buttons_threshold_pressed, lv_palette_darken(LV_PALETTE_BLUE, 4));

		lv_style_set_text_font(&style_buttons_threshold_pressed, &lv_font_montserrat_40);


    /*Add a transition to the outline*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&style_buttons_threshold_pressed, &trans);






}

void set_style_reset() {

    lv_style_init(&style_reset);
    lv_style_set_bg_opa(&style_reset, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_reset, 2);
    lv_style_set_border_color(&style_reset, lv_palette_main(LV_RB_COLOR_RED));
    lv_style_set_text_color(&style_reset, lv_color_hex(LV_COLOR_TEXT_NOTIFICATION));
    lv_style_set_text_font(&style_reset, &lv_font_montserrat_24);
    lv_style_set_pad_all(&style_reset, 8);
    lv_style_set_radius(&style_reset, 3);

}


void set_style_mode() {

    lv_style_init(&style_text_mode);
    lv_style_set_bg_opa(&style_text_mode, LV_OPA_TRANSP);
    //lv_style_set_border_opa(&style_text_mode, LV_OPA_0);
    lv_style_set_border_width(&style_text_mode, 2);
    lv_style_set_border_color(&style_text_mode, lv_color_hex(LV_COLOR_TEXT_NOTIFICATION));
    lv_style_set_text_color(&style_text_mode, lv_color_hex(LV_COLOR_TEXT_NOTIFICATION));
    lv_style_set_text_font(&style_text_mode, &lv_font_montserrat_20);
    lv_style_set_pad_all(&style_text_mode, 2);

}

void style_status_ok() {

    lv_style_init(&style_ok);
    lv_style_set_text_color(&style_ok, lv_color_hex(LV_COLOR_TEXT_NOTIFICATION));
    lv_style_set_text_font(&style_ok, &lv_font_montserrat_16);
    lv_style_set_pad_all(&style_ok, 8);



}



void set_style_schedule() {

    lv_style_init(&style_schedule);
    lv_style_set_bg_opa(&style_schedule, LV_OPA_COVER);
    lv_style_set_bg_color(&style_schedule, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style_schedule, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir(&style_schedule, LV_GRAD_DIR_HOR);
 

}