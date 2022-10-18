#pragma once
#include "lvgl.h"

typedef void (*readCb)(lv_indev_drv_t *indevDrv, lv_indev_data_t *data);
typedef void (*flush_cb)(struct _lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

lv_disp_draw_buf_t disp_buf;
lv_fragment_manager_t *manager;
lv_obj_t *root ;

void app_init(flush_cb disp_driver_flush, readCb touch_read);
void drawbuf_free();
void full_size(lv_obj_t *obj);
void manager_del_cb(lv_event_t *e)