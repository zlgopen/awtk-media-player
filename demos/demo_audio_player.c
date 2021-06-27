/**
 * File:   demo_media_player.c
 * Author: AWTK Develop Team
 * Brief:  media_player demo
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2019-05-10 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "media_player/media_player_helper.h"

static ret_t application_init() {
  widget_t* win = NULL;
  widget_t* audio_view = NULL;

  media_player_init(TRUE);
  log_set_log_level(LOG_LEVEL_DEBUG);

  win = window_open("audio_player");
  audio_view = widget_lookup_by_type(win, "audio_view", TRUE);

  play_list_append(audio_view_get_play_list(audio_view), "data/test.mp3");
  play_list_append(audio_view_get_play_list(audio_view), "data/song1.mp3");
  play_list_append(audio_view_get_play_list(audio_view), "data/song2.mp3");
  play_list_append(audio_view_get_play_list(audio_view), "data/song3.mp3");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  media_player_deinit();

  return RET_OK;
}

#include "../res/assets.inc"
#include "awtk_main.inc"
