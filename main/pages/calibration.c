#pragma once

#include "lvgl.h"
#include "esp_log.h"
#include "app.h"

#include "lv_tc_screen.h"

#define TAG "Calibration"

struct calibration_page
{
  /* data */
  lv_fragment_t base;
  const char *name;
};

static void init_page(lv_fragment_t *self, void *args)
{
  ((struct calibration_page *)self)->name = args;
}

static void on_accept(lv_event_t *event)
{
  ESP_LOGI(TAG, "Accept clicked");
  // create_demo();
}

static lv_obj_t *create_page(lv_fragment_t *self, lv_obj_t *parent)
{
  lv_obj_t *tCScreen = lv_tc_screen_create();
  // full_size(tCScreen);

  lv_obj_add_event_cb(tCScreen, on_accept, LV_EVENT_READY, NULL);
  lv_disp_load_scr(tCScreen);
  lv_tc_screen_start(tCScreen);

  return tCScreen;
}

static const lv_fragment_class_t calibration_cls = {
    .constructor_cb = init_page,
    .create_obj_cb = create_page,
    .instance_size = sizeof(struct calibration_page)};

void calibration_show(void)
{
  lv_fragment_t *page = lv_fragment_create(&calibration_cls, "Fragment");
  lv_fragment_manager_replace(manager, page, &root);
}