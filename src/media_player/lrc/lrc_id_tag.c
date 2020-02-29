/**
 * File:   lrc_id_tag.c
 * Author: AWTK Develop Team
 * Brief:  lrc id tag
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
#include "media_player/lrc/lrc_id_tag.h"

lrc_id_tag_list_t* lrc_id_tag_list_create(void) {
  lrc_id_tag_list_t* list = TKMEM_ZALLOC(lrc_id_tag_list_t);
  return_value_if_fail(list != NULL, NULL);

  return list;
}

static ret_t lrc_id_tag_list_expand(lrc_id_tag_list_t* list) {
  uint32_t capacity = 0;
  lrc_id_tag_t* items = NULL;

  return_value_if_fail(list != NULL, RET_BAD_PARAMS);
  if (list->size < list->capacity) {
    return RET_OK;
  }

  capacity = list->size + 5;
  items = TKMEM_REALLOC(list->items, sizeof(lrc_id_tag_t) * capacity);

  if (items != NULL) {
    list->items = items;
    list->capacity = capacity;

    return RET_OK;
  } else {
    return RET_OOM;
  }
}

ret_t lrc_id_tag_list_append(lrc_id_tag_list_t* list, const char* id, const char* value) {
  lrc_id_tag_t* tag = NULL;

  return_value_if_fail(id != NULL && value != NULL && list != NULL, RET_BAD_PARAMS);
  return_value_if_fail(lrc_id_tag_list_expand(list) == RET_OK, RET_OOM);

  tag = list->items + list->size;

  tag->id = id;
  tag->value = value;
  list->size++;

  return RET_OK;
}

const char* lrc_id_tag_list_find(lrc_id_tag_list_t* list, const char* id) {
  uint32_t i = 0;
  lrc_id_tag_t* tag = NULL;
  return_value_if_fail(id != NULL && list != NULL, NULL);

  for (i = 0; i < list->size; i++) {
    tag = list->items + i;
    if (tk_str_ieq(id, tag->id)) {
      return tag->value;
    }
  }

  return NULL;
}

ret_t lrc_id_tag_list_destroy(lrc_id_tag_list_t* list) {
  return_value_if_fail(list != NULL, RET_BAD_PARAMS);

  TKMEM_FREE(list->items);
  TKMEM_FREE(list);

  return RET_OK;
}
