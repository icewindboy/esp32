idf_component_register(SRCS "esp_nvs_tc.c"
                            "lv_tc_screen.c"
                            "lv_tc.c"
                            "img/lv_tc_indicator_img.c"
                INCLUDE_DIRS "."
                PRIV_REQUIRES lvgl nvs_flash)