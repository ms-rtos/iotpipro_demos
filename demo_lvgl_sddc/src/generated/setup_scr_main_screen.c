/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_main_screen(lv_ui *ui){

	//Write codes main_screen
	ui->main_screen = lv_obj_create(NULL, NULL);

	//Write codes main_screen_background
	ui->main_screen_background = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_background
	static lv_style_t style_main_screen_background_main;
	lv_style_reset(&style_main_screen_background_main);
	lv_style_init(&style_main_screen_background_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_background_main
	lv_style_set_image_recolor(&style_main_screen_background_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_background_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_background_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_background, LV_IMG_PART_MAIN, &style_main_screen_background_main);
	lv_obj_set_pos(ui->main_screen_background, 0, 0);
	lv_obj_set_size(ui->main_screen_background, 480, 272);
	lv_obj_set_click(ui->main_screen_background, true);
	lv_img_set_src(ui->main_screen_background,&_background_alpha_480x272);
	lv_img_set_pivot(ui->main_screen_background, 0,0);
	lv_img_set_angle(ui->main_screen_background, 0);

	//Write codes main_screen_temperature_tab
	ui->main_screen_temperature_tab = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_temperature_tab
	static lv_style_t style_main_screen_temperature_tab_main;
	lv_style_reset(&style_main_screen_temperature_tab_main);
	lv_style_init(&style_main_screen_temperature_tab_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_temperature_tab_main
	lv_style_set_image_recolor(&style_main_screen_temperature_tab_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_temperature_tab_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_temperature_tab_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_temperature_tab, LV_IMG_PART_MAIN, &style_main_screen_temperature_tab_main);
	lv_obj_set_pos(ui->main_screen_temperature_tab, 16, 65);
	lv_obj_set_size(ui->main_screen_temperature_tab, 100, 135);
	lv_obj_set_click(ui->main_screen_temperature_tab, true);
	lv_img_set_src(ui->main_screen_temperature_tab,&_bg_tab_page_alpha_100x135);
	lv_img_set_pivot(ui->main_screen_temperature_tab, 0,0);
	lv_img_set_angle(ui->main_screen_temperature_tab, 0);

	//Write codes main_screen_lightcontrol_button
	ui->main_screen_lightcontrol_button = lv_imgbtn_create(ui->main_screen, NULL);

	//Write style LV_IMGBTN_PART_MAIN for main_screen_lightcontrol_button
	static lv_style_t style_main_screen_lightcontrol_button_main;
	lv_style_reset(&style_main_screen_lightcontrol_button_main);
	lv_style_init(&style_main_screen_lightcontrol_button_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_lightcontrol_button_main
	lv_style_set_text_color(&style_main_screen_lightcontrol_button_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_main_screen_lightcontrol_button_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_lightcontrol_button_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_lightcontrol_button_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_lightcontrol_button, LV_IMGBTN_PART_MAIN, &style_main_screen_lightcontrol_button_main);
	lv_obj_set_pos(ui->main_screen_lightcontrol_button, 364, 65);
	lv_obj_set_size(ui->main_screen_lightcontrol_button, 100, 135);
	lv_imgbtn_set_src(ui->main_screen_lightcontrol_button,LV_BTN_STATE_RELEASED,&_bg_tab_page_alpha_100x135);
	lv_imgbtn_set_checkable(ui->main_screen_lightcontrol_button, true);

	//Write codes main_screen_temperature_text
	ui->main_screen_temperature_text = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_temperature_text, "温度");
	lv_label_set_long_mode(ui->main_screen_temperature_text, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_temperature_text, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_temperature_text
	static lv_style_t style_main_screen_temperature_text_main;
	lv_style_reset(&style_main_screen_temperature_text_main);
	lv_style_init(&style_main_screen_temperature_text_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_temperature_text_main
	lv_style_set_radius(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_temperature_text_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_temperature_text, LV_LABEL_PART_MAIN, &style_main_screen_temperature_text_main);
	lv_obj_set_pos(ui->main_screen_temperature_text, 49, 70);
	lv_obj_set_size(ui->main_screen_temperature_text, 35, 0);

	//Write codes main_screen_humidity_tab
	ui->main_screen_humidity_tab = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_humidity_tab
	static lv_style_t style_main_screen_humidity_tab_main;
	lv_style_reset(&style_main_screen_humidity_tab_main);
	lv_style_init(&style_main_screen_humidity_tab_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_humidity_tab_main
	lv_style_set_image_recolor(&style_main_screen_humidity_tab_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_humidity_tab_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_humidity_tab_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_humidity_tab, LV_IMG_PART_MAIN, &style_main_screen_humidity_tab_main);
	lv_obj_set_pos(ui->main_screen_humidity_tab, 132, 65);
	lv_obj_set_size(ui->main_screen_humidity_tab, 100, 135);
	lv_obj_set_click(ui->main_screen_humidity_tab, true);
	lv_img_set_src(ui->main_screen_humidity_tab,&_bg_tab_page_alpha_100x135);
	lv_img_set_pivot(ui->main_screen_humidity_tab, 0,0);
	lv_img_set_angle(ui->main_screen_humidity_tab, 0);

	//Write codes main_screen_illumination_tab
	ui->main_screen_illumination_tab = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_illumination_tab
	static lv_style_t style_main_screen_illumination_tab_main;
	lv_style_reset(&style_main_screen_illumination_tab_main);
	lv_style_init(&style_main_screen_illumination_tab_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_illumination_tab_main
	lv_style_set_image_recolor(&style_main_screen_illumination_tab_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_illumination_tab_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_illumination_tab_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_illumination_tab, LV_IMG_PART_MAIN, &style_main_screen_illumination_tab_main);
	lv_obj_set_pos(ui->main_screen_illumination_tab, 248, 65);
	lv_obj_set_size(ui->main_screen_illumination_tab, 100, 135);
	lv_obj_set_click(ui->main_screen_illumination_tab, true);
	lv_img_set_src(ui->main_screen_illumination_tab,&_bg_tab_page_alpha_100x135);
	lv_img_set_pivot(ui->main_screen_illumination_tab, 0,0);
	lv_img_set_angle(ui->main_screen_illumination_tab, 0);

	//Write codes main_screen_humidity_text
	ui->main_screen_humidity_text = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_humidity_text, "湿度");
	lv_label_set_long_mode(ui->main_screen_humidity_text, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_humidity_text, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_humidity_text
	static lv_style_t style_main_screen_humidity_text_main;
	lv_style_reset(&style_main_screen_humidity_text_main);
	lv_style_init(&style_main_screen_humidity_text_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_humidity_text_main
	lv_style_set_radius(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_humidity_text_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_humidity_text, LV_LABEL_PART_MAIN, &style_main_screen_humidity_text_main);
	lv_obj_set_pos(ui->main_screen_humidity_text, 165, 70);
	lv_obj_set_size(ui->main_screen_humidity_text, 35, 0);

	//Write codes main_screen_light_text
	ui->main_screen_light_text = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_light_text, "灯光");
	lv_label_set_long_mode(ui->main_screen_light_text, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_light_text, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_light_text
	static lv_style_t style_main_screen_light_text_main;
	lv_style_reset(&style_main_screen_light_text_main);
	lv_style_init(&style_main_screen_light_text_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_light_text_main
	lv_style_set_radius(&style_main_screen_light_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_light_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_light_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_light_text_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_light_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_light_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_main_screen_light_text_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_main_screen_light_text_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_main_screen_light_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_light_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_light_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_light_text_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_light_text, LV_LABEL_PART_MAIN, &style_main_screen_light_text_main);
	lv_obj_set_pos(ui->main_screen_light_text, 397, 70);
	lv_obj_set_size(ui->main_screen_light_text, 35, 0);

	//Write codes main_screen_illumination_text
	ui->main_screen_illumination_text = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_illumination_text, "光照");
	lv_label_set_long_mode(ui->main_screen_illumination_text, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_illumination_text, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_illumination_text
	static lv_style_t style_main_screen_illumination_text_main;
	lv_style_reset(&style_main_screen_illumination_text_main);
	lv_style_init(&style_main_screen_illumination_text_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_illumination_text_main
	lv_style_set_radius(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_illumination_text_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_illumination_text, LV_LABEL_PART_MAIN, &style_main_screen_illumination_text_main);
	lv_obj_set_pos(ui->main_screen_illumination_text, 281, 70);
	lv_obj_set_size(ui->main_screen_illumination_text, 35, 0);

	//Write codes main_screen_msrtos_logo
	ui->main_screen_msrtos_logo = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_msrtos_logo
	static lv_style_t style_main_screen_msrtos_logo_main;
	lv_style_reset(&style_main_screen_msrtos_logo_main);
	lv_style_init(&style_main_screen_msrtos_logo_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_msrtos_logo_main
	lv_style_set_image_recolor(&style_main_screen_msrtos_logo_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_msrtos_logo_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_msrtos_logo_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_msrtos_logo, LV_IMG_PART_MAIN, &style_main_screen_msrtos_logo_main);
	lv_obj_set_pos(ui->main_screen_msrtos_logo, 190, 15);
	lv_obj_set_size(ui->main_screen_msrtos_logo, 100, 18);
	lv_obj_set_click(ui->main_screen_msrtos_logo, true);
	lv_img_set_src(ui->main_screen_msrtos_logo,&_msrtos_logo_alpha_100x18);
	lv_img_set_pivot(ui->main_screen_msrtos_logo, 0,0);
	lv_img_set_angle(ui->main_screen_msrtos_logo, 0);

	//Write codes main_screen_temperature_icon
	ui->main_screen_temperature_icon = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_temperature_icon
	static lv_style_t style_main_screen_temperature_icon_main;
	lv_style_reset(&style_main_screen_temperature_icon_main);
	lv_style_init(&style_main_screen_temperature_icon_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_temperature_icon_main
	lv_style_set_image_recolor(&style_main_screen_temperature_icon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_temperature_icon_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_temperature_icon_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_temperature_icon, LV_IMG_PART_MAIN, &style_main_screen_temperature_icon_main);
	lv_obj_set_pos(ui->main_screen_temperature_icon, 45, 110);
	lv_obj_set_size(ui->main_screen_temperature_icon, 40, 40);
	lv_obj_set_click(ui->main_screen_temperature_icon, true);
	lv_img_set_src(ui->main_screen_temperature_icon,&_icon_temperature_alpha_40x40);
	lv_img_set_pivot(ui->main_screen_temperature_icon, 0,0);
	lv_img_set_angle(ui->main_screen_temperature_icon, 0);

	//Write codes main_screen_humidity_icon
	ui->main_screen_humidity_icon = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_humidity_icon
	static lv_style_t style_main_screen_humidity_icon_main;
	lv_style_reset(&style_main_screen_humidity_icon_main);
	lv_style_init(&style_main_screen_humidity_icon_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_humidity_icon_main
	lv_style_set_image_recolor(&style_main_screen_humidity_icon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_humidity_icon_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_humidity_icon_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_humidity_icon, LV_IMG_PART_MAIN, &style_main_screen_humidity_icon_main);
	lv_obj_set_pos(ui->main_screen_humidity_icon, 160, 110);
	lv_obj_set_size(ui->main_screen_humidity_icon, 40, 40);
	lv_obj_set_click(ui->main_screen_humidity_icon, true);
	lv_img_set_src(ui->main_screen_humidity_icon,&_icon_humidity_alpha_40x40);
	lv_img_set_pivot(ui->main_screen_humidity_icon, 0,0);
	lv_img_set_angle(ui->main_screen_humidity_icon, 0);

	//Write codes main_screen_illumination_icon
	ui->main_screen_illumination_icon = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_illumination_icon
	static lv_style_t style_main_screen_illumination_icon_main;
	lv_style_reset(&style_main_screen_illumination_icon_main);
	lv_style_init(&style_main_screen_illumination_icon_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_illumination_icon_main
	lv_style_set_image_recolor(&style_main_screen_illumination_icon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_illumination_icon_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_illumination_icon_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_illumination_icon, LV_IMG_PART_MAIN, &style_main_screen_illumination_icon_main);
	lv_obj_set_pos(ui->main_screen_illumination_icon, 279, 110);
	lv_obj_set_size(ui->main_screen_illumination_icon, 40, 40);
	lv_obj_set_click(ui->main_screen_illumination_icon, true);
	lv_img_set_src(ui->main_screen_illumination_icon,&_icon_light_alpha_40x40);
	lv_img_set_pivot(ui->main_screen_illumination_icon, 0,0);
	lv_img_set_angle(ui->main_screen_illumination_icon, 0);

	//Write codes main_screen_light_icon
	ui->main_screen_light_icon = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_light_icon
	static lv_style_t style_main_screen_light_icon_main;
	lv_style_reset(&style_main_screen_light_icon_main);
	lv_style_init(&style_main_screen_light_icon_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_light_icon_main
	lv_style_set_image_recolor(&style_main_screen_light_icon_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_light_icon_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_light_icon_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_light_icon, LV_IMG_PART_MAIN, &style_main_screen_light_icon_main);
	lv_obj_set_pos(ui->main_screen_light_icon, 396, 110);
	lv_obj_set_size(ui->main_screen_light_icon, 40, 40);
	lv_obj_set_click(ui->main_screen_light_icon, true);
	lv_img_set_src(ui->main_screen_light_icon,&_icon_lamp_alpha_40x40);
	lv_img_set_pivot(ui->main_screen_light_icon, 0,0);
	lv_img_set_angle(ui->main_screen_light_icon, 0);

	//Write codes main_screen_Concontroller_text
	ui->main_screen_Concontroller_text = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_Concontroller_text, "Controller");
	lv_label_set_long_mode(ui->main_screen_Concontroller_text, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_Concontroller_text, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_Concontroller_text
	static lv_style_t style_main_screen_Concontroller_text_main;
	lv_style_reset(&style_main_screen_Concontroller_text_main);
	lv_style_init(&style_main_screen_Concontroller_text_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_Concontroller_text_main
	lv_style_set_radius(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_16);
	lv_style_set_text_letter_space(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_Concontroller_text_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_Concontroller_text, LV_LABEL_PART_MAIN, &style_main_screen_Concontroller_text_main);
	lv_obj_set_pos(ui->main_screen_Concontroller_text, 374, 165);
	lv_obj_set_size(ui->main_screen_Concontroller_text, 80, 0);

	//Write codes main_screen_temperature_value
	ui->main_screen_temperature_value = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_temperature_value, "");
	lv_label_set_long_mode(ui->main_screen_temperature_value, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_temperature_value, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_temperature_value
	static lv_style_t style_main_screen_temperature_value_main;
	lv_style_reset(&style_main_screen_temperature_value_main);
	lv_style_init(&style_main_screen_temperature_value_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_temperature_value_main
	lv_style_set_radius(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_letter_space(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_temperature_value_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_temperature_value, LV_LABEL_PART_MAIN, &style_main_screen_temperature_value_main);
	lv_obj_set_pos(ui->main_screen_temperature_value, 26, 175);
	lv_obj_set_size(ui->main_screen_temperature_value, 80, 0);

	//Write codes main_screen_humidity_value
	ui->main_screen_humidity_value = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_humidity_value, "");
	lv_label_set_long_mode(ui->main_screen_humidity_value, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_humidity_value, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_humidity_value
	static lv_style_t style_main_screen_humidity_value_main;
	lv_style_reset(&style_main_screen_humidity_value_main);
	lv_style_init(&style_main_screen_humidity_value_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_humidity_value_main
	lv_style_set_radius(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_letter_space(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_humidity_value_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_humidity_value, LV_LABEL_PART_MAIN, &style_main_screen_humidity_value_main);
	lv_obj_set_pos(ui->main_screen_humidity_value, 142, 175);
	lv_obj_set_size(ui->main_screen_humidity_value, 80, 0);

	//Write codes main_screen_illumination_value
	ui->main_screen_illumination_value = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_illumination_value, "");
	lv_label_set_long_mode(ui->main_screen_illumination_value, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_illumination_value, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_illumination_value
	static lv_style_t style_main_screen_illumination_value_main;
	lv_style_reset(&style_main_screen_illumination_value_main);
	lv_style_init(&style_main_screen_illumination_value_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_illumination_value_main
	lv_style_set_radius(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_letter_space(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_illumination_value_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_illumination_value, LV_LABEL_PART_MAIN, &style_main_screen_illumination_value_main);
	lv_obj_set_pos(ui->main_screen_illumination_value, 258, 170);
	lv_obj_set_size(ui->main_screen_illumination_value, 80, 0);

	//Init events for screen
	events_init_main_screen(ui);
}
