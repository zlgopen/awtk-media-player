/**
 * File:   audio_encoder_factory.h
 * Author: AWTK Develop Team
 * Brief:  audio encoder factory
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
 * 2021-01-18 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_AUDIO_ENCODER_FACTORY_H
#define TK_AUDIO_ENCODER_FACTORY_H

#include "tkc/object.h"
#include "tkc/data_writer.h"
#include "media_player/base/audio_encoder.h"

BEGIN_C_DECLS

typedef audio_encoder_t* (*audio_encoder_create_t)(data_writer_t* writer);

/**
 * @class audio_encoder_factory_t
 * audio encoder工厂。
 *
 */
typedef struct _audio_encoder_factory_t {
  /*private*/
  object_t* creators;
} audio_encoder_factory_t;

/**
 * @method audio_encoder_factory
 * 获取缺省的audio encoder工厂对象。
 * @annotation ["constructor"]
 * @return {audio_encoder_factory_t*} 返回audio encoder工厂对象。
 */
audio_encoder_factory_t* audio_encoder_factory(void);

/**
 * @method audio_encoder_factory_set
 * 设置缺省的audio encoder工厂对象。
 * @param {audio_encoder_factory_t*} factory audio encoder工厂对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_encoder_factory_set(audio_encoder_factory_t* factory);

/**
 * @method audio_encoder_factory_create
 * 创建audio encoder工厂对象。
 * @annotation ["constructor"]
 *
 * @return {audio_encoder_factory_t*} 返回audio encoder工厂对象。
 */
audio_encoder_factory_t* audio_encoder_factory_create(void);

/**
 * @method audio_encoder_factory_register
 * 注册audio encoder创建函数。
 * @param {audio_encoder_factory_t*} factory encoder工厂对象。
 * @param {const char*} type 类型(如mp3)。
 * @param {audio_encoder_create_t} create audio encoder创建函数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_encoder_factory_register(audio_encoder_factory_t* factory, const char* type,
                                     audio_encoder_create_t create);
/**
 * @method audio_encoder_factory_create_encoder
 * 创建指定类型的audio encoder对象。
 * @annotation ["constructor"]
 * @param {audio_encoder_factory_t*} factory audio encoder工厂对象。
 * @param {const char*} type 类型(如mp3)。
 * @param {data_writer_t*} writer writer对象。
 *
 * @return {audio_encoder_t*} 返回audio encoder对象。
 */
audio_encoder_t* audio_encoder_factory_create_encoder(audio_encoder_factory_t* factory,
                                                      const char* type, data_writer_t* writer);

/**
 * @method audio_encoder_factory_destroy
 * 析构并释放audio encoder工厂对象。
 * @param {audio_encoder_factory_t*} factory audio encoder工厂对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_encoder_factory_destroy(audio_encoder_factory_t* factory);

END_C_DECLS

#endif /*TK_AUDIO_ENCODER_FACTORY_H*/
