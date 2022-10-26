#pragma once

#include "lvgl/lvgl.h"

#include "esp_system.h"
#include "esp_freertos_hooks.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_blufi.h"


#define BLUFI_EXAMPLE_TAG "BLUFI_EXAMPLE"
#define BLUFI_INFO(fmt, ...)   ESP_LOGI(BLUFI_EXAMPLE_TAG, fmt, ##__VA_ARGS__)
#define BLUFI_ERROR(fmt, ...)  ESP_LOGE(BLUFI_EXAMPLE_TAG, fmt, ##__VA_ARGS__)
#define ADJUST_TIME 10 //校准次数

void blufi_dh_negotiate_data_handler(uint8_t *data, int len, uint8_t **output_data, int *output_len, bool *need_free);
int blufi_aes_encrypt(uint8_t iv8, uint8_t *crypt_data, int crypt_len);
int blufi_aes_decrypt(uint8_t iv8, uint8_t *crypt_data, int crypt_len);
uint16_t blufi_crc_checksum(uint8_t iv8, uint8_t *data, int len);

int blufi_security_init(void);
void blufi_security_deinit(void);
int esp_blufi_gap_register_callback(void);
esp_err_t esp_blufi_host_init(void);
esp_err_t esp_blufi_host_and_cb_init(esp_blufi_callbacks_t *callbacks);

void start_blufi(void);
// typedef struct
// {

//   lv_obj_t *cont;
//   lv_obj_t *adjBtn[4];
//   lv_obj_t *adjBtnLabel[4];
//   lv_obj_t *adjCntLabel[4];
//   lv_obj_t *adjLabel;
// } adjObj_TypeDef;

// typedef struct
// {

//   int16_t adj_coord_x[4][ADJUST_TIME];
//   int16_t adj_coord_y[4][ADJUST_TIME];
//   int32_t adj_sum_x[4];
//   int32_t adj_sum_y[4];
//   bool fullCnt[4];
// } adjBuff_TypeDef;

// static void TP_Adjust_Create(void);
