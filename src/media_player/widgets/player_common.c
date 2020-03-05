/**
 * File:   player_common.c
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

#include "tkc/path.h"
#include "tkc/utils.h"
#include "tkc/data_reader.h"
#include "media_player/widgets/player_common.h"

#define WIDGET_GET_PLAY_LIST(widget) \
  (play_list_t*)widget_get_prop_pointer(widget, WIDGET_PROP_PLAY_LIST);

static ret_t widget_set_value_without_notify(widget_t* widget, uint32_t value) {
  emitter_disable(widget->emitter);
  widget_set_value(widget, value);
  emitter_enable(widget->emitter);

  return RET_OK;
}

static ret_t player_play_curr(play_list_t* play_list) {
  media_player_t* player = media_player();
  const char* url = play_list_curr(play_list);
  return_value_if_fail(url != NULL, RET_BAD_PARAMS);

  return_value_if_fail(media_player_load(player, url) == RET_OK, RET_FAIL);

  return media_player_start(player);
}

static ret_t player_on_play_or_pause(void* ctx, event_t* e) {
  media_player_t* player = media_player();
  play_list_t* play_list = (play_list_t*)(ctx);
  return_value_if_fail(play_list != NULL && player != NULL, RET_BAD_PARAMS);

  media_player_state_t state = media_player_get_state(player);

  if (state == MEDIA_PLAYER_PAUSED) {
    media_player_start(player);
  } else if (state == MEDIA_PLAYER_PLAYING) {
    media_player_pause(player);
  } else {
    player_play_curr(play_list);
  }

  return RET_OK;
}

static ret_t player_on_prev(void* ctx, event_t* e) {
  play_list_t* play_list = (play_list_t*)(ctx);

  return_value_if_fail(play_list_prev(play_list) == RET_OK, RET_BAD_PARAMS);

  return player_play_curr(play_list);
}

static ret_t player_on_next(void* ctx, event_t* e) {
  play_list_t* play_list = (play_list_t*)(ctx);

  return_value_if_fail(play_list_next(play_list) == RET_OK, RET_BAD_PARAMS);

  return player_play_curr(play_list);
}

static ret_t player_idle_on_done(const idle_info_t* info) {
  widget_t* widget = WIDGET(info->ctx);
  play_list_t* play_list = WIDGET_GET_PLAY_LIST(widget);

  return_value_if_fail(play_list_next(play_list) == RET_OK, RET_BAD_PARAMS);

  player_play_curr(play_list);

  return RET_REMOVE;
}

static ret_t player_idle_on_load(const idle_info_t* info) {
  char* lrc_text = NULL;
  char lrc_filename[MAX_PATH + 1];
  widget_t* widget = WIDGET(info->ctx);
  play_list_t* play_list = WIDGET_GET_PLAY_LIST(widget);
  widget_t* lrc = widget_lookup(widget, WIDGET_NAME_LRC, TRUE);
  const char* url = play_list_curr(play_list);
  return_value_if_fail(url != NULL, RET_REMOVE);

  if (lrc != NULL) {
    lrc_t* alrc = NULL;

    path_replace_extname(lrc_filename, sizeof(lrc_filename), url, "lrc");
    lrc_text = data_reader_read_all(lrc_filename, NULL);

    if (lrc_text != NULL) {
      alrc = lrc_create(lrc_text);
      TKMEM_FREE(lrc_text);
    } else {
      alrc = lrc_create("[ar:unkown][ti:unkown][0:0]no lyric");
    }
    widget_set_prop_pointer(widget, WIDGET_PROP_LRC, alrc);
  }

  return RET_REMOVE;
}

ret_t player_on_media_player_event(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(ctx);

  switch (e->type) {
    case EVT_MEDIA_PLAYER_LOADED: {
      idle_add(player_idle_on_load, widget);
      break;
    }
    case EVT_MEDIA_PLAYER_PAUSED: {
      log_debug("paused\n");
      break;
    }
    case EVT_MEDIA_PLAYER_DONE: {
      log_debug("done\n");
      idle_add(player_idle_on_done, widget);
      break;
    }
  }
  return RET_OK;
}

static ret_t player_on_mute_changed(void* ctx, event_t* e) {
  widget_t* target = WIDGET(e->target);
  uint32_t muted = widget_get_value(target);

  return media_player_set_muted(media_player(), muted);
}

static ret_t player_on_mode_changed(void* ctx, event_t* e) {
  play_list_t* play_list = (play_list_t*)(ctx);
  widget_t* target = WIDGET(e->target);
  uint32_t mode = widget_get_value(target);

  return play_list_set_play_mode(play_list, mode);
}

static ret_t player_on_progress_changed(void* ctx, event_t* e) {
  widget_t* target = WIDGET(e->target);
  uint32_t position = widget_get_value(target);
  media_player_t* player = media_player();

  media_player_seek(player, position);

  return RET_OK;
}

static ret_t player_on_volume_changed(void* ctx, event_t* e) {
  widget_t* target = WIDGET(e->target);
  uint32_t volume = widget_get_value(target);

  return media_player_set_volume(media_player(), volume);
}

static const char* player_format_time(char* buff, uint32_t size, uint32_t ms) {
  uint32_t m = ms / (60 * 1000);
  uint32_t s = (ms / 1000) % 60;
  tk_snprintf(buff, size, "%02u:%02u", m, s);

  return buff;
}

ret_t player_on_update_timer(const timer_info_t* info) {
  char buff[64];
  widget_t* widget = WIDGET(info->ctx);
  media_player_t* player = media_player();
  widget_t* lrc = widget_lookup(widget, WIDGET_NAME_LRC, TRUE);
  widget_t* play = widget_lookup(widget, WIDGET_NAME_PLAY, TRUE);
  widget_t* elapsed = widget_lookup(widget, WIDGET_NAME_ELAPSED, TRUE);
  widget_t* progress = widget_lookup(widget, WIDGET_NAME_PROGRESS, TRUE);
  widget_t* duration = widget_lookup(widget, WIDGET_NAME_DURATION, TRUE);
  media_player_state_t state = media_player_get_state(player);

  if (state == MEDIA_PLAYER_PLAYING) {
    uint32_t telapsed = media_player_get_elapsed(player);
    uint32_t tduration = media_player_get_duration(player);

    widget_set_value_without_notify(progress, telapsed);
    widget_set_prop_int(progress, WIDGET_PROP_MAX, tduration);
    widget_set_text_utf8(elapsed, player_format_time(buff, sizeof(buff), telapsed));
    widget_set_text_utf8(duration, player_format_time(buff, sizeof(buff), tduration));

    widget_set_value_without_notify(lrc, telapsed);
  } else {
    widget_set_value_without_notify(play, 0);
  }

  return RET_REPEAT;
}

ret_t player_hook_children(widget_t* widget) {
  media_player_t* player = media_player();
  play_list_t* play_list = WIDGET_GET_PLAY_LIST(widget);
  widget_t* volume = widget_lookup(widget, WIDGET_NAME_VOLUME, TRUE);

  widget_child_on(widget, WIDGET_NAME_NEXT, EVT_CLICK, player_on_next, play_list);
  widget_child_on(widget, WIDGET_NAME_PREV, EVT_CLICK, player_on_prev, play_list);
  widget_child_on(widget, WIDGET_NAME_PLAY, EVT_VALUE_CHANGED, player_on_play_or_pause, play_list);
  widget_child_on(widget, WIDGET_NAME_MUTE, EVT_VALUE_CHANGED, player_on_mute_changed, play_list);
  widget_child_on(widget, WIDGET_NAME_MODE, EVT_VALUE_CHANGED, player_on_mode_changed, play_list);
  widget_child_on(widget, WIDGET_NAME_PROGRESS, EVT_VALUE_CHANGED, player_on_progress_changed,
                  NULL);
  widget_child_on(widget, WIDGET_NAME_LRC, EVT_VALUE_CHANGED, player_on_progress_changed, NULL);

  if (volume != NULL) {
    uint32_t v = media_player_get_volume(player);
    widget_set_prop_int(volume, WIDGET_PROP_MAX, MEDIA_PLAYER_MAX_VOLUME);
    widget_set_value_without_notify(volume, v);
    widget_on(volume, EVT_VALUE_CHANGED, player_on_volume_changed, play_list);
  }

  return RET_OK;
}
