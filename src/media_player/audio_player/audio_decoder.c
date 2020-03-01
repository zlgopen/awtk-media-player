/**
 * File:   audio_decoder.c
 * Author: AWTK Develop Team
 * Brief:  audio decoder interface
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
 * 2020-03-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "media_player/audio_player/audio_decoder.h"

int32_t audio_decoder_decode(audio_decoder_t* decoder, void* buff, uint32_t size) {
  return_value_if_fail(buff != NULL && size > 0, 0);
  return_value_if_fail(decoder != NULL && decoder->vt != NULL && decoder->vt->decode != NULL, 0);

  return decoder->vt->decode(decoder, buff, size);
}

ret_t audio_decoder_seek(audio_decoder_t* decoder, uint32_t offset) {
  return_value_if_fail(decoder != NULL && decoder->vt != NULL && decoder->vt->seek != NULL,
                       RET_BAD_PARAMS);

  return decoder->vt->seek(decoder, offset);
}

ret_t audio_decoder_destroy(audio_decoder_t* decoder) {
  return_value_if_fail(decoder != NULL && decoder->vt != NULL && decoder->vt->destroy != NULL,
                       RET_BAD_PARAMS);

  return decoder->vt->destroy(decoder);
}
