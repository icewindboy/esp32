#include "inc/ui.h"
#include <stdio.h>

lv_style_t flex_style;
lv_style_t item_wrap_panel_style;
lv_style_t item_upper_btn_style;
lv_style_t item_upper_label_style;
lv_style_t item_text_below_style;

static void init_style(void)
{
  // flex style
  lv_style_init(&flex_style);
  lv_style_set_flex_flow(&flex_style, LV_FLEX_FLOW_ROW_WRAP);
  lv_style_set_flex_main_place(&flex_style, LV_FLEX_ALIGN_START);
  lv_style_set_layout(&flex_style, LV_LAYOUT_FLEX);

  // the item panel style
  lv_style_init(&item_wrap_panel_style);
  lv_style_set_bg_opa(&item_wrap_panel_style, 0);
  lv_style_set_border_width(&item_wrap_panel_style, 1);
  lv_style_set_size(&item_wrap_panel_style, 64);

  // the upper btn style
  lv_style_init(&item_upper_btn_style);
  lv_style_set_width(&item_upper_btn_style, 36);
  lv_style_set_height(&item_upper_btn_style, 36);
  lv_style_set_align(&item_upper_btn_style, LV_ALIGN_TOP_MID);
  lv_style_set_y(&item_upper_btn_style, -10);
  // the upper label style
  lv_style_init(&item_upper_label_style);
  lv_style_set_text_font(&item_upper_label_style, &lv_font_montserrat_22);
  lv_style_set_align(&item_upper_label_style, LV_ALIGN_CENTER);

  // the below text style
  lv_style_init(&item_text_below_style);
  lv_style_set_text_font(&item_text_below_style, &lv_font_montserrat_12);
  lv_style_set_align(&item_text_below_style, LV_ALIGN_BOTTOM_MID);
  lv_style_set_y(&item_text_below_style, 12);

}

static void on_click(lv_event_t *e)
{
  printf("Press on img");
}

static lv_obj_t *desk_item(lv_obj_t *parent, const char *icon, const char *text)
{
  // wrapper
  lv_obj_t *btn_wrapper = lv_obj_create(parent);
  lv_obj_add_style(btn_wrapper, &item_wrap_panel_style, 0);
  lv_obj_set_scrollbar_mode(btn_wrapper, LV_SCROLLBAR_MODE_OFF);

  // upper image + label
  lv_obj_t *upper_button = lv_btn_create(btn_wrapper);
  lv_obj_add_style(upper_button, &item_upper_btn_style, 0);
  lv_obj_add_event_cb(upper_button, on_click, LV_EVENT_CLICKED, NULL);

  lv_obj_t *upper_label = lv_label_create(upper_button);
  lv_label_set_text(upper_label, icon);
  lv_obj_add_style(upper_label, &item_upper_label_style, 0);

  // bottom text
  lv_obj_t *below_txt = lv_label_create(btn_wrapper);
  lv_label_set_text(below_txt, text);
  lv_obj_add_style(below_txt, &item_text_below_style, 0);
  return btn_wrapper;
}

void home_init(void)
{
  home = lv_obj_create(NULL);

  init_style();
  // printf("the screen size is width:%d,height %d\n", lv_obj_get_width(home), lv_obj_get_height(home));
  lv_obj_t *panel = lv_obj_create(home);
  lv_obj_set_size(panel, 240, 200);
  lv_obj_set_style_border_width(panel, 0, 0);
  lv_obj_set_align(panel, LV_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(panel, 0, 0);

  lv_obj_add_style(panel, &flex_style, 0);

  desk_item(panel, LV_SYMBOL_WIFI, "WIFI");
  desk_item(panel, LV_SYMBOL_BELL, "Clock");

  lv_disp_load_scr(home);
}
