/**
 * File:   audio_decoder_factory.h
 * Author: AWTK Develop Team
 * Brief:  audio decoder factory
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
 * ================================================================
 * 2020-03-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_AUDIO_DECODER_FACTORY_H
#define TK_AUDIO_DECODER_FACTORY_H

#include "tkc/darray.h"
#include "tkc/data_reader.h"
#include "media_player/audio_player/audio_decoder.h"

BEGIN_C_DECLS

typedef audio_decoder_t* (*audio_decoder_create_t)(data_reader_t* reader);

/**
 * @class audio_decoder_factory_t
 * audio decoder工厂。
 *
 */
typedef struct _audio_decoder_factory_t {
  /*private*/
  darray_t creators;
} audio_decoder_factory_t;

/**
 * @method audio_decoder_factory
 * 获取缺省的audio decoder工厂对象。
 * @annotation ["constructor"]
 * @return {audio_decoder_factory_t*} 返回audio decoder工厂对象。
 */
audio_decoder_factory_t* audio_decoder_factory(void);

/**
 * @method audio_decoder_factory_set
 * 设置缺省的audio decoder工厂对象。
 * @param {audio_decoder_factory_t*} factory audio decoder工厂对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_decoder_factory_set(audio_decoder_factory_t* factory);

/**
 * @method audio_decoder_factory_create
 * 创建audio decoder工厂对象。
 * @annotation ["constructor"]
 *
 * @return {audio_decoder_factory_t*} 返回audio decoder工厂对象。
 */
audio_decoder_factory_t* audio_decoder_factory_create(void);

/**
 * @method audio_decoder_factory_register
 * 注册audio decoder创建函数。
 * @param {audio_decoder_factory_t*} factory decoder工厂对象。
 * @param {const char*} type 类型(如mp3)。
 * @param {audio_decoder_create_t} create audio decoder创建函数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_decoder_factory_register(audio_decoder_factory_t* factory, const char* type,
                                     audio_decoder_create_t create);
/**
 * @method audio_decoder_factory_create_decoder
 * 创建指定类型的audio decoder对象。
 * @annotation ["constructor"]
 * @param {audio_decoder_factory_t*} factory audio decoder工厂对象。
 * @param {const char*} type 类型(如mp3)。
 * @param {data_reader_t*} reader reader对象。
 *
 * @return {audio_decoder_t*} 返回audio decoder对象。
 */
audio_decoder_t* audio_decoder_factory_create_decoder(audio_decoder_factory_t* factory,
                                                      const char* type, data_reader_t* reader);

/**
 * @method audio_decoder_factory_destroy
 * 析构并释放audio decoder工厂对象。
 * @param {audio_decoder_factory_t*} factory audio decoder工厂对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_decoder_factory_destroy(audio_decoder_factory_t* factory);

END_C_DECLS

#endif /*TK_AUDIO_DECODER_FACTORY_H*/
