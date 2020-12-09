/**
 * File:   media_player_audio.h
 * Author: AWTK Develop Team
 * Brief:  media_player_audio
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
 * 2020-02-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_MEDIA_PLAYER_AUDIO_H
#define TK_MEDIA_PLAYER_AUDIO_H

#include "media_player/base/media_player.h"

BEGIN_C_DECLS

/**
 * @class media_player_audio_t
 * @parent media_player_t
 * @annotation ["fake"]
 * 音频播放器。
 */

/**
 * @method media_player_audio_create
 * 创建音频播放器对象。
 * @return {media_player_t*} 返回media player对象。
 */
media_player_t* media_player_audio_create(void);

END_C_DECLS

#endif /*TK_MEDIA_PLAYER_AUDIO_H*/
