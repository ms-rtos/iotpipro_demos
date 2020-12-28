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
# 文   件   名: demo_gui.mk
#
# 创   建   人: IoT Studio
#
# 文件创建日期: 2020 年 07 月 14 日
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
LOCAL_TARGET_NAME := demo_gui

#*********************************************************************************************************
# Source list
#*********************************************************************************************************
LOCAL_SRCS :=  \
src/app_touchgfx.c \
src/main.cpp \
src/ms_touchgfx_configuration.cpp \
src/TouchGFX/generated/fonts/src/ApplicationFontProvider.cpp \
src/TouchGFX/generated/fonts/src/CachedFont.cpp \
src/TouchGFX/generated/fonts/src/FontCache.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_14_4bpp_0.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_14_4bpp_10.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_14_4bpp_11.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_14_4bpp_13.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_14_4bpp_14.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_20_4bpp_0.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_20_4bpp_10.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_20_4bpp_12.cpp \
src/TouchGFX/generated/fonts/src/Font_SIMYOU_TTF_20_4bpp_14.cpp \
src/TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.cpp \
src/TouchGFX/generated/fonts/src/Font_verdana_16_4bpp_0.cpp \
src/TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.cpp \
src/TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.cpp \
src/TouchGFX/generated/fonts/src/GeneratedFont.cpp \
src/TouchGFX/generated/fonts/src/Kerning_SIMYOU_TTF_14_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Kerning_SIMYOU_TTF_20_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Kerning_verdana_16_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Table_SIMYOU_TTF_14_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Table_SIMYOU_TTF_20_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Table_verdana_16_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.cpp \
src/TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.cpp \
src/TouchGFX/generated/gui_generated/src/common/FrontendApplicationBase.cpp \
src/TouchGFX/generated/gui_generated/src/lightcontrolscreen_screen/LightControlScreenViewBase.cpp \
src/TouchGFX/generated/gui_generated/src/mainscreen_screen/MainScreenViewBase.cpp \
src/TouchGFX/generated/images/src/BitmapDatabase.cpp \
src/TouchGFX/generated/images/src/light_screen/button_home.cpp \
src/TouchGFX/generated/images/src/light_screen/button_off.cpp \
src/TouchGFX/generated/images/src/light_screen/button_on.cpp \
src/TouchGFX/generated/images/src/light_screen/icon_led_dark.cpp \
src/TouchGFX/generated/images/src/light_screen/icon_led_light.cpp \
src/TouchGFX/generated/images/src/main_screen/background.cpp \
src/TouchGFX/generated/images/src/main_screen/msrtos_logo.cpp \
src/TouchGFX/generated/images/src/main_screen/bg_tab_page.cpp \
src/TouchGFX/generated/images/src/main_screen/icon_humidity.cpp \
src/TouchGFX/generated/images/src/main_screen/icon_lamp.cpp \
src/TouchGFX/generated/images/src/main_screen/icon_light.cpp \
src/TouchGFX/generated/images/src/main_screen/icon_temperature.cpp \
src/TouchGFX/generated/texts/src/LanguageGb.cpp \
src/TouchGFX/generated/texts/src/Texts.cpp \
src/TouchGFX/generated/texts/src/TypedTextDatabase.cpp \
src/TouchGFX/gui/src/common/FrontendApplication.cpp \
src/TouchGFX/gui/src/lightcontrolscreen_screen/LightControlScreenPresenter.cpp \
src/TouchGFX/gui/src/lightcontrolscreen_screen/LightControlScreenView.cpp \
src/TouchGFX/gui/src/mainscreen_screen/MainScreenPresenter.cpp \
src/TouchGFX/gui/src/mainscreen_screen/MainScreenView.cpp \
src/TouchGFX/gui/src/model/Model.cpp \
src/System/System.cpp

#*********************************************************************************************************
# Header file search path (eg. LOCAL_INC_PATH := -I"Your header files search path")
#*********************************************************************************************************
LOCAL_INC_PATH :=  \
-I"$(MSRTOS_BASE_PATH)/st_touchgfx/src/ST/touchgfx/framework/include" \
-I"$(MSRTOS_BASE_PATH)/st_touchgfx/src/porting" \
-I"$(MSRTOS_BASE_PATH)/libmsdriver/src" \
-I"$(MSRTOS_BASE_PATH)/sddc/src" \
-I"$(MSRTOS_BASE_PATH)/cjson/src/cJSON" \
-I"$(MSRTOS_BASE_PATH)/u8g2/src/u8g2/csrc" \
-I"$(MSRTOS_BASE_PATH)/u8g2/src" \
-I"src/TouchGFX/generated" \
-I"src/TouchGFX/generated/gui_generated/include" \
-I"src/TouchGFX/generated/fonts/include" \
-I"src/TouchGFX/generated/images/include" \
-I"src/TouchGFX/generated/texts/include" \
-I"src/TouchGFX/gui/include" \
-I"src/System"

#*********************************************************************************************************
# Pre-defined macro (eg. -DYOUR_MARCO=1)
#*********************************************************************************************************
LOCAL_DSYMBOL := 

#*********************************************************************************************************
# Compiler flags
#*********************************************************************************************************
LOCAL_CFLAGS := 
LOCAL_CXXFLAGS := 

#*********************************************************************************************************
# Depend library (eg. LOCAL_DEPEND_LIB := -la LOCAL_DEPEND_LIB_PATH := -L"Your library search path")
#*********************************************************************************************************
LOCAL_DEPEND_LIB      := -lsddc -lcjson -lu8g2 
LOCAL_DEPEND_LIB_PATH := \
-L"$(MSRTOS_BASE_PATH)/sddc/$(OUTDIR)" \
-L"$(MSRTOS_BASE_PATH)/cJSON/$(OUTDIR)" \
-L"$(MSRTOS_BASE_PATH)/u8g2/$(OUTDIR)" 

ifeq ($(FLOAT_ABI), softfp)
LOCAL_DEPEND_LIB      += -ltouchgfx
else 
LOCAL_DEPEND_LIB      += -ltouchgfx-float-abi-hard
endif

ifeq ($(CPU_TYPE), cortex-m4)
LOCAL_DEPEND_LIB_PATH += -L"$(MSRTOS_BASE_PATH)/st_touchgfx/src/ST/touchgfx/lib/core/cortex_m4f/gcc"
else 
LOCAL_DEPEND_LIB_PATH += -L"$(MSRTOS_BASE_PATH)/st_touchgfx/src/ST/touchgfx/lib/core/cortex_m7/gcc"
endif

LOCAL_DEPEND_LIB      += -ltouchgfx_port
LOCAL_DEPEND_LIB_PATH += -L"$(MSRTOS_BASE_PATH)/st_touchgfx/$(OUTDIR)"

#*********************************************************************************************************
# C++ config
#*********************************************************************************************************
LOCAL_USE_CXX        := yes
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
LOCAL_USE_SHORT_CMD := yes

#*********************************************************************************************************
# User link command
#*********************************************************************************************************
LOCAL_PRE_LINK_CMD   := 
LOCAL_POST_LINK_CMD  := 
LOCAL_PRE_STRIP_CMD  := 
LOCAL_POST_STRIP_CMD := 

#*********************************************************************************************************
# Depend target
#*********************************************************************************************************
LOCAL_DEPEND_TARGET := 

include $(APPLICATION_MK)

#*********************************************************************************************************
# End
#*********************************************************************************************************
