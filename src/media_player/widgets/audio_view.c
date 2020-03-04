/**
 * File:   audio_view.h
 * Author: AWTK Develop Team
 * Brief:  audio_view
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
 * 2020-03-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "media_player/widgets/audio_view.h"

static ret_t play_list_play(play_list_t* play_list) {
  media_player_t* player = media_player();
  const char* song = play_list_curr(play_list);
  return_value_if_fail(song != NULL, RET_BAD_PARAMS);
  media_player_load(player, song);

  return media_player_start(player);
}

static ret_t player_on_play_or_pause(void* ctx, event_t* e) {
  media_player_t* player = media_player();
  play_list_t* play_list = (play_list_t*)(ctx);
  return_value_if_fail(play_list != NULL && player != NULL, RET_BAD_PARAMS);

  media_player_state_t state = media_player_get_state(player);

  if (state == MEDIA_PLAYER_PLAYING) {
    media_player_start(player);
  } else if (state == MEDIA_PLAYER_PLAYING) {
    media_player_pause(player);
  } else {
    play_list_play(play_list);
  }

  return RET_OK;
}

static ret_t player_on_prev(void* ctx, event_t* e) {
  play_list_t* play_list = (play_list_t*)(ctx);

  return_value_if_fail(play_list_next(play_list) == RET_OK, RET_BAD_PARAMS);
  return play_list_play(play_list);
}

static ret_t player_on_next(void* ctx, event_t* e) {
  play_list_t* play_list = (play_list_t*)(ctx);

  return_value_if_fail(play_list_next(play_list) == RET_OK, RET_BAD_PARAMS);
  return play_list_play(play_list);
}

static ret_t player_idle_next(const idle_info_t* info) {
  play_list_t* play_list = (play_list_t*)(info->ctx);

  return_value_if_fail(play_list_next(play_list) == RET_OK, RET_BAD_PARAMS);

  return play_list_play(play_list);
}

static ret_t audio_view_on_media_player_event(void* ctx, event_t* e) {
  audio_view_t* audio_view = AUDIO_VIEW(ctx);

  switch (e->type) {
    case EVT_MEDIA_PLAYER_LOADED: {
      media_player_loaded_event_t* evt = media_player_loaded_event_cast(e);
      log_debug("w=%u h=%u duration=%u\n", evt->video_width, evt->video_height, evt->duration);
      break;
    }
    case EVT_MEDIA_PLAYER_PAUSED: {
      log_debug("paused\n");
      break;
    }
    case EVT_MEDIA_PLAYER_DONE: {
      log_debug("done\n");
      idle_add(player_idle_next, audio_view->play_list);
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
  log_debug("progress changed\n");
  return RET_OK;
}

static ret_t player_on_volume_changed(void* ctx, event_t* e) {
  widget_t* target = WIDGET(e->target);
  uint32_t volume = widget_get_value(target);

  return media_player_set_volume(media_player(), volume);
}

static ret_t widget_set_value_without_notify(widget_t* widget, uint32_t value) {
  emitter_disable(widget->emitter);
  widget_set_value(widget, value);
  emitter_enable(widget->emitter);

  return RET_OK;
}

static ret_t audio_view_update_timer(const timer_info_t* info) {
  widget_t* widget = WIDGET(info->ctx);
  widget_t* play = widget_lookup(widget, "play", TRUE);
  widget_t* progress = widget_lookup(widget, "progress", TRUE);
  media_player_t* player = media_player();
  media_player_state_t state = media_player_get_state(player);
  bool_t paused = (bool_t)widget_get_value(play);

  if (state == MEDIA_PLAYER_PLAYING) {
    uint32_t offset = media_player_get_position(player);
    uint32_t duration = media_player_get_duration(player);

    widget_set_value_without_notify(play, 1);
    widget_set_value_without_notify(progress, offset);
    widget_set_prop_int(progress, WIDGET_PROP_MAX, duration);
  } else {
    widget_set_value_without_notify(play, 0);
  }

  return RET_REPEAT;
}

static ret_t audio_view_hook_children(widget_t* widget, play_list_t* play_list) {
  media_player_t* player = media_player();
  widget_t* volume = widget_lookup(widget, "volume", TRUE);

  widget_child_on(widget, "next", EVT_CLICK, player_on_next, play_list);
  widget_child_on(widget, "prev", EVT_CLICK, player_on_prev, play_list);
  widget_child_on(widget, "play", EVT_VALUE_CHANGED, player_on_play_or_pause, play_list);
  widget_child_on(widget, "mute", EVT_VALUE_CHANGED, player_on_mute_changed, play_list);
  widget_child_on(widget, "mode", EVT_VALUE_CHANGED, player_on_mode_changed, play_list);
  widget_child_on(widget, "progress", EVT_VALUE_CHANGED, player_on_progress_changed, play_list);

  if (volume != NULL) {
    uint32_t v = media_player_get_volume(player);
    widget_set_prop_int(volume, WIDGET_PROP_MAX, MEDIA_PLAYER_MAX_VOLUME);
    widget_set_value_without_notify(volume, v);
    widget_on(volume, EVT_VALUE_CHANGED, player_on_volume_changed, play_list);
  }

  return RET_OK;
}

static ret_t audio_view_on_event(widget_t* widget, event_t* e) {
  audio_view_t* audio_view = AUDIO_VIEW(widget);
  switch (e->type) {
    case EVT_WINDOW_WILL_OPEN: {
      audio_view_hook_children(widget, audio_view->play_list);
      break;
    }
    case EVT_WINDOW_OPEN: {
      break;
    }
    case EVT_WINDOW_CLOSE: {
      break;
    }
    default:
      break;
  }

  return RET_OK;
}

static ret_t audio_view_get_prop(widget_t* widget, const char* name, value_t* v) {
  audio_view_t* audio_view = AUDIO_VIEW(widget);
  return_value_if_fail(audio_view != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(name, WIDGET_PROP_TEXT)) {
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t audio_view_set_prop(widget_t* widget, const char* name, const value_t* v) {
  audio_view_t* audio_view = AUDIO_VIEW(widget);
  return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(name, WIDGET_PROP_TEXT)) {
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t audio_view_on_destroy(widget_t* widget) {
  audio_view_t* audio_view = AUDIO_VIEW(widget);

  media_player_set_on_event(media_player(), NULL, NULL);
  play_list_destroy(audio_view->play_list);
  if (audio_view->lrc != NULL) {
    lrc_destroy(audio_view->lrc);
  }

  return RET_OK;
}

TK_DECL_VTABLE(audio_view) = {.size = sizeof(audio_view_t),
                              .type = WIDGET_TYPE_AUDIO_VIEW,
                              .parent = TK_PARENT_VTABLE(widget),
                              .set_prop = audio_view_set_prop,
                              .get_prop = audio_view_get_prop,
                              .on_event = audio_view_on_event,
                              .create = audio_view_create,
                              .on_destroy = audio_view_on_destroy};

widget_t* audio_view_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h) {
  widget_t* widget = widget_create(parent, TK_REF_VTABLE(audio_view), x, y, w, h);
  audio_view_t* audio_view = AUDIO_VIEW(widget);
  return_value_if_fail(audio_view != NULL, NULL);

  audio_view->timer_id = timer_add(audio_view_update_timer, audio_view, 500);
  audio_view->play_list = play_list_create();
  media_player_set_on_event(media_player(), audio_view_on_media_player_event, audio_view);

  return widget;
}

widget_t* audio_view_cast(widget_t* widget) {
  return_value_if_fail(WIDGET_IS_INSTANCE_OF(widget, audio_view), NULL);

  return widget;
}

play_list_t* audio_view_get_play_list(widget_t* widget) {
  audio_view_t* audio_view = AUDIO_VIEW(widget);
  return_value_if_fail(audio_view != NULL, NULL);

  return audio_view->play_list;
}

#include "base/widget_factory.h"

ret_t audio_view_register(void) {
  return widget_factory_register(widget_factory(), WIDGET_TYPE_AUDIO_VIEW, audio_view_create);
}
