/**
 * File:   play_list.c
 * Author: AWTK Develop Team
 * Brief:  play list
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
 * 2020-02-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "media_player/base/play_list.h"

static ret_t filename_destroy(void* data) {
  TKMEM_FREE(data);
  return RET_OK;
}

static int filename_compare(const void* a, const void* b) {
  return strcmp((const char*)a, (const char*)b);
}

play_list_t* play_list_create(void) {
  play_list_t* list = TKMEM_ZALLOC(play_list_t);
  return_value_if_fail(list != NULL, NULL);

  darray_init(&(list->arr), 0, filename_destroy, filename_compare);

  return list;
}

ret_t play_list_append(play_list_t* list, const char* filename) {
  char* dup = NULL;
  return_value_if_fail(list != NULL && filename != NULL, RET_BAD_PARAMS);
  dup = tk_strdup(filename);
  return_value_if_fail(dup != NULL, RET_OOM);

  if (darray_push(&(list->arr), dup) != RET_OK) {
    TKMEM_FREE(dup);
  }

  return RET_OK;
}

ret_t play_list_remove(play_list_t* list, const char* filename) {
  ret_t ret = RET_OK;
  return_value_if_fail(list != NULL && filename != NULL, RET_BAD_PARAMS);

  ret = darray_remove(&(list->arr), (void*)filename);

  if (list->curr < play_list_get_size(list)) {
    if (play_list_get_size(list) > 0) {
      list->curr = play_list_get_size(list) - 1;
    } else {
      list->curr = 0;
    }
  }

  return ret;
}

uint32_t play_list_get_size(play_list_t* list) {
  return_value_if_fail(list != NULL, 0);

  return list->arr.size;
}

static ret_t play_list_shuffle(play_list_t* list) {
  uint32_t curr = list->curr;
  uint32_t size = play_list_get_size(list);

  while (curr == list->curr) {
    list->curr = random() % size;
  }

  return RET_OK;
}

ret_t play_list_next(play_list_t* list) {
  uint32_t size = play_list_get_size(list);
  if (size <= 1) {
    return RET_OK;
  }

  switch (list->mode) {
    case PLAY_MODE_SHUFFLE: {
      play_list_shuffle(list);
      break;
    }
    case PLAY_MODE_REPEAT_ALL: {
      list->curr = (list->curr + 1) % size;
      break;
    }
    default:
      break;
  }

  return RET_OK;
}

ret_t play_list_prev(play_list_t* list) {
  uint32_t size = play_list_get_size(list);

  if (size <= 1) {
    return RET_OK;
  }

  switch (list->mode) {
    case PLAY_MODE_SHUFFLE: {
      play_list_shuffle(list);
      break;
    }
    case PLAY_MODE_REPEAT_ALL: {
      list->curr = (list->curr - 1 + size) % size;
      break;
    }
    default:
      break;
  }

  return RET_OK;
}

const char* play_list_curr(play_list_t* list) {
  return_value_if_fail(list != NULL, NULL);

  if (list->curr < play_list_get_size(list)) {
    return (const char*)(list->arr.elms[list->curr]);
  }

  return NULL;
}

ret_t play_list_set_play_mode(play_list_t* list, play_mode_t mode) {
  return_value_if_fail(list != NULL, RET_BAD_PARAMS);

  list->mode = mode;

  return RET_OK;
}

ret_t play_list_destroy(play_list_t* list) {
  return_value_if_fail(list != NULL, RET_BAD_PARAMS);

  darray_deinit(&(list->arr));
  TKMEM_FREE(list);

  return RET_OK;
}
