#include "lvgl.h"

void apply_theme(void)
{
  lv_theme_t *new_theme = lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_RED), lv_palette_lighten(LV_PALETTE_ORANGE, 2), true, LV_FONT_DEFAULT);

  lv_disp_set_theme(NULL, new_theme);
}