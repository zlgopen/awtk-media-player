/**
 * File:   audio_decoder.h
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

#ifndef TK_AUDIO_DECODER_H
#define TK_AUDIO_DECODER_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

struct _audio_decoder_t;
typedef struct _audio_decoder_t audio_decoder_t;

typedef ret_t (*audio_decoder_seek_t)(audio_decoder_t* decoder, uint32_t offset);
typedef int32_t (*audio_decoder_decode_t)(audio_decoder_t* decoder, void* buff, uint32_t size);
typedef ret_t (*audio_decoder_destroy_t)(audio_decoder_t* decoder);

typedef struct _audio_decoder_vtable_t {
  audio_decoder_seek_t seek;
  audio_decoder_decode_t decode;
  audio_decoder_destroy_t destroy;
} audio_decoder_vtable_t;

/**
 * @class audio_decoder_t
 * 媒体播放器接口。
 */
struct _audio_decoder_t {
  const audio_decoder_vtable_t* vt;

  /**
   * @property {uint32_t} position 
   * @annotation ["readable"]
   * 当前解码位置(ms)。
   */
  uint32_t position;

  /**
   * @property {uint32_t} duration
   * @annotation ["readable"]
   * 时间长度(ms)。
   */
  uint32_t duration;

  /**
   * @property {int32_t} freq
   * @annotation ["readable"]
   * 每秒采样数量。
   */
  int32_t freq;

  /**
   * @property {uint32_t} format
   * @annotation ["readable"]
   * 音频格式。
   */
  uint32_t format;

  /**
   * @property {uint8_t} channels
   * @annotation ["readable"]
   * 通道数。1表示单声道，2表示立体声。
   */
  uint8_t channels;

  /**
   * @property {uint32_t} samples
   * @annotation ["readable"]
   * 总采样数。
   */
  uint32_t samples;
};

/**
 * @method audio_decoder_decode
 * 解码数据。
 *
 * @param {audio_decoder_t*} audio_decoder audio_decoder对象。
 * @param {void*} buff 返回解码的数据。
 * @param {uint32_t} size buff的大小。
 *
 * @return {int32_t} 返回实际数据的长度。
 */
int32_t audio_decoder_decode(audio_decoder_t* decoder, void* buff, uint32_t size);

/**
 * @method audio_decoder_seek
 * 定位到指定的位置。
 *
 * @param {audio_decoder_t*} decoder audio_decoder对象。
 * @param {uint32_t} offset 绝对偏移量(ms)。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_decoder_seek(audio_decoder_t* decoder, uint32_t offset);

/**
 * @method audio_decoder_destroy
 * 销毁audio decoder对象。
 *
 * @param {audio_decoder_t*} decoder audio_decoder对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_decoder_destroy(audio_decoder_t* decoder);

END_C_DECLS

#endif /*TK_AUDIO_DECODER_H*/
