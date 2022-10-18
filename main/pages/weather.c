#include "lvgl.h"
#include "esp_log.h"
#include "app.h"

#define TAG "Weather"

struct weather_page
{
  /* data */
  lv_fragment_t base;
  const char *name;
};

static void init_page(lv_fragment_t *self, void *args)
{
  ((struct weather_page *)self)->name = args;
}

static lv_obj_t *create_page(lv_fragment_t *self, lv_obj_t *parent)
{
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_obj_set_style_bg_opa(label, LV_OPA_COVER, 0);
  
  lv_label_set_text_fmt(label, "Hello, %s!", ((struct weather_page *)self)->name);
  return label;
}

static const lv_fragment_class_t weather_cls = {
    .constructor_cb = init_page,
    .create_obj_cb = create_page,
    .instance_size = sizeof(struct weather_page)};

void weather_show(void)
{
  lv_fragment_t *page = lv_fragment_create(&weather_cls, "Fragment");
  lv_fragment_manager_push(manager,page,NULL);
  // lv_fragment_manager_replace(manager, page, &root);
}