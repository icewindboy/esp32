#include "lvgl.h"
#include "esp_log.h"
#include "../app/theme.h"
#include "../app/app.h"

#define TAG "Weather"

struct weather_page
{
  /* data */
  lv_fragment_t base;
  const char *name;
};

static lv_monkey_t *monkey;

void lv_example_monkey_1(void)
{
  /*Create pointer monkey test*/
  lv_monkey_config_t config;
  lv_monkey_config_init(&config);
  config.type = LV_INDEV_TYPE_POINTER;
  config.period_range.min = 10;
  config.period_range.max = 100;

  monkey = lv_monkey_create(&config);

  /*Start monkey test*/
  lv_monkey_set_enable(monkey, true);
}

static void init_page(lv_fragment_t *self, void *args)
{
  ((struct weather_page *)self)->name = args;
}

static void on_click(lv_event_t *e)
{
  ESP_LOGI(TAG, "apply theme called");
  // lv_monkey_del(monkey);
}

static lv_obj_t *create_page(lv_fragment_t *self, lv_obj_t *parent)
{
  apply_theme();
  lv_obj_t *cont = lv_scr_act();

  full_size(cont);
  // lv_obj_set_style_bg_color(cont, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
  lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);

  lv_obj_t *label = lv_label_create(cont);
  lv_obj_set_style_bg_opa(label, LV_OPA_TRANSP, 0);
  lv_label_set_text_fmt(label, "Hello, %s!", ((struct weather_page *)self)->name);
  lv_obj_set_flex_grow(label, 1);

  lv_obj_t *btn = lv_btn_create(cont);
  lv_obj_add_event_cb(btn, on_click, LV_EVENT_CLICKED, NULL);
  lv_obj_set_flex_grow(btn, 3);

  label = lv_label_create(btn);
  lv_label_set_text_static(label, "Change Theme");
  lv_obj_center(label);

  // lv_example_monkey_1();
  return cont;
}

static const lv_fragment_class_t weather_cls = {
    .constructor_cb = init_page,
    .create_obj_cb = create_page,
    .instance_size = sizeof(struct weather_page)};

void weather_show(void)
{
  lv_fragment_t *page = lv_fragment_create(&weather_cls, "Fragment");
  lv_fragment_manager_push(manager, page, NULL);
  // lv_fragment_manager_replace(manager, page, &root);
}