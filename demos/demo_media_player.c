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

#include "awtk.h"
#include "media_player/widgets/lrc_view.h"
#include "media_player/widgets/video_view.h"
#include "media_player/base/media_player.h"
#include "media_player/ffmpeg/media_player_ffmpeg.h"

static ret_t app_global_init(void) {
  lrc_view_register();
  video_view_register();
  media_player_set(media_player_ffmpeg_create());
  data_reader_factory_set(data_reader_factory_create());
  data_reader_factory_register(data_reader_factory(), "file", data_reader_file_create);

  return RET_OK;
}

ret_t application_init() {
  widget_t* win = NULL;
  widget_t* video_view = NULL;

  app_global_init();
  log_set_log_level(LOG_LEVEL_DEBUG);

  win = window_open("video_player");
  video_view = widget_lookup_by_type(win, "video_view", TRUE);

  play_list_append(video_view_get_play_list(video_view), "data/test1.mp4");
  play_list_append(video_view_get_play_list(video_view), "data/test2.mp4");

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  media_player_destroy(media_player());
  data_reader_factory_destroy(data_reader_factory());
  media_player_set(NULL);

  return RET_OK;
}

#include "../res/assets.inc"
#include "awtk_main.inc"
