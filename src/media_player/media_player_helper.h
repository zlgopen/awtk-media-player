/**
 * File:   media_player_helper.h
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
 * 2021-01-20 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_MEDIA_PLAYER_HELPER_H
#define TK_MEDIA_PLAYER_HELPER_H

#include "awtk.h"
#include "media_player/base/play_list.h"
#include "media_player/base/media_player.h"
#include "media_player/widgets/audio_view.h"
#include "media_player/widgets/video_view.h"
#include "media_player/base/audio_encoder_factory.h"
#include "media_player/base/audio_decoder_factory.h"
#include "media_player/audio_recorder/audio_recorder.h"

BEGIN_C_DECLS

/**
 * @method media_player_init
 * 初始化。
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_init(void);

/**
 * @method media_player_deinit
 * ~初始化。
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_deinit(void);

END_C_DECLS

#endif /*TK_MEDIA_PLAYER_HELPER_H*/
