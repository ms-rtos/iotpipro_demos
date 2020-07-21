/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: main.c TouchGFX application main.
 *
 * Author: Jiao.jinxing <jiaojixing@acoinfo.com>
 *
 */

#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

#include <ms_rtos.h>

#include "app_touchgfx.h"

using namespace touchgfx;

#define CANVAS_BUFFER_SIZE (14000)
static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

int main(int argc, char **argv)
{
    MX_TouchGFX_Init();

    /**
     * IMPORTANT NOTICE!
     *
     * The GUI task stack size might need to be increased if creating a new application.
     * The current value of 950 in this template is enough for the examples distributed with
     * TouchGFX, but is often insufficient for larger applications.
     * For reference, the touchgfx_2014 demo uses a stacksize of 2000.
     * If you experience inexplicable hard faults with your custom application, try increasing the
     * stack size.
     */

    // Setup the CanvasWidgetRenderer. ONLY needed if you use CanvasWidgets
    // in your application. The CANVAS_BUFFER_SIZE can be adjusted to match
    // your needs in performance vs. RAM usage. Read more on this in the
    // TouchGFX Manual.
    CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    while (MS_TRUE) {
        MX_TouchGFX_Process();
    }

    return 0;
}
