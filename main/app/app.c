#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_system.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_heap_caps.h"

#include "lvgl.h"
#include "lvgl_helpers.h"
#include "lvgl_touch_calibration/lv_tc.h"
#include "lvgl_touch_calibration/esp_nvs_tc.h"
#include "lvgl_touch_calibration/lv_tc_screen.h"

#include "app.h"
#define LV_TICK_PERIOD_MS 1

/* data */
static lv_color_t *draw_buf1;
static lv_color_t *draw_buf2;

static void init_display(flush_cb disp_driver_flush);
static void init_indev(readCb touch_read);
static void init_periodic_timer();
static void init_root();

void lv_tick_task(void *arg);

void app_init(flush_cb driver_flush, readCb touch_read)
{
  esp_err_t ret;
  ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  lv_init();
  lvgl_driver_init();

  init_display(driver_flush);
  init_indev(touch_read);

  init_periodic_timer();
  init_root();
}

void init_root()
{
  manager = lv_fragment_manager_create(NULL);
}

void manager_del_cb(lv_event_t *e)
{
  lv_fragment_manager_t *manager = (lv_fragment_manager_t *)lv_event_get_user_data(e);
  lv_fragment_manager_del(manager);
}

void init_display(flush_cb disp_driver_flush)
{

  draw_buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
  assert(draw_buf1 != NULL);
  draw_buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
  assert(draw_buf2 != NULL);

  uint32_t size_in_px = DISP_BUF_SIZE;

  lv_disp_draw_buf_init(&disp_buf, draw_buf1, draw_buf2, size_in_px);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = disp_driver_flush;
  disp_drv.hor_res = LV_HOR_RES_MAX;
  disp_drv.ver_res = LV_VER_RES_MAX;

  disp_drv.draw_buf = &disp_buf;
  lv_disp_drv_register(&disp_drv);
}

void init_indev(readCb touch_read)
{
  /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
  static lv_indev_drv_t indev_drv;

  lv_tc_indev_drv_init(&indev_drv, touch_read);
  lv_indev_drv_register(&indev_drv);
  lv_tc_register_coeff_save_cb(esp_nvs_tc_coeff_save_cb);
#endif
}

void init_periodic_timer()
{
  // esp_register_freertos_tick_hook((void *)lv_tick_task);
  /* Create and start a periodic timer interrupt to call lv_tick_inc */
  const esp_timer_create_args_t periodic_timer_args = {
      .callback = &lv_tick_task,
      .name = "periodic_gui"};
  esp_timer_handle_t periodic_timer;
  ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
}

void drawbuf_free()
{
  free(draw_buf1);
  free(draw_buf2);
  if (manager)
    lv_fragment_manager_del(manager);
}

void lv_tick_task(void *arg)
{
  (void)arg;
  lv_tick_inc(LV_TICK_PERIOD_MS);
}

void full_size(lv_obj_t *obj)
{
  lv_obj_set_size(obj, LV_HOR_RES_MAX, LV_VER_RES_MAX);
}

lv_obj_t *get_screen()
{
  lv_obj_t *scr = lv_scr_act();
  // lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);

  return scr;
}