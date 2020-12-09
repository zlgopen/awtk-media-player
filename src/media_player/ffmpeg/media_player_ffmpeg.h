/**
 * File:   media_player_ffmpeg.h
 * Author: AWTK Develop Team
 * Brief:  media_player_ffmpeg
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
 * 2020-02-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_MEDIA_PLAYER_FFMPEG_H
#define TK_MEDIA_PLAYER_FFMPEG_H

#include "media_player/base/media_player.h"

BEGIN_C_DECLS

/**
 * @class media_player_ffmpeg_t
 * @parent media_player_t
 * @annotation ["fake"]
 * 基于ffmpeg实现的视频播放器。
 */

/**
 * @method media_player_ffmpeg_create
 * 创建视频播放器对象。
 * @return {media_player_t*} 返回media player对象。
 */
media_player_t* media_player_ffmpeg_create(void);

END_C_DECLS

#endif /*TK_MEDIA_PLAYER_FFMPEG_H*/
