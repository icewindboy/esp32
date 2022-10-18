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

#include "app.h"
#include "calibration.h"

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

static void onCalibrationAccept(lv_event_t *event)
{
    ESP_LOGI(TAG, "Accept clicked");
    create_demo();
}

static void guiTask(void *pvParameter)
{
    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    app_init(disp_driver_flush, touch_driver_read);

#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    if (!esp_nvs_tc_coeff_init())
    {
        calibration_run();
    }
#endif
    create_demo();

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

static lv_obj_t *example_msg_3(void)
{
    lv_obj_t *panel = lv_obj_create(lv_scr_act());
    lv_obj_set_size(panel, LV_HOR_RES_MAX, LV_VER_RES);
    lv_obj_center(panel);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_t *btn;
    lv_obj_t *label;

    /*Current value*/
    label = lv_label_create(panel);
    lv_obj_set_flex_grow(label, 2);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(label, "?");

    /*Down button*/
    btn = lv_btn_create(panel);
    lv_obj_set_flex_grow(btn, 1);

    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_RIGHT);
    lv_obj_center(label);

    /*Slider*/
    lv_obj_t *slider = lv_slider_create(panel);
    lv_obj_set_flex_grow(slider, 1);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

    return panel;
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
    // lv_demo_widgets();
    // lv_demo_keypad_encoder();
    // lv_demo_benchmark_set_max_speed(false);
    // lv_obj_t *panel = example_msg_3();
    // lv_obj_add_event_cb(panel, on_long_pressed, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
    // lv_obj_add_event_cb(panel, on_pressed_released, LV_EVENT_RELEASED, NULL);
    // ESP_LOGI(TAG, "MSG1:CREATED_DEMO");
    calibration_show();
}

void calibration_run()
{
    lv_obj_t *tCScreen = lv_tc_screen_create();
    lv_obj_add_event_cb(tCScreen, onCalibrationAccept, LV_EVENT_READY, NULL);

    lv_disp_load_scr(tCScreen);

    lv_tc_screen_start(tCScreen);
}
