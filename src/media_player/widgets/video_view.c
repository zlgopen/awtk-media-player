/**
 * File:   video_view.h
 * Author: AWTK Develop Team
 * Brief:  video_view
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
 * 2020-03-06 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/path.h"
#include "mutable_image/mutable_image.h"
#include "media_player/widgets/video_view.h"
#include "media_player/widgets/player_common.h"

static bitmap_t* mutable_image_create_image(void* ctx, bitmap_format_t format,
                                            bitmap_t* old_image) {
  bitmap_t* image = old_image;
  widget_t* widget = WIDGET(ctx);
  media_player_t* player = media_player();
  widget_t* mutable = widget_lookup(widget, WIDGET_NAME_MUTABLE_IMAGE, TRUE);

  if (media_player_get_state(player) == MEDIA_PLAYER_PLAYING) {
    uint32_t ww = mutable->w;
    uint32_t wh = mutable->h;
    uint32_t vw = media_player_get_video_width(player);
    uint32_t vh = media_player_get_video_height(player);
    if (vw > 0 && vh > 0 && ww > 0 && wh > 0) {
      double scale_w = (double)ww / (double)vw;
      double scale_h = (double)wh / (double)vh;
      double scale = tk_min(scale_w, scale_h);

      uint32_t iw = vw * scale;
      uint32_t ih = vh * scale;

      if (old_image != NULL) {
        if (old_image->w != iw || old_image->h != ih) {
          bitmap_destroy(old_image);
          old_image = NULL;
        }
      }

      if (old_image == NULL) {
        image = bitmap_create_ex(iw, ih, 0, format);
      }
    }
  }

  return image;
}

static ret_t mutable_image_prepare_image(void* ctx, bitmap_t* image) {
  media_player_t* player = media_player();

  if (media_player_get_state(player) == MEDIA_PLAYER_PLAYING) {
    return media_player_get_video_frame(player, image);
  }

  return RET_OK;
}

static ret_t video_view_on_event(widget_t* widget, event_t* e) {
  widget_t* mutable = widget_lookup(widget, WIDGET_NAME_MUTABLE_IMAGE, TRUE);
  switch (e->type) {
    case EVT_WINDOW_WILL_OPEN: {
      media_player_t* player = player_get(widget);
      player_hook_children(widget);
      return_value_if_fail(player != NULL, RET_BAD_PARAMS);
      return_value_if_fail(mutable != NULL, RET_BAD_PARAMS);
      mutable_image_set_prepare_image(mutable, mutable_image_prepare_image, widget);
      mutable_image_set_create_image(mutable, mutable_image_create_image, widget);
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

static ret_t video_view_get_prop(widget_t* widget, const char* name, value_t* v) {
  video_view_t* video_view = VIDEO_VIEW(widget);
  return_value_if_fail(video_view != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(name, WIDGET_PROP_PLAY_LIST)) {
    value_set_pointer(v, video_view->play_list);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t video_view_set_prop(widget_t* widget, const char* name, const value_t* v) {
  return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  return RET_NOT_FOUND;
}

static ret_t video_view_on_destroy(widget_t* widget) {
  video_view_t* video_view = VIDEO_VIEW(widget);
  media_player_t* player = media_player();

  media_player_stop(player);
  media_player_set_on_event(player, NULL, NULL);
  play_list_destroy(video_view->play_list);

  return RET_OK;
}

TK_DECL_VTABLE(video_view) = {.size = sizeof(video_view_t),
                              .type = WIDGET_TYPE_VIDEO_VIEW,
                              .parent = TK_PARENT_VTABLE(widget),
                              .set_prop = video_view_set_prop,
                              .get_prop = video_view_get_prop,
                              .on_event = video_view_on_event,
                              .create = video_view_create,
                              .on_destroy = video_view_on_destroy};

widget_t* video_view_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h) {
  widget_t* widget = widget_create(parent, TK_REF_VTABLE(video_view), x, y, w, h);
  video_view_t* video_view = VIDEO_VIEW(widget);
  media_player_t* player = media_player();
  return_value_if_fail(video_view != NULL, NULL);

  player_set(widget, player);
  video_view->timer_id = timer_add(player_on_update_timer, video_view, 500);
  video_view->play_list = play_list_create();
  media_player_set_on_event(player, player_on_media_player_event, video_view);

  return widget;
}

widget_t* video_view_cast(widget_t* widget) {
  return_value_if_fail(WIDGET_IS_INSTANCE_OF(widget, video_view), NULL);

  return widget;
}

play_list_t* video_view_get_play_list(widget_t* widget) {
  video_view_t* video_view = VIDEO_VIEW(widget);
  return_value_if_fail(video_view != NULL, NULL);

  return video_view->play_list;
}

#include "base/widget_factory.h"

ret_t video_view_register(void) {
  return widget_factory_register(widget_factory(), WIDGET_TYPE_VIDEO_VIEW, video_view_create);
}
