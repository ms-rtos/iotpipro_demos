/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "../system/system.h"

void events_init(lv_ui *ui)
{
    setup_scr_light_control_screen(&guider_ui);
}

static void main_screen_light_iconevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		lv_scr_load(guider_ui.light_control_screen);
		light_state_init();
	}
		break;
	default:
		break;
	}
}

void events_init_main_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->main_screen_light_icon, main_screen_light_iconevent_handler);
}

static void light_control_screen_home_iconevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		lv_scr_load(guider_ui.main_screen);
	}
		break;
	default:
		break;
	}
}

void light_state_init(void)
{
    lv_event_send(guider_ui.light_control_screen_led1_button, LV_EVENT_INSERT, NULL);
    lv_event_send(guider_ui.light_control_screen_led2_button, LV_EVENT_INSERT, NULL);
    lv_event_send(guider_ui.light_control_screen_led3_button, LV_EVENT_INSERT, NULL);
}

static void light_control_screen_led1_buttonevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
        lv_obj_set_hidden(guider_ui.light_control_screen_led1_light, leds_state[0]);
        system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 0, !leds_state[0]);
        system_sddc_notify(SYSTEM_NOTIFY_TYPE_LED, 0, !leds_state[0]);
	}
		break;

	case LV_EVENT_INSERT:
	{
        lv_imgbtn_set_state(guider_ui.light_control_screen_led1_button, leds_state[0] ? LV_BTN_STATE_CHECKED_RELEASED : LV_BTN_STATE_RELEASED);
        lv_obj_set_hidden(guider_ui.light_control_screen_led1_light, !leds_state[0]);
	}
	    break;
	default:
		break;
	}
}

static void light_control_screen_led2_buttonevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
    case LV_EVENT_PRESSED:
    {
        lv_obj_set_hidden(guider_ui.light_control_screen_led2_light, leds_state[1]);
        system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 1, !leds_state[1]);
        system_sddc_notify(SYSTEM_NOTIFY_TYPE_LED, 1, !leds_state[1]);
    }
        break;
    case LV_EVENT_INSERT:
    {
        lv_imgbtn_set_state(guider_ui.light_control_screen_led2_button, leds_state[1] ? LV_BTN_STATE_CHECKED_RELEASED : LV_BTN_STATE_RELEASED);
        lv_obj_set_hidden(guider_ui.light_control_screen_led2_light, !leds_state[1]);
    }
		break;
	default:
		break;
	}
}

static void light_control_screen_led3_buttonevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
    case LV_EVENT_PRESSED:
    {
        lv_obj_set_hidden(guider_ui.light_control_screen_led3_light, leds_state[2]);
        system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 2, !leds_state[2]);
        system_sddc_notify(SYSTEM_NOTIFY_TYPE_LED, 2, !leds_state[2]);
    }
        break;
    case LV_EVENT_INSERT:
    {
        lv_imgbtn_set_state(guider_ui.light_control_screen_led3_button, leds_state[2] ? LV_BTN_STATE_CHECKED_RELEASED : LV_BTN_STATE_RELEASED);
        lv_obj_set_hidden(guider_ui.light_control_screen_led3_light, !leds_state[2]);
    }
		break;
	default:
		break;
	}
}

void events_init_light_control_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->light_control_screen_home_icon, light_control_screen_home_iconevent_handler);
	lv_obj_set_event_cb(ui->light_control_screen_led1_button, light_control_screen_led1_buttonevent_handler);
	lv_obj_set_event_cb(ui->light_control_screen_led2_button, light_control_screen_led2_buttonevent_handler);
	lv_obj_set_event_cb(ui->light_control_screen_led3_button, light_control_screen_led3_buttonevent_handler);
}
