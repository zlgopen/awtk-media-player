/**
 * File:   lrc_builder_dump.c
 * Author: AWTK Develop Team
 * Brief:  lrc builder dump
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
#include "media_player/lrc/lrc_builder_dump.h"

static ret_t lrc_builder_dump_on_id_tag(lrc_builder_t* builder, const char* id, const char* value) {
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  str_append(&(dump->result), "[");
  str_append(&(dump->result), id);
  str_append(&(dump->result), ":");
  str_append(&(dump->result), value);
  str_append(&(dump->result), "]");

  return RET_OK;
}

static ret_t lrc_builder_dump_on_time_tag(lrc_builder_t* builder, uint32_t timestamp) {
  char buff[64];
  uint32_t m = timestamp / (1000 * 60);
  double s = (timestamp % (1000 * 60)) / 1000.0f;
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  tk_snprintf(buff, sizeof(buff), "[%02d:%2.2f]", m, s);

  str_append(&(dump->result), buff);

  return RET_OK;
}

static ret_t lrc_builder_dump_on_text(lrc_builder_t* builder, const char* text) {
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  str_append(&(dump->result), text);

  return RET_OK;
}

static ret_t lrc_builder_dump_on_error(lrc_builder_t* builder, const char* error) {
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  str_append(&(dump->result), error);

  return RET_OK;
}

static ret_t lrc_builder_dump_destroy(lrc_builder_t* builder) {
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;
  str_reset(&(dump->result));

  TKMEM_FREE(builder);

  return RET_OK;
}

static const lrc_builder_vtable_t s_lrc_builder_dump_vtable = {
    .on_text = lrc_builder_dump_on_text,
    .on_id_tag = lrc_builder_dump_on_id_tag,
    .on_time_tag = lrc_builder_dump_on_time_tag,
    .on_error = lrc_builder_dump_on_error,
    .destroy = lrc_builder_dump_destroy,
};

lrc_builder_t* lrc_builder_dump_create(void) {
  lrc_builder_dump_t* dump = TKMEM_ZALLOC(lrc_builder_dump_t);
  return_value_if_fail(dump != NULL, NULL);

  str_init(&(dump->result), 0);
  dump->lrc_builder.vt = &s_lrc_builder_dump_vtable;

  return (lrc_builder_t*)dump;
}
