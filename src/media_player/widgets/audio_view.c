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
#include "tkc/path.h"
#include "media_player/widgets/lrc_view.h"
#include "media_player/widgets/audio_view.h"
#include "media_player/widgets/player_common.h"

static ret_t audio_view_on_event(widget_t* widget, event_t* e) {
  switch (e->type) {
    case EVT_WINDOW_WILL_OPEN: {
      player_hook_children(widget);
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
  } else if (tk_str_eq(name, WIDGET_PROP_PLAY_LIST)) {
    value_set_pointer(v, audio_view->play_list);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

ret_t audio_view_set_lrc(widget_t* widget, lrc_t* lrc) {
  widget_t* lrc_widget = NULL;
  audio_view_t* audio_view = AUDIO_VIEW(widget);
  return_value_if_fail(widget != NULL, RET_BAD_PARAMS);

  if (audio_view->lrc != NULL) {
    lrc_destroy(audio_view->lrc);
  }
  audio_view->lrc = lrc;

  lrc_widget = widget_lookup(widget, WIDGET_NAME_LRC, TRUE);
  if (lrc_widget != NULL) {
    lrc_view_set_lrc(lrc_widget, lrc);
  }

  return RET_OK;
}

static ret_t audio_view_set_prop(widget_t* widget, const char* name, const value_t* v) {
  audio_view_t* audio_view = AUDIO_VIEW(widget);
  return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(name, WIDGET_PROP_TEXT)) {
  } else if (tk_str_eq(name, WIDGET_PROP_LRC)) {
    audio_view_set_lrc(widget, (lrc_t*)value_pointer(v));
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

  audio_view->timer_id = timer_add(player_on_update_timer, audio_view, 500);
  audio_view->play_list = play_list_create();
  media_player_set_on_event(media_player(), player_on_media_player_event, audio_view);

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
