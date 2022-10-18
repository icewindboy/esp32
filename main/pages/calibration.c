#include "lvgl.h"
#include "app.h"

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

static lv_obj_t *create_page(lv_fragment_t *self, lv_obj_t *parent)
{
  lv_obj_t *label = lv_label_create(parent);
  lv_obj_set_style_bg_opa(label, LV_OPA_COVER, 0);

  lv_label_set_text_fmt(label, "Hello, %s!", ((struct calibration_page *)self)->name);
  return label;
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