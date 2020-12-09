/**
 * File:   audio_decoder_mp3.h
 * Author: AWTK Develop Team
 * Brief:  mp3 audio decoder
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

#ifndef TK_AUDIO_DECODER_MP3_H
#define TK_AUDIO_DECODER_MP3_H

#include "tkc/data_reader.h"
#include "media_player/base/audio_decoder.h"

BEGIN_C_DECLS

/**
 * @method audio_decoder_mp3_create
 * 创建decoder对象。
 * @param {data_reader_t*} reader data reader对象(由decoder销毁)。
 * @return {audio_decoder_t*} 返回decoder对象。
 */
audio_decoder_t* audio_decoder_mp3_create(data_reader_t* reader);

END_C_DECLS

#endif /*TK_AUDIO_DECODER_MP3_H*/
