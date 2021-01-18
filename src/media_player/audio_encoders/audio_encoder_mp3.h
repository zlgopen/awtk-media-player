/**
 * File:   audio_encoder_mp3.h
 * Author: AWTK Develop Team
 * Brief:  mp3 audio encoder
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

#ifndef TK_AUDIO_ENCODER_MP3_H
#define TK_AUDIO_ENCODER_MP3_H

#include "tkc/data_writer.h"
#include "media_player/base/audio_encoder.h"

BEGIN_C_DECLS

/**
 * @method audio_encoder_mp3_create
 * 创建encoder对象。
 * @param {data_writer_t*} writer data writer对象(由encoder销毁)。
 * @return {audio_encoder_t*} 返回encoder对象。
 */
audio_encoder_t* audio_encoder_mp3_create(data_writer_t* writer);

END_C_DECLS

#endif /*TK_AUDIO_ENCODER_MP3_H*/
