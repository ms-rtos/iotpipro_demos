/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: ms_touchgfx_configuration.cpp TouchGFX configuration.
 *
 * Author: Jiao.jinxing <jiaojixing@acoinfo.com>
 *
 */

#include <ms_rtos.h>

#include <texts/TypedTextDatabase.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <BitmapDatabase.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <platform/driver/lcd/LCD24bpp.hpp>
#include <platform/driver/lcd/LCD32bpp.hpp>
#include <ms_touchgfx_dma.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <ms_touchgfx_hal.hpp>
#include <ms_touchgfx_touch.hpp>

extern "C" void touchgfx_init();
extern "C" void touchgfx_taskEntry();

using namespace touchgfx;

static TouchGFXHAL *ms_tgfx_hal;

int ms_tgfx_fb_fd;
ms_fb_var_screeninfo_t ms_tgfx_fb_var_info;
ms_fb_fix_screeninfo_t ms_tgfx_fb_fix_info;

void touchgfx_init()
{
    MsTouchController *tc = new MsTouchController();
    ApplicationFontProvider *fontProvider = new ApplicationFontProvider();
    Texts *texts = new Texts();
    LCD *display;
    DMA_Interface *dma;

    ms_tgfx_fb_fd = ms_io_open("/dev/fb0", O_RDWR, 0666);
    if (ms_tgfx_fb_fd < 0) {
        ms_printf("Failed to open /dev/fb0 device!\n");
        abort();
    }

    if (ms_io_ioctl(ms_tgfx_fb_fd, MS_FB_CMD_GET_VSCREENINFO, &ms_tgfx_fb_var_info) < 0) {
        ms_printf("Failed to get /dev/fb0 variable screen info!\n");
        abort();
    }

    if (ms_io_ioctl(ms_tgfx_fb_fd, MS_FB_CMD_GET_FSCREENINFO, &ms_tgfx_fb_fix_info) < 0) {
        ms_printf("Failed to get /dev/fb0 fix screen info!\n");
        abort();
    }

    if (ms_tgfx_fb_var_info.bits_per_pixel == 16) {
        display = new LCD16bpp();
    } else {
        display = new LCD32bpp();
    }

    if ((ms_tgfx_fb_fix_info.capability & MS_FB_BLIT_OP_COPY) ||
        (ms_tgfx_fb_fix_info.capability & MS_FB_BLIT_OP_FILL)) {
        dma = new NoDMA();
    } else {
        dma = new NoDMA();
    }

    ms_tgfx_hal = new TouchGFXHAL(*dma, *display, *tc, ms_tgfx_fb_var_info.xres, ms_tgfx_fb_var_info.yres);

    Bitmap::registerBitmapDatabase(BitmapDatabase::getInstance(), BitmapDatabase::getInstanceSize());

    TypedText::registerTexts(texts);

    Texts::setLanguage(0);

    FontManager::setFontProvider(fontProvider);

    FrontendHeap& heap = FrontendHeap::getInstance();
    (void)heap; // we need to obtain the reference above to initialize the frontend heap.

    ms_tgfx_hal->initialize();
}

void touchgfx_taskEntry()
{
    /*
     * Main event loop. Will wait for VSYNC signal, and then process next frame. Call
     * this function from your GUI task.
     *
     * Note This function never returns
     */
    ms_tgfx_hal->taskEntry();
}

extern "C" uint32_t CRC_Lock(void)
{
    return (uint32_t)CRC_Lock;
}

extern "C" _PTR memcpy(_PTR dest, const _PTR src, size_t len)
{
    ms_arch_memcpy(dest, src, len);
    return dest;
}
