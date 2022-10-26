#include "lvgl.h"
typedef lv_obj_t (*page)(void* args);

typedef struct router
{
  /* data */
  char name[32];
  page start;
};
