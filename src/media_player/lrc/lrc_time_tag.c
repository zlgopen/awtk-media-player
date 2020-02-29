/**
 * File:   lrc_time_tag.c
 * Author: AWTK Develop Team
 * Brief:  lrc time tag
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ===============================================================
 * 2020-02-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "media_player/lrc/lrc_time_tag.h"

lrc_time_tag_list_t* lrc_time_tag_list_create(void) {
  lrc_time_tag_list_t* list = TKMEM_ZALLOC(lrc_time_tag_list_t);
  return_value_if_fail(list != NULL, NULL);

  return list;
}

static ret_t lrc_time_tag_list_expand(lrc_time_tag_list_t* list) {
  uint32_t capacity = 0;
  lrc_time_tag_t* items = NULL;

  return_value_if_fail(list != NULL, RET_BAD_PARAMS);
  if (list->size < list->capacity) {
    return RET_OK;
  }

  capacity = list->size + 20;
  items = TKMEM_REALLOC(list->items, sizeof(lrc_time_tag_t) * capacity);

  if (items != NULL) {
    list->items = items;
    list->capacity = capacity;

    return RET_OK;
  } else {
    return RET_OOM;
  }
}

ret_t lrc_time_tag_list_append(lrc_time_tag_list_t* list, uint32_t timestamp) {
  lrc_time_tag_t* tag = NULL;

  return_value_if_fail(list != NULL, RET_BAD_PARAMS);
  return_value_if_fail(lrc_time_tag_list_expand(list) == RET_OK, RET_OOM);

  tag = list->items + list->size;

  tag->timestamp = timestamp;
  tag->text = NULL;
  list->size++;

  return RET_OK;
}

ret_t lrc_time_tag_list_destroy(lrc_time_tag_list_t* list) {
  return_value_if_fail(list != NULL, RET_BAD_PARAMS);

  TKMEM_FREE(list->items);
  TKMEM_FREE(list);

  return RET_OK;
}

ret_t lrc_time_tag_list_set_text(lrc_time_tag_list_t* list, const char* text) {
  uint32_t i = 0;
  return_value_if_fail(list != NULL && text != NULL, RET_BAD_PARAMS);

  for (i = list->cursor; i < list->size; i++) {
    lrc_time_tag_t* iter = list->items + i;
    iter->text = text;
  }
  list->cursor = list->size;

  return RET_OK;
}

static int lrc_time_tag_cmp(const void* a, const void* b) {
  lrc_time_tag_t* t1 = (lrc_time_tag_t*)a;
  lrc_time_tag_t* t2 = (lrc_time_tag_t*)b;

  return t1->timestamp - t2->timestamp;
}

ret_t lrc_time_tag_list_sort(lrc_time_tag_list_t* list) {
  return_value_if_fail(list != NULL, RET_BAD_PARAMS);

  qsort(list->items, list->size, sizeof(lrc_time_tag_t), lrc_time_tag_cmp);

  return RET_OK;
}

const char* lrc_time_tag_list_find(lrc_time_tag_list_t* list, uint32_t timestamp) {
  uint32_t i = 0;
  return_value_if_fail(list != NULL, NULL);
  for (i = 0; i < list->size; i++) {
    lrc_time_tag_t* iter = list->items + i;

    if (iter->timestamp == timestamp) {
      return iter->text;
    } else if (iter->timestamp > timestamp) {
      if (i > 0) {
        iter = list->items + i - 1;
        return iter->text;
      } else {
        return NULL;
      }
    } else if ((i + 1) == list->size) {
      return iter->text;
    }
  }

  return NULL;
}
