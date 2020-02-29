/**
 * File:   lrc_builder.c
 * Author: AWTK Develop Team
 * Brief:  lrc builder interface
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

#include "media_player/lrc/lrc_builder.h"

ret_t lrc_builder_on_id_tag(lrc_builder_t* builder, const char* id, const char* value) {
  return_value_if_fail(builder != NULL && builder->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(id != NULL && value != NULL, RET_BAD_PARAMS);
  return_value_if_fail(builder->vt->on_id_tag != NULL, RET_BAD_PARAMS);

  return builder->vt->on_id_tag(builder, id, value);
}

ret_t lrc_builder_on_time_tag(lrc_builder_t* builder, uint32_t timestamp) {
  return_value_if_fail(builder != NULL && builder->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(builder->vt->on_time_tag != NULL, RET_BAD_PARAMS);

  return builder->vt->on_time_tag(builder, timestamp);
}

ret_t lrc_builder_on_text(lrc_builder_t* builder, const char* text) {
  return_value_if_fail(builder != NULL && builder->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(builder->vt->on_text != NULL, RET_BAD_PARAMS);
  return_value_if_fail(text != NULL, RET_BAD_PARAMS);

  return builder->vt->on_text(builder, text);
}

ret_t lrc_builder_on_error(lrc_builder_t* builder, const char* error) {
  return_value_if_fail(builder != NULL && builder->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(builder->vt->on_error != NULL, RET_BAD_PARAMS);
  return_value_if_fail(error != NULL, RET_BAD_PARAMS);

  return builder->vt->on_error(builder, error);
}

ret_t lrc_builder_destroy(lrc_builder_t* builder) {
  return_value_if_fail(builder != NULL && builder->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(builder->vt->destroy != NULL, RET_BAD_PARAMS);

  return builder->vt->destroy(builder);
}
