/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_light_control_screen(lv_ui *ui){

	//Write codes light_control_screen
	ui->light_control_screen = lv_obj_create(NULL, NULL);

	//Write codes light_control_screen_background
	ui->light_control_screen_background = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_background
	static lv_style_t style_light_control_screen_background_main;
	lv_style_reset(&style_light_control_screen_background_main);
	lv_style_init(&style_light_control_screen_background_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_background_main
	lv_style_set_image_recolor(&style_light_control_screen_background_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_background_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_background_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_background, LV_IMG_PART_MAIN, &style_light_control_screen_background_main);
	lv_obj_set_pos(ui->light_control_screen_background, 0, 0);
	lv_obj_set_size(ui->light_control_screen_background, 480, 272);
	lv_obj_set_click(ui->light_control_screen_background, true);
	lv_img_set_src(ui->light_control_screen_background,&_background_alpha_480x272);
	lv_img_set_pivot(ui->light_control_screen_background, 0,0);
	lv_img_set_angle(ui->light_control_screen_background, 0);

	//Write codes light_control_screen_home_icon
	ui->light_control_screen_home_icon = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_home_icon
	static lv_style_t style_light_control_screen_home_icon_main;
	lv_style_reset(&style_light_control_screen_home_icon_main);
	lv_style_init(&style_light_control_screen_home_icon_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_home_icon_main
	lv_style_set_image_recolor(&style_light_control_screen_home_icon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_home_icon_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_home_icon_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_home_icon, LV_IMG_PART_MAIN, &style_light_control_screen_home_icon_main);
	lv_obj_set_pos(ui->light_control_screen_home_icon, 9, 10);
	lv_obj_set_size(ui->light_control_screen_home_icon, 32, 31);
	lv_obj_set_click(ui->light_control_screen_home_icon, true);
	lv_img_set_src(ui->light_control_screen_home_icon,&_button_home_alpha_32x31);
	lv_img_set_pivot(ui->light_control_screen_home_icon, 0,0);
	lv_img_set_angle(ui->light_control_screen_home_icon, 0);

	//Write codes light_control_screen_lightcontrol_text
	ui->light_control_screen_lightcontrol_text = lv_label_create(ui->light_control_screen, NULL);
	lv_label_set_text(ui->light_control_screen_lightcontrol_text, "灯光控制");
	lv_label_set_long_mode(ui->light_control_screen_lightcontrol_text, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->light_control_screen_lightcontrol_text, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for light_control_screen_lightcontrol_text
	static lv_style_t style_light_control_screen_lightcontrol_text_main;
	lv_style_reset(&style_light_control_screen_lightcontrol_text_main);
	lv_style_init(&style_light_control_screen_lightcontrol_text_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_lightcontrol_text_main
	lv_style_set_radius(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, &lv_font_simsun_24);
	lv_style_set_text_letter_space(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_light_control_screen_lightcontrol_text_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->light_control_screen_lightcontrol_text, LV_LABEL_PART_MAIN, &style_light_control_screen_lightcontrol_text_main);
	lv_obj_set_pos(ui->light_control_screen_lightcontrol_text, 155, 55);
	lv_obj_set_size(ui->light_control_screen_lightcontrol_text, 170, 0);

	//Write codes light_control_screen_led1_dark
	ui->light_control_screen_led1_dark = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_led1_dark
	static lv_style_t style_light_control_screen_led1_dark_main;
	lv_style_reset(&style_light_control_screen_led1_dark_main);
	lv_style_init(&style_light_control_screen_led1_dark_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led1_dark_main
	lv_style_set_image_recolor(&style_light_control_screen_led1_dark_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led1_dark_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led1_dark_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led1_dark, LV_IMG_PART_MAIN, &style_light_control_screen_led1_dark_main);
	lv_obj_set_pos(ui->light_control_screen_led1_dark, 75, 100);
	lv_obj_set_size(ui->light_control_screen_led1_dark, 60, 70);
	lv_obj_set_click(ui->light_control_screen_led1_dark, true);
	lv_img_set_src(ui->light_control_screen_led1_dark,&_icon_led_dark_alpha_60x70);
	lv_img_set_pivot(ui->light_control_screen_led1_dark, 0,0);
	lv_img_set_angle(ui->light_control_screen_led1_dark, 0);

	//Write codes light_control_screen_led2_dark
	ui->light_control_screen_led2_dark = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_led2_dark
	static lv_style_t style_light_control_screen_led2_dark_main;
	lv_style_reset(&style_light_control_screen_led2_dark_main);
	lv_style_init(&style_light_control_screen_led2_dark_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led2_dark_main
	lv_style_set_image_recolor(&style_light_control_screen_led2_dark_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led2_dark_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led2_dark_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led2_dark, LV_IMG_PART_MAIN, &style_light_control_screen_led2_dark_main);
	lv_obj_set_pos(ui->light_control_screen_led2_dark, 210, 100);
	lv_obj_set_size(ui->light_control_screen_led2_dark, 60, 70);
	lv_obj_set_click(ui->light_control_screen_led2_dark, true);
	lv_img_set_src(ui->light_control_screen_led2_dark,&_icon_led_dark_alpha_60x70);
	lv_img_set_pivot(ui->light_control_screen_led2_dark, 0,0);
	lv_img_set_angle(ui->light_control_screen_led2_dark, 0);

	//Write codes light_control_screen_led3_dark
	ui->light_control_screen_led3_dark = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_led3_dark
	static lv_style_t style_light_control_screen_led3_dark_main;
	lv_style_reset(&style_light_control_screen_led3_dark_main);
	lv_style_init(&style_light_control_screen_led3_dark_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led3_dark_main
	lv_style_set_image_recolor(&style_light_control_screen_led3_dark_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led3_dark_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led3_dark_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led3_dark, LV_IMG_PART_MAIN, &style_light_control_screen_led3_dark_main);
	lv_obj_set_pos(ui->light_control_screen_led3_dark, 340, 100);
	lv_obj_set_size(ui->light_control_screen_led3_dark, 60, 70);
	lv_obj_set_click(ui->light_control_screen_led3_dark, true);
	lv_img_set_src(ui->light_control_screen_led3_dark,&_icon_led_dark_alpha_60x70);
	lv_img_set_pivot(ui->light_control_screen_led3_dark, 0,0);
	lv_img_set_angle(ui->light_control_screen_led3_dark, 0);

	//Write codes light_control_screen_led1_button
	ui->light_control_screen_led1_button = lv_imgbtn_create(ui->light_control_screen, NULL);

	//Write style LV_IMGBTN_PART_MAIN for light_control_screen_led1_button
	static lv_style_t style_light_control_screen_led1_button_main;
	lv_style_reset(&style_light_control_screen_led1_button_main);
	lv_style_init(&style_light_control_screen_led1_button_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led1_button_main
	lv_style_set_text_color(&style_light_control_screen_led1_button_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_light_control_screen_led1_button_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led1_button_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led1_button_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led1_button, LV_IMGBTN_PART_MAIN, &style_light_control_screen_led1_button_main);
	lv_obj_set_pos(ui->light_control_screen_led1_button, 65, 185);
	lv_obj_set_size(ui->light_control_screen_led1_button, 80, 25);
	lv_imgbtn_set_src(ui->light_control_screen_led1_button,LV_BTN_STATE_RELEASED,&_button_off_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led1_button,LV_BTN_STATE_PRESSED,&_button_on_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led1_button,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led1_button,LV_BTN_STATE_CHECKED_PRESSED,&_button_off_alpha_80x25);
	lv_imgbtn_set_checkable(ui->light_control_screen_led1_button, true);

	//Write codes light_control_screen_led2_button
	ui->light_control_screen_led2_button = lv_imgbtn_create(ui->light_control_screen, NULL);

	//Write style LV_IMGBTN_PART_MAIN for light_control_screen_led2_button
	static lv_style_t style_light_control_screen_led2_button_main;
	lv_style_reset(&style_light_control_screen_led2_button_main);
	lv_style_init(&style_light_control_screen_led2_button_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led2_button_main
	lv_style_set_text_color(&style_light_control_screen_led2_button_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_light_control_screen_led2_button_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led2_button_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led2_button_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led2_button, LV_IMGBTN_PART_MAIN, &style_light_control_screen_led2_button_main);
	lv_obj_set_pos(ui->light_control_screen_led2_button, 200, 185);
	lv_obj_set_size(ui->light_control_screen_led2_button, 80, 25);
	lv_imgbtn_set_src(ui->light_control_screen_led2_button,LV_BTN_STATE_RELEASED,&_button_off_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led2_button,LV_BTN_STATE_PRESSED,&_button_on_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led2_button,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led2_button,LV_BTN_STATE_CHECKED_PRESSED,&_button_off_alpha_80x25);
	lv_imgbtn_set_checkable(ui->light_control_screen_led2_button, true);

	//Write codes light_control_screen_led3_button
	ui->light_control_screen_led3_button = lv_imgbtn_create(ui->light_control_screen, NULL);

	//Write style LV_IMGBTN_PART_MAIN for light_control_screen_led3_button
	static lv_style_t style_light_control_screen_led3_button_main;
	lv_style_reset(&style_light_control_screen_led3_button_main);
	lv_style_init(&style_light_control_screen_led3_button_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led3_button_main
	lv_style_set_text_color(&style_light_control_screen_led3_button_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_light_control_screen_led3_button_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led3_button_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led3_button_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led3_button, LV_IMGBTN_PART_MAIN, &style_light_control_screen_led3_button_main);
	lv_obj_set_pos(ui->light_control_screen_led3_button, 330, 185);
	lv_obj_set_size(ui->light_control_screen_led3_button, 80, 25);
	lv_imgbtn_set_src(ui->light_control_screen_led3_button,LV_BTN_STATE_RELEASED,&_button_off_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led3_button,LV_BTN_STATE_PRESSED,&_button_on_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led3_button,LV_BTN_STATE_CHECKED_RELEASED,&_button_on_alpha_80x25);
	lv_imgbtn_set_src(ui->light_control_screen_led3_button,LV_BTN_STATE_CHECKED_PRESSED,&_button_off_alpha_80x25);
	lv_imgbtn_set_checkable(ui->light_control_screen_led3_button, true);

	//Write codes light_control_screen_msrtos_logo
	ui->light_control_screen_msrtos_logo = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_msrtos_logo
	static lv_style_t style_light_control_screen_msrtos_logo_main;
	lv_style_reset(&style_light_control_screen_msrtos_logo_main);
	lv_style_init(&style_light_control_screen_msrtos_logo_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_msrtos_logo_main
	lv_style_set_image_recolor(&style_light_control_screen_msrtos_logo_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_msrtos_logo_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_msrtos_logo_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_msrtos_logo, LV_IMG_PART_MAIN, &style_light_control_screen_msrtos_logo_main);
	lv_obj_set_pos(ui->light_control_screen_msrtos_logo, 355, 230);
	lv_obj_set_size(ui->light_control_screen_msrtos_logo, 100, 18);
	lv_obj_set_click(ui->light_control_screen_msrtos_logo, true);
	lv_img_set_src(ui->light_control_screen_msrtos_logo,&_msrtos_logo_alpha_100x18);
	lv_img_set_pivot(ui->light_control_screen_msrtos_logo, 0,0);
	lv_img_set_angle(ui->light_control_screen_msrtos_logo, 0);

	//Write codes light_control_screen_led1_light
	ui->light_control_screen_led1_light = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_led1_light
	static lv_style_t style_light_control_screen_led1_light_main;
	lv_style_reset(&style_light_control_screen_led1_light_main);
	lv_style_init(&style_light_control_screen_led1_light_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led1_light_main
	lv_style_set_image_recolor(&style_light_control_screen_led1_light_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led1_light_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led1_light_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led1_light, LV_IMG_PART_MAIN, &style_light_control_screen_led1_light_main);
	lv_obj_set_pos(ui->light_control_screen_led1_light, 75, 100);
	lv_obj_set_size(ui->light_control_screen_led1_light, 60, 70);
	lv_obj_set_click(ui->light_control_screen_led1_light, true);
	lv_img_set_src(ui->light_control_screen_led1_light,&_icon_led_light_alpha_60x70);
	lv_img_set_pivot(ui->light_control_screen_led1_light, 0,0);
	lv_img_set_angle(ui->light_control_screen_led1_light, 0);
	lv_obj_set_hidden(ui->light_control_screen_led1_light, true);

	//Write codes light_control_screen_led2_light
	ui->light_control_screen_led2_light = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_led2_light
	static lv_style_t style_light_control_screen_led2_light_main;
	lv_style_reset(&style_light_control_screen_led2_light_main);
	lv_style_init(&style_light_control_screen_led2_light_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led2_light_main
	lv_style_set_image_recolor(&style_light_control_screen_led2_light_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led2_light_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led2_light_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led2_light, LV_IMG_PART_MAIN, &style_light_control_screen_led2_light_main);
	lv_obj_set_pos(ui->light_control_screen_led2_light, 210, 100);
	lv_obj_set_size(ui->light_control_screen_led2_light, 60, 70);
	lv_obj_set_click(ui->light_control_screen_led2_light, true);
	lv_img_set_src(ui->light_control_screen_led2_light,&_icon_led_light_alpha_60x70);
	lv_img_set_pivot(ui->light_control_screen_led2_light, 0,0);
	lv_img_set_angle(ui->light_control_screen_led2_light, 0);
	lv_obj_set_hidden(ui->light_control_screen_led2_light, true);

	//Write codes light_control_screen_led3_light
	ui->light_control_screen_led3_light = lv_img_create(ui->light_control_screen, NULL);

	//Write style LV_IMG_PART_MAIN for light_control_screen_led3_light
	static lv_style_t style_light_control_screen_led3_light_main;
	lv_style_reset(&style_light_control_screen_led3_light_main);
	lv_style_init(&style_light_control_screen_led3_light_main);

	//Write style state: LV_STATE_DEFAULT for style_light_control_screen_led3_light_main
	lv_style_set_image_recolor(&style_light_control_screen_led3_light_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_light_control_screen_led3_light_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_light_control_screen_led3_light_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->light_control_screen_led3_light, LV_IMG_PART_MAIN, &style_light_control_screen_led3_light_main);
	lv_obj_set_pos(ui->light_control_screen_led3_light, 340, 100);
	lv_obj_set_size(ui->light_control_screen_led3_light, 60, 70);
	lv_obj_set_click(ui->light_control_screen_led3_light, true);
	lv_img_set_src(ui->light_control_screen_led3_light,&_icon_led_light_alpha_60x70);
	lv_img_set_pivot(ui->light_control_screen_led3_light, 0,0);
	lv_img_set_angle(ui->light_control_screen_led3_light, 0);
	lv_obj_set_hidden(ui->light_control_screen_led3_light, true);

	//Init events for screen
	events_init_light_control_screen(ui);
}
