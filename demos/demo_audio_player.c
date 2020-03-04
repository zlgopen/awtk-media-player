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
#include "media_player/widgets/audio_view.h"
#include "media_player/base/media_player.h"
#include "media_player/audio_player/audio_decoder_mp3.h"
#include "media_player/audio_player/audio_decoder_factory.h"
#include "media_player/audio_player/media_player_audio.h"

static ret_t on_quit_click(void* ctx, event_t* e) {
  tk_quit();
  return RET_OK;
}

static ret_t app_global_init(void) {
  lrc_view_register();
  audio_view_register();
  media_player_set(media_player_audio_create());
  data_reader_factory_set(data_reader_factory_create());
  data_reader_factory_register(data_reader_factory(), "file", data_reader_file_create);
  audio_decoder_factory_set(audio_decoder_factory_create());
  audio_decoder_factory_register(audio_decoder_factory(), "mp3", audio_decoder_mp3_create);

  return RET_OK;
}

static ret_t application_init() {
  widget_t* win = NULL;
  widget_t* audio_view = NULL;
  media_player_t* player = NULL;

  app_global_init();
  log_set_log_level(LOG_LEVEL_DEBUG);

  player = media_player();
  win = window_open("audio_player");
  audio_view = widget_lookup_by_type(win, "audio_view", TRUE);

  play_list_append(audio_view_get_play_list(audio_view), "data/test.mp3");
  play_list_append(audio_view_get_play_list(audio_view), "data/song1.mp3");
  play_list_append(audio_view_get_play_list(audio_view), "data/song2.mp3");
  play_list_append(audio_view_get_play_list(audio_view), "data/song3.mp3");

  widget_child_on(win, "close", EVT_CLICK, on_quit_click, NULL);
  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  data_reader_factory_destroy(data_reader_factory());

  return RET_OK;
}

#define LCD_WIDTH 800
#define LCD_HEGHT 480
#include "awtk_main.inc"
