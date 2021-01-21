/**
 * File:   audio_encoder.h
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

#ifndef TK_AUDIO_ENCODER_H
#define TK_AUDIO_ENCODER_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

struct _audio_encoder_t;
typedef struct _audio_encoder_t audio_encoder_t;

typedef int32_t (*audio_encoder_encode_t)(audio_encoder_t* encoder, const void* buff,
                                          uint32_t size);
typedef ret_t (*audio_encoder_set_prop_t)(audio_encoder_t* encoder, const char* name,
                                          const value_t* v);
typedef ret_t (*audio_encoder_get_prop_t)(audio_encoder_t* encoder, const char* name, value_t* v);
typedef ret_t (*audio_encoder_destroy_t)(audio_encoder_t* encoder);

typedef struct _audio_encoder_vtable_t {
  audio_encoder_encode_t encode;
  audio_encoder_set_prop_t set_prop;
  audio_encoder_get_prop_t get_prop;
  audio_encoder_destroy_t destroy;
} audio_encoder_vtable_t;

/**
 * @class audio_encoder_t
 * 音频编码器接口。
 *
 * 音频编码器除了将声音编码成mp3/wav等文件外，也可以将声音识别成文本。
 *
 */
struct _audio_encoder_t {
  const audio_encoder_vtable_t* vt;
  /**
   * @property {int32_t} freq
   * @annotation ["readable"]
   * 每秒采样数量。
   */
  int32_t freq;

  /**
   * @property {uint8_t} channels
   * @annotation ["readable"]
   * 通道数。1表示单声道，2表示立体声。
   */
  uint8_t channels;
};

/**
 * @method audio_encoder_encode
 * 对音频数据进行编码。
 *
 * @param {audio_encoder_t*} audio_encoder audio_encoder对象。
 * @param {const void*} buff 待编码的数据。
 * @param {uint32_t} size buff的大小。
 *
 * @return {int32_t} 返回实际编码的原始数据的长度。
 */
int32_t audio_encoder_encode(audio_encoder_t* encoder, const void* buff, uint32_t size);

/**
 * @method audio_encoder_set_prop
 * 设置属性。
 *
 * @param {audio_encoder_t*} encoder audio_encoder对象。
 * @param {const char*} name 属性名。
 * @param {const value_t*} v 属性值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_encoder_set_prop(audio_encoder_t* encoder, const char* name, const value_t* v);

/**
 * @method audio_encoder_get_prop
 * 获取属性。
 *
 * @param {audio_encoder_t*} encoder audio_encoder对象。
 * @param {const char*} name 属性名。
 * @param {const value_t*} v 属性值(返回)。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_encoder_get_prop(audio_encoder_t* encoder, const char* name, value_t* v);

/**
 * @method audio_encoder_destroy
 * 销毁audio encoder对象。
 *
 * @param {audio_encoder_t*} encoder audio_encoder对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_encoder_destroy(audio_encoder_t* encoder);

/*通道数*/
#define AUDIO_ENCODER_PROP_CHANNELS "channels"

/*采样率*/
#define AUDIO_ENCODER_PROP_SAMPLE_RATE "samplerate"

/*一次编码数据长度*/
#define AUDIO_ENCODER_PROP_PREFER_BUFFER_SIZE "prefer_buffer_size"

END_C_DECLS

#endif /*TK_AUDIO_ENCODER_H*/
