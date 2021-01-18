/**
 * File:   audio_encoder.c
 * Author: AWTK Develop Team
 * Brief:  audio encoder interface
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
 * 2021-01-18 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "media_player/base/audio_encoder.h"

int32_t audio_encoder_encode(audio_encoder_t* encoder, const void* buff, uint32_t size) {
  return_value_if_fail(buff != NULL && size > 0, 0);
  return_value_if_fail(encoder != NULL && encoder->vt != NULL && encoder->vt->encode != NULL, 0);

  return encoder->vt->encode(encoder, buff, size);
}

ret_t audio_encoder_destroy(audio_encoder_t* encoder) {
  return_value_if_fail(encoder != NULL && encoder->vt != NULL && encoder->vt->destroy != NULL,
                       RET_BAD_PARAMS);

  return encoder->vt->destroy(encoder);
}

ret_t audio_encoder_get_prop(audio_encoder_t* encoder, const char* name, value_t* v) {
  return_value_if_fail(encoder != NULL && encoder->vt != NULL && encoder->vt->get_prop != NULL,
                       RET_BAD_PARAMS);

  return encoder->vt->get_prop(encoder, name, v);
}

ret_t audio_encoder_set_prop(audio_encoder_t* encoder, const char* name, const value_t* v) {
  return_value_if_fail(encoder != NULL && encoder->vt != NULL && encoder->vt->set_prop != NULL,
                       RET_BAD_PARAMS);

  return encoder->vt->set_prop(encoder, name, v);
}

