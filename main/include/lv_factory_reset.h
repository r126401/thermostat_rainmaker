/*
 * lv_factory_reset.h
 *
 *  Created on: 8 jun 2023
 *      Author: t126401
 */

#ifndef LV_SRC_INCLUDE_LV_FACTORY_RESET_H_
#define LV_SRC_INCLUDE_LV_FACTORY_RESET_H_




#include "lvgl.h"

/**
 * @fn void lv_set_style_factory_screen()
 * @brief
 *
 */
void lv_set_style_factory_screen();
void lv_set_style_text_area_factory();
void lv_set_style_button_reset();

void lv_create_screen_factory();
void lv_create_text_area();
void lv_screen_factory_reset();



void lv_smartconfig_notify();


#endif /* LV_SRC_INCLUDE_LV_FACTORY_RESET_H_ */
