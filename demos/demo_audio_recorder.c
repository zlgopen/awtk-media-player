/**
 * File:   demo_audio_recorder.c
 * Author: AWTK Develop Team
 * Brief:  audio_recorder demo
 *
 * Copyright (c) 2021 - 2021  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2021-01-19 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "media_player/media_player_helper.h"

#define STR_DURATION "duration"

static ret_t on_time_elapse(const timer_info_t* info) {
  widget_t* win = WIDGET(info->ctx);
  widget_t* duration = widget_lookup(win, STR_DURATION, TRUE);

  if (audio_recorder_get_state(audio_recorder()) == AUDIO_RECODER_RECORDING) {
    widget_add_value(duration, 1);
    return RET_REPEAT;
  } else {
    return RET_REMOVE;
  }
}

static ret_t on_start_stop_click(void* ctx, event_t* e) {
  widget_t* win = WIDGET(ctx);
  widget_t* widget = WIDGET(e->target);
  const char* url = "file://./test.mp3";
  int32_t play = widget_get_value(widget);
  widget_t* duration = widget_lookup(win, STR_DURATION, TRUE);

  if (play) {
    widget_set_value(duration, 0);
    timer_add(on_time_elapse, win, 1000);
    audio_recorder_start(audio_recorder(), url);
  } else {
    audio_recorder_stop(audio_recorder());
  }

  return RET_OK;
}

static ret_t application_init() {
  widget_t* win = NULL;
  media_player_init(TRUE);
  log_set_log_level(LOG_LEVEL_DEBUG);

  win = window_open("audio_recorder");
  widget_child_on(win, "start_stop", EVT_CLICK, on_start_stop_click, win);

  widget_layout(win);

  return RET_OK;
}

ret_t application_exit() {
  media_player_deinit();

  return RET_OK;
}

#include "../res/assets.inc"
#include "awtk_main.inc"
