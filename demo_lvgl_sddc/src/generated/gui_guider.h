/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts/guider_fonts.h"

typedef struct
{
	lv_obj_t *main_screen;
	lv_obj_t *main_screen_background;
	lv_obj_t *main_screen_temperature_tab;
	lv_obj_t *main_screen_lightcontrol_button;
	lv_obj_t *main_screen_lightcontrol_button_label;
	lv_obj_t *main_screen_temperature_text;
	lv_obj_t *main_screen_humidity_tab;
	lv_obj_t *main_screen_illumination_tab;
	lv_obj_t *main_screen_humidity_text;
	lv_obj_t *main_screen_light_text;
	lv_obj_t *main_screen_illumination_text;
	lv_obj_t *main_screen_msrtos_logo;
	lv_obj_t *main_screen_temperature_icon;
	lv_obj_t *main_screen_humidity_icon;
	lv_obj_t *main_screen_illumination_icon;
	lv_obj_t *main_screen_light_icon;
	lv_obj_t *main_screen_Concontroller_text;
	lv_obj_t *main_screen_temperature_value;
	lv_obj_t *main_screen_humidity_value;
	lv_obj_t *main_screen_illumination_value;
	lv_obj_t *light_control_screen;
	lv_obj_t *light_control_screen_background;
	lv_obj_t *light_control_screen_home_icon;
	lv_obj_t *light_control_screen_lightcontrol_text;
	lv_obj_t *light_control_screen_led1_dark;
	lv_obj_t *light_control_screen_led2_dark;
	lv_obj_t *light_control_screen_led3_dark;
	lv_obj_t *light_control_screen_led1_button;
	lv_obj_t *light_control_screen_led1_button_label;
	lv_obj_t *light_control_screen_led2_button;
	lv_obj_t *light_control_screen_led2_button_label;
	lv_obj_t *light_control_screen_led3_button;
	lv_obj_t *light_control_screen_led3_button_label;
	lv_obj_t *light_control_screen_msrtos_logo;
	lv_obj_t *light_control_screen_led1_light;
	lv_obj_t *light_control_screen_led2_light;
	lv_obj_t *light_control_screen_led3_light;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_main_screen(lv_ui *ui);
void setup_scr_light_control_screen(lv_ui *ui);
LV_IMG_DECLARE(_icon_led_dark_alpha_60x70);
LV_IMG_DECLARE(_background_alpha_480x272);
LV_IMG_DECLARE(_icon_humidity_alpha_40x40);
LV_IMG_DECLARE(_icon_light_alpha_40x40);
LV_IMG_DECLARE(_button_off_alpha_80x25);
LV_IMG_DECLARE(_bg_tab_page_alpha_100x135);
LV_IMG_DECLARE(_icon_lamp_alpha_40x40);
LV_IMG_DECLARE(_icon_led_light_alpha_60x70);
LV_IMG_DECLARE(_button_home_alpha_32x31);
LV_IMG_DECLARE(_icon_temperature_alpha_40x40);
LV_IMG_DECLARE(_button_on_alpha_80x25);
LV_IMG_DECLARE(_msrtos_logo_alpha_100x18);

#ifdef __cplusplus
}
#endif
#endif
