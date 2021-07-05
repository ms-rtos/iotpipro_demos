#*********************************************************************************************************
#
#                                 北京翼辉信息技术有限公司
#
#                                   微型安全实时操作系统
#
#                                       MS-RTOS(TM)
#
#                               Copyright All Rights Reserved
#
#--------------文件信息--------------------------------------------------------------------------------
#
# 文   件   名: demo_lvgl_sddc.mk
#
# 创   建   人: IoT Studio
#
# 文件创建日期: 2021 年 06 月 21 日
#
# 描        述: 本文件由 IoT Studio 生成，用于配置 Makefile 功能，请勿手动修改
#*********************************************************************************************************

#*********************************************************************************************************
# Clear setting
#*********************************************************************************************************
include $(CLEAR_VARS_MK)

#*********************************************************************************************************
# Target
#*********************************************************************************************************
LOCAL_TARGET_NAME := demo_lvgl_sddc

#*********************************************************************************************************
# Source list
#*********************************************************************************************************
LOCAL_SRCS :=  \
src/custom/custom.c \
src/demo_lvgl_sddc.c \
src/generated/events_init.c \
src/generated/guider_fonts/lv_font_montserratMedium_12.c \
src/generated/guider_fonts/lv_font_montserratMedium_16.c \
src/generated/guider_fonts/lv_font_montserratMedium_24.c \
src/generated/guider_fonts/lv_font_simsun_12.c \
src/generated/guider_fonts/lv_font_simsun_24.c \
src/generated/guider_fonts/lv_font_simsun_26.c \
src/generated/gui_guider.c \
src/generated/images/_background_alpha_480x272.c \
src/generated/images/_bg_tab_page_alpha_100x135.c \
src/generated/images/_button_home_alpha_32x31.c \
src/generated/images/_button_off_alpha_80x25.c \
src/generated/images/_button_off_alpha_88x32.c \
src/generated/images/_button_on_alpha_80x25.c \
src/generated/images/_button_on_alpha_88x32.c \
src/generated/images/_icon_humidity_alpha_40x40.c \
src/generated/images/_icon_humidity_alpha_40x43.c \
src/generated/images/_icon_lamp_alpha_40x40.c \
src/generated/images/_icon_lamp_alpha_40x43.c \
src/generated/images/_icon_led_dark_alpha_60x70.c \
src/generated/images/_icon_led_dark_alpha_73x79.c \
src/generated/images/_icon_led_light_alpha_60x70.c \
src/generated/images/_icon_light_alpha_40x40.c \
src/generated/images/_icon_light_alpha_40x43.c \
src/generated/images/_icon_temperature_alpha_40x40.c \
src/generated/images/_icon_temperature_alpha_40x43.c \
src/generated/images/_msrtos_logo_alpha_100x17.c \
src/generated/images/_msrtos_logo_alpha_100x18.c \
src/generated/setup_scr_light_control_screen.c \
src/generated/setup_scr_main_screen.c \
src/system/system.c

#*********************************************************************************************************
# Header file search path (eg. LOCAL_INC_PATH := -I"Your header files search path")
#*********************************************************************************************************
LOCAL_INC_PATH :=  \
-I"$(MSRTOS_BASE_PATH)/littlevgl/src" \
-I"$(MSRTOS_BASE_PATH)/littlevgl/src/lvgl/src" \
-I"$(MSRTOS_BASE_PATH)/littlevgl/src/lvgl/src/lv_font" \
-I"$(MSRTOS_BASE_PATH)/libsddc/src" \
-I"$(MSRTOS_BASE_PATH)/libmsdriver/src" \
-I"$(MSRTOS_BASE_PATH)/cjson/src/cJSON" \
-I"./src"

#*********************************************************************************************************
# Pre-defined macro (eg. -DYOUR_MARCO=1)
#*********************************************************************************************************
LOCAL_DSYMBOL := 

#*********************************************************************************************************
# Compiler flags
#*********************************************************************************************************
LOCAL_CFLAGS := 
LOCAL_CXXFLAGS := 
LOCAL_LINKFLAGS := 

#*********************************************************************************************************
# Depend library (eg. LOCAL_DEPEND_LIB := -la LOCAL_DEPEND_LIB_PATH := -L"Your library search path")
#*********************************************************************************************************
LOCAL_DEPEND_LIB :=  \
-llittlevgl \
-lcjson \
-lmsdriver \
-lsddc \
-lmbedtls \
-lmbedcrypto \
-llittlevgl

LOCAL_DEPEND_LIB_PATH :=  \
-L"$(MSRTOS_BASE_PATH)/littlevgl/$(OUTDIR)" \
-L"$(MSRTOS_BASE_PATH)/cjson/$(OUTDIR)" \
-L"$(MSRTOS_BASE_PATH)/libmsdriver/$(OUTDIR)" \
-L"$(MSRTOS_BASE_PATH)/libsddc/$(OUTDIR)" \
-L"$(MSRTOS_BASE_PATH)/mbedtls/$(OUTDIR)"

#*********************************************************************************************************
# C++ config
#*********************************************************************************************************
LOCAL_USE_CXX        := no
LOCAL_USE_CXX_EXCEPT := no

#*********************************************************************************************************
# Code coverage config
#*********************************************************************************************************
LOCAL_USE_GCOV := no

#*********************************************************************************************************
# Stack check config
#*********************************************************************************************************
LOCAL_USE_STACK_CHECK := no

#*********************************************************************************************************
# Use short command for link and ar
#*********************************************************************************************************
LOCAL_USE_SHORT_CMD := no

#*********************************************************************************************************
# User link command
#*********************************************************************************************************
LOCAL_PRE_LINK_CMD := 
LOCAL_POST_LINK_CMD := 
LOCAL_PRE_STRIP_CMD := 
LOCAL_POST_STRIP_CMD := 

#*********************************************************************************************************
# Depend target
#*********************************************************************************************************
LOCAL_DEPEND_TARGET :=

include $(APPLICATION_MK)

#*********************************************************************************************************
# End
#*********************************************************************************************************
