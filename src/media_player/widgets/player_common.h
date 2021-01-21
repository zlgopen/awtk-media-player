/**
 * File:   player_common.h
 * Author: AWTK Develop Team
 * Brief:  common stuff shared by players
 *
 * Copyright (c) 2020 - 2020 Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2020-03-05 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_PLAYER_COMMON_H
#define TK_PLAYER_COMMON_H

#include "base/widget.h"
#include "media_player/lrc/lrc.h"
#include "media_player/base/play_list.h"
#include "media_player/base/media_player.h"

BEGIN_C_DECLS

#define WIDGET_PROP_LRC "lrc"
#define WIDGET_PROP_PLAY_LIST "play_list"

#define WIDGET_NAME_LRC "lrc"
#define WIDGET_NAME_MUTE "mute"
#define WIDGET_NAME_MODE "mode"
#define WIDGET_NAME_PLAY "play"
#define WIDGET_NAME_PREV "prev"
#define WIDGET_NAME_NEXT "next"
#define WIDGET_NAME_TITLE "title"
#define WIDGET_NAME_AUTHOR "author"
#define WIDGET_NAME_VOLUME "volume"
#define WIDGET_NAME_ELAPSED "elapsed"
#define WIDGET_NAME_DURATION "duration"
#define WIDGET_NAME_PROGRESS "progress"
#define WIDGET_NAME_MUTABLE_IMAGE "mutable_image"

ret_t player_hook_children(widget_t* widget);
ret_t player_on_update_timer(const timer_info_t* info);
ret_t player_on_media_player_event(void* ctx, event_t* e);
media_player_t* player_get(widget_t* widget);
ret_t player_set(widget_t* widget, media_player_t* player);

END_C_DECLS

#endif /*TK_PLAYER_COMMON_H*/
