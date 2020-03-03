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

static ret_t player_on_play_or_pause(widget_t* widget, event_t* e) {
  log_debug("player_on_play_or_pause\n");
  return RET_OK;
}

static ret_t player_on_prev(widget_t* widget, event_t* e) {
  log_debug("prev\n");
  return RET_OK;
}

static ret_t player_on_next(widget_t* widget, event_t* e) {
  log_debug("next\n");
  return RET_OK;
}

static ret_t player_on_mute_changed(widget_t* widget, event_t* e) {
  log_debug("mute changed\n");
  return RET_OK;
}

static ret_t player_on_mode_changed(widget_t* widget, event_t* e) {
  log_debug("mode changed\n");
  return RET_OK;
}

static ret_t player_on_progress_changed(widget_t* widget, event_t* e) {
  log_debug("progress changed\n");
  return RET_OK;
}

static ret_t audio_view_hook_children(widget_t* widget) {
  widget_child_on(widget, "next", EVT_CLICK, player_on_next, widget);
  widget_child_on(widget, "prev", EVT_CLICK, player_on_prev, widget);
  widget_child_on(widget, "play", EVT_VALUE_CHANGED, player_on_play_or_pause, widget);
  widget_child_on(widget, "mute", EVT_VALUE_CHANGED, player_on_mute_changed, widget);
  widget_child_on(widget, "mode", EVT_VALUE_CHANGED, player_on_mode_changed, widget);
  widget_child_on(widget, "progress", EVT_VALUE_CHANGED, player_on_progress_changed, widget);

  return RET_OK;
}

static ret_t audio_view_on_event(widget_t* widget, event_t* e) {
  switch (e->type) {
    case EVT_WINDOW_WILL_OPEN: {
      audio_view_hook_children(widget);
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
  return widget_create(parent, TK_REF_VTABLE(audio_view), x, y, w, h);
}

widget_t* audio_view_cast(widget_t* widget) {
  return_value_if_fail(WIDGET_IS_INSTANCE_OF(widget, audio_view), NULL);

  return widget;
}

#include "base/widget_factory.h"

ret_t audio_view_register(void) {
  return widget_factory_register(widget_factory(), WIDGET_TYPE_AUDIO_VIEW, audio_view_create);
}
