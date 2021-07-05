/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#include "gui_guider.h"

void events_init(lv_ui *ui);
void events_init_main_screen(lv_ui *ui);
void events_init_light_control_screen(lv_ui *ui);
void memory_print(void);
void light_state_init(void);
#endif /* EVENT_CB_H_ */
