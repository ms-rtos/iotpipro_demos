/**
  ******************************************************************************
  * File Name          : app_touchgfx.h
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef APP_TOUCHGFX_H
#define APP_TOUCHGFX_H

#ifdef __cplusplus
extern "C" {
#endif

void MX_TouchGFX_Init(void);
void MX_TouchGFX_Process(void);
void TouchGFX_Task(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* APP_TOUCHGFX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
