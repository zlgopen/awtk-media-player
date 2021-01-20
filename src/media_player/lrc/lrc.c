/**
 * File:   lrc.c
 * Author: AWTK Develop Team
 * Brief:  lrc
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
#include "media_player/lrc/lrc.h"
#include "media_player/lrc/lrc_parser.h"
#include "media_player/lrc/lrc_builder.h"

typedef struct _lrc_builder_default_t {
  lrc_builder_t lrc_builder;

  lrc_t* lrc;
  char* p;
  char* strs;
  uint32_t size;
} lrc_builder_default_t;

#define lrc_isspace(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')

static const char* lrc_builder_default_dup(lrc_builder_default_t* b, const char* text) {
  char* p = b->p;
  uint32_t size = strlen(text);
  const char* start = text;
  const char* end = start + size - 1;

  while (*start && lrc_isspace(*start)) start++;
  while (end > start && lrc_isspace(*end)) end--;

  size = end - start + 1;
  memcpy(p, start, size);
  p[size] = '\0';

  b->p += size + 1;

  return p;
}

#define DUP(text) lrc_builder_default_dup(b, text)

static ret_t lrc_builder_default_on_id_tag(lrc_builder_t* builder, const char* id,
                                           const char* value) {
  lrc_builder_default_t* b = (lrc_builder_default_t*)builder;

  lrc_id_tag_list_append(b->lrc->id_tags, DUP(id), DUP(value));

  return RET_OK;
}

static ret_t lrc_builder_default_on_time_tag(lrc_builder_t* builder, uint32_t timestamp) {
  lrc_builder_default_t* b = (lrc_builder_default_t*)builder;

  lrc_time_tag_list_append(b->lrc->time_tags, timestamp);

  return RET_OK;
}

static ret_t lrc_builder_default_on_text(lrc_builder_t* builder, const char* text) {
  lrc_builder_default_t* b = (lrc_builder_default_t*)builder;

  lrc_time_tag_list_set_text(b->lrc->time_tags, DUP(text));

  return RET_OK;
}

static ret_t lrc_builder_default_on_error(lrc_builder_t* builder, const char* error) {
  log_debug("error:%s\n", error);

  return RET_OK;
}

static ret_t lrc_builder_default_destroy(lrc_builder_t* builder) {
  lrc_builder_default_t* b = (lrc_builder_default_t*)builder;

  b->lrc->strs = b->strs;

  return RET_OK;
}

static const lrc_builder_vtable_t s_lrc_builder_default_vtable = {
    .on_text = lrc_builder_default_on_text,
    .on_id_tag = lrc_builder_default_on_id_tag,
    .on_time_tag = lrc_builder_default_on_time_tag,
    .on_error = lrc_builder_default_on_error,
    .destroy = lrc_builder_default_destroy,
};

lrc_builder_t* lrc_builder_default_init(lrc_builder_default_t* b, lrc_t* lrc, char* strs,
                                        uint32_t size) {
  return_value_if_fail(strs != NULL, NULL);

  b->lrc = lrc;
  b->p = strs;
  b->strs = strs;
  b->size = size;
  memset(strs, 0x00, size);
  b->lrc_builder.vt = &s_lrc_builder_default_vtable;

  return (lrc_builder_t*)b;
}

static lrc_t* lrc_parse(lrc_t* lrc, const char* text) {
  ret_t ret = RET_OK;
  lrc_builder_default_t builder;
  uint32_t size = strlen(text) + 1;
  char* strs = TKMEM_ALLOC(size);
  lrc_builder_t* b = lrc_builder_default_init(&builder, lrc, strs, size);

  ret = lrc_parser_parse(b, text);
  lrc_time_tag_list_sort(lrc->time_tags);
  lrc_builder_destroy(&builder);

  return ret == RET_OK ? lrc : NULL;
}

lrc_t* lrc_create(const char* text) {
  lrc_t* lrc = NULL;
  return_value_if_fail(text != NULL, NULL);

  lrc = TKMEM_ZALLOC(lrc_t);
  return_value_if_fail(lrc != NULL, NULL);

  lrc->id_tags = lrc_id_tag_list_create();
  lrc->time_tags = lrc_time_tag_list_create();

  if (lrc->id_tags == NULL || lrc->time_tags == NULL) {
    lrc_destroy(lrc);
    lrc = NULL;
  }

  return_value_if_fail(lrc != NULL, NULL);

  if (lrc_parse(lrc, text) == NULL) {
    lrc_destroy(lrc);
    lrc = NULL;
  }

  return lrc;
}

ret_t lrc_destroy(lrc_t* lrc) {
  return_value_if_fail(lrc != NULL, RET_BAD_PARAMS);

  lrc_id_tag_list_destroy(lrc->id_tags);
  lrc_time_tag_list_destroy(lrc->time_tags);
  TKMEM_FREE(lrc->strs);
  TKMEM_FREE(lrc);

  return RET_OK;
}
