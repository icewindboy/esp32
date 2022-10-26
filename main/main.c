/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

/****************************************************************************
 * This is a demo for bluetooth config wifi connection to ap. You can config ESP32 to connect a softap
 * or config ESP32 as a softap to be connected by other device. APP can be downloaded from github
 * android source code: https://github.com/EspressifApp/EspBlufi
 * iOS source code: https://github.com/EspressifApp/EspBlufiForiOS
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#include "lvgl.h"
#include "lvgl_helpers.h"

#include "lvgl_touch_calibration/lv_tc.h"
#include "lvgl_touch_calibration/esp_nvs_tc.h"
#include "lvgl_touch_calibration/lv_tc_screen.h"

#include "examples/lv_examples.h"
#include "demos/lv_demos.h"
#include "sndbx/pages/sndbx_pges.h"

#include "app/app.h"
#include "pages/calibration.h"
#include "pages/weather.h"
#include "pages/gadget/ui.h"
#include "blufi/blufi.h"
#include "mqtt/mqtt.h"

#define TAG "APP"
#define LV_TICK_PERIOD_MS 1

static void guiTask(void *pvParameter);
static void create_demo(void);
static void calibration_run(void);
static void on_long_pressed(lv_event_t *event);
static void on_pressed_released(lv_event_t *event);
SemaphoreHandle_t xGuiSemaphore;

void app_main(void)
{
    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 0, NULL, 1);
}

static void guiTask(void *pvParameter)
{
    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    app_init(disp_driver_flush, touch_driver_read);
    if (!esp_nvs_tc_coeff_init())
    {
        // start_blufi();
        // mqtt_start();
        // ui_init();
    }
    else
    {
        // weather_show();
        // calibration_show();
        start_blufi();
        mqtt_start();
        ui_init();
        // sndbx_pge_lv_examples_test();
    }

    while (1)
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }

    /* A task should NEVER return */
    drawbuf_free();
    vTaskDelete(NULL);
}

static uint32_t long_pressed = 0;
void on_long_pressed(lv_event_t *event)
{
    long_pressed++;
    if (long_pressed > 30)
    {
        calibration_run();
    }
    ESP_LOGI(TAG, "long long pressed %d!", long_pressed);
}

void on_pressed_released(lv_event_t *event)
{
    long_pressed = 0;
}

void create_demo(void)
{
    // lv_example_win_1();
    // lv_example_get_started_1();
    // lv_demo_music();
    lv_demo_widgets();
    // lv_demo_keypad_encoder();
    // lv_demo_benchmark_set_max_speed(false);
    // lv_obj_t *panel = example_msg_3();
    // lv_obj_add_event_cb(panel, on_long_pressed, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
    // lv_obj_add_event_cb(panel, on_pressed_released, LV_EVENT_RELEASED, NULL);
    // ESP_LOGI(TAG, "MSG1:CREATED_DEMO");
    // calibration_show();
}