/**
 * File:   lrc_view.c
 * Author: AWTK Develop Team
 * Brief:  a view to display lyric
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
 * 2020-03-02 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/utils.h"

#include "lrc_view.h"
#include "widget_animators/widget_animator_scroll.h"

static ret_t lrc_view_get_prop(widget_t* widget, const char* name, value_t* v) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  return_value_if_fail(lrc_view != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(name, WIDGET_PROP_XOFFSET)) {
    value_set_int(v, 0);
    return RET_OK;
  } else if (tk_str_eq(name, WIDGET_PROP_YOFFSET)) {
    value_set_int(v, lrc_view->yoffset);
    return RET_OK;
  } else if (tk_str_eq(name, WIDGET_PROP_VALUE)) {
    value_set_int(v, lrc_view->current_time);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t lrc_view_set_prop(widget_t* widget, const char* name, const value_t* v) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(name, WIDGET_PROP_YOFFSET)) {
    lrc_view->yoffset = value_int(v);
    return RET_OK;
  } else if (tk_str_eq(name, WIDGET_PROP_XOFFSET)) {
    return RET_OK;
  } else if (tk_str_eq(name, WIDGET_PROP_VALUE)) {
    return lrc_view_set_current_time(widget, value_uint32(v));
  }

  return RET_NOT_FOUND;
}

static ret_t lrc_view_on_destroy(widget_t* widget) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  return_value_if_fail(widget != NULL && lrc_view != NULL, RET_BAD_PARAMS);

  return RET_OK;
}

static ret_t lrc_view_paint_self(widget_t* widget, canvas_t* c) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  style_t* style = widget->astyle;
  lrc_t* lrc = lrc_view->lrc;
  lrc_time_tag_list_t* time_tags = lrc->time_tags;

  rect_t r;
  int32_t i = 0;
  int32_t y = 0;
  int32_t yoffset = lrc_view->yoffset;
  uint32_t current_time = lrc_view->current_time;
  int32_t margin = style_get_int(style, STYLE_ID_MARGIN, 5);
  int32_t spacer = style_get_int(style, STYLE_ID_SPACER, 2);
  int32_t margin_top = style_get_int(style, STYLE_ID_MARGIN_TOP, margin);
  int32_t margin_bottom = style_get_int(style, STYLE_ID_MARGIN_BOTTOM, margin);
  int32_t margin_left = style_get_int(style, STYLE_ID_MARGIN_LEFT, margin);
  int32_t margin_right = style_get_int(style, STYLE_ID_MARGIN_RIGHT, margin);
  int32_t align_h = style_get_int(style, STYLE_ID_TEXT_ALIGN_H, ALIGN_H_CENTER);
  int32_t font_size = style_get_int(style, STYLE_ID_FONT_SIZE, TK_DEFAULT_FONT_SIZE);
  int32_t current_font_size = style_get_int(style, STYLE_ID_HIGHLIGHT_FONT_SIZE, font_size);
  const char* font_name = style_get_str(style, STYLE_ID_FONT_NAME, NULL);
  const char* current_font_name = style_get_str(style, STYLE_ID_HIGHLIGHT_FONT_NAME, NULL);
  int32_t w = widget->w - margin_left - margin_right;
  int32_t h = widget->h - margin_top - margin_bottom;
  color_t black = color_init(0, 0, 0, 0xff);
  color_t text_color = style_get_color(style, STYLE_ID_TEXT_COLOR, black);
  color_t curr_text_color = style_get_color(style, STYLE_ID_HIGHLIGHT_TEXT_COLOR, black);

  y = margin_top;
  canvas_set_text_align(c, (align_h_t)align_h, ALIGN_V_MIDDLE);

  for (i = 0; i < time_tags->size; i++) {
    wstr_t* text = &(widget->text);
    lrc_time_tag_t* iter = time_tags->items + i;
    bool_t is_current = lrc_time_tag_list_is_matched(time_tags, i, current_time);

    if ((y - margin_top + font_size) >= yoffset) {
      if (is_current) {
        r = rect_init(margin_left, y - yoffset, w, current_font_size);
        canvas_set_text_color(c, curr_text_color);
        canvas_set_font(c, current_font_name, current_font_size);
      } else {
        r = rect_init(margin_left, y - yoffset, w, font_size);
        canvas_set_text_color(c, text_color);
        canvas_set_font(c, font_name, font_size);
      }

      wstr_set_utf8(text, iter->text);
      canvas_draw_text_in_rect(c, text->str, text->size, &r);
    }

    if (is_current) {
      y += current_font_size;
    } else {
      y += font_size;
    }
    y += spacer;

    if (y >= (yoffset + h)) {
      break;
    }
  }

  lrc_view->line_hight = font_size + spacer;

  return y;
}

static ret_t lrc_view_on_paint_self(widget_t* widget, canvas_t* c) {
  rect_t r_save;
  style_t* style = widget->astyle;
  lrc_view_t* lrc_view = LRC_VIEW(widget);

  if (style != NULL && lrc_view->lrc != NULL) {
    int32_t margin = style_get_int(style, STYLE_ID_MARGIN, 5);
    int32_t margin_top = style_get_int(style, STYLE_ID_MARGIN_TOP, margin);
    int32_t margin_bottom = style_get_int(style, STYLE_ID_MARGIN_BOTTOM, margin);
    int32_t margin_left = style_get_int(style, STYLE_ID_MARGIN_LEFT, margin);
    int32_t margin_right = style_get_int(style, STYLE_ID_MARGIN_RIGHT, margin);
    int32_t w = widget->w - margin_left - margin_right;
    int32_t h = widget->h - margin_top - margin_bottom;
    rect_t r = rect_init(c->ox + margin_left, c->oy + margin_top, w, h);
    return_value_if_fail(widget != NULL, RET_BAD_PARAMS);

    canvas_get_clip_rect(c, &r_save);
    r = rect_intersect(&r_save, &r);
    if (r.w > 0 && r.h > 0) {
      canvas_set_clip_rect(c, &r);
      lrc_view_paint_self(widget, c);
      canvas_set_clip_rect(c, &r_save);
    }
  }

  return RET_OK;
}

static ret_t lrc_view_on_pointer_down(lrc_view_t* lrc_view, pointer_event_t* e) {
  velocity_t* v = &(lrc_view->velocity);

  velocity_reset(v);
  lrc_view->ydown = e->y;
  lrc_view->yoffset_save = lrc_view->yoffset;

  velocity_update(v, e->e.time, e->x, e->y);

  return RET_OK;
}
static ret_t lrc_view_on_pointer_move(lrc_view_t* lrc_view, pointer_event_t* e) {
  velocity_t* v = &(lrc_view->velocity);
  int32_t dy = e->y - lrc_view->ydown;
  velocity_update(v, e->e.time, e->x, e->y);

  if (lrc_view->wa == NULL && dy) {
    lrc_view->yoffset = lrc_view->yoffset_save - dy;
  }

  return RET_OK;
}

static ret_t lrc_view_on_scroll_done(void* ctx, event_t* e) {
  lrc_view_t* lrc_view = LRC_VIEW(ctx);
  return_value_if_fail(lrc_view != NULL, RET_BAD_PARAMS);

  lrc_view->wa = NULL;

  return RET_REMOVE;
}

static int32_t lrc_view_get_content_height(widget_t* widget) {
  int32_t i = 0;
  int32_t y = 0;
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  style_t* style = widget->astyle;
  lrc_t* lrc = lrc_view->lrc;
  lrc_time_tag_list_t* time_tags = lrc->time_tags;

  uint32_t current_time = lrc_view->current_time;
  int32_t margin = style_get_int(style, STYLE_ID_MARGIN, 5);
  int32_t spacer = style_get_int(style, STYLE_ID_SPACER, 2);
  int32_t margin_top = style_get_int(style, STYLE_ID_MARGIN_TOP, margin);
  int32_t font_size = style_get_int(style, STYLE_ID_FONT_SIZE, TK_DEFAULT_FONT_SIZE);
  int32_t current_font_size = style_get_int(style, STYLE_ID_HIGHLIGHT_FONT_SIZE, font_size);

  y = margin_top;
  for (i = 0; i < time_tags->size; i++) {
    if (lrc_time_tag_list_is_matched(time_tags, i, current_time)) {
      y += current_font_size;
    } else {
      y += font_size;
    }
    y += spacer;
  }

  return y;
}

static ret_t lrc_view_scroll_to(widget_t* widget, int32_t yoffset_end) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  int32_t yoffset = lrc_view->yoffset;
  int32_t content_h = lrc_view_get_content_height(widget);

  if (lrc_view->yoffset == yoffset_end) {
    return RET_OK;
  }

  if (yoffset_end < 0) {
    yoffset_end = 0;
  }

  if (yoffset_end > content_h) {
    yoffset_end = content_h - widget->h / 2;
  }

  lrc_view->wa = widget_animator_scroll_create(widget, TK_ANIMATING_TIME, 0, EASING_SIN_INOUT);
  return_value_if_fail(lrc_view->wa != NULL, RET_OOM);

  widget_animator_scroll_set_params(lrc_view->wa, 0, yoffset, 0, yoffset_end);
  widget_animator_on(lrc_view->wa, EVT_ANIM_END, lrc_view_on_scroll_done, lrc_view);
  widget_animator_start(lrc_view->wa);

  return RET_OK;
}

static ret_t lrc_view_set_current_time_by_y(widget_t* widget, int32_t pointer_y) {
  int32_t i = 0;
  int32_t y = 0;
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  style_t* style = widget->astyle;
  lrc_t* lrc = lrc_view->lrc;

  lrc_time_tag_list_t* time_tags = lrc->time_tags;
  uint32_t current_time = lrc_view->current_time;
  int32_t margin = style_get_int(style, STYLE_ID_MARGIN, 5);
  int32_t spacer = style_get_int(style, STYLE_ID_SPACER, 2);
  int32_t margin_top = style_get_int(style, STYLE_ID_MARGIN_TOP, margin);
  int32_t font_size = style_get_int(style, STYLE_ID_FONT_SIZE, TK_DEFAULT_FONT_SIZE);
  int32_t current_font_size = style_get_int(style, STYLE_ID_HIGHLIGHT_FONT_SIZE, font_size);

  y = margin_top;
  pointer_y += lrc_view->yoffset;
  for (i = 0; i < time_tags->size; i++) {
    int32_t line_height = 0;

    if (lrc_time_tag_list_is_matched(time_tags, i, current_time)) {
      line_height += current_font_size;
    } else {
      line_height += font_size;
    }
    line_height += spacer;

    if (pointer_y >= y && pointer_y <= (y + line_height)) {
      lrc_view_set_current_time(widget, time_tags->items[i].timestamp);
      break;
    } else {
      y += line_height;
    }
  }

  return RET_OK;

  return RET_OK;
}

static ret_t lrc_view_on_pointer_up(lrc_view_t* lrc_view, pointer_event_t* e) {
  int32_t yoffset_end = 0;
  widget_t* widget = WIDGET(lrc_view);
  velocity_t* v = &(lrc_view->velocity);

  velocity_update(v, e->e.time, e->x, e->y);
  yoffset_end = lrc_view->yoffset - v->yv;

  if (e->y == lrc_view->ydown) {
    point_t p = {e->x, e->y};
    widget_to_local(widget, &p);
    lrc_view_set_current_time_by_y(widget, p.y);
  }

  lrc_view_scroll_to(widget, yoffset_end);

  return RET_OK;
}

static ret_t lrc_view_up(widget_t* widget) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);

  return lrc_view_scroll_to(widget, lrc_view->yoffset - lrc_view->line_hight);
}

static ret_t lrc_view_down(widget_t* widget) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);

  return lrc_view_scroll_to(widget, lrc_view->yoffset + lrc_view->line_hight);
}

static ret_t lrc_view_on_event(widget_t* widget, event_t* e) {
  ret_t ret = RET_OK;
  uint16_t type = e->type;
  lrc_view_t* lrc_view = LRC_VIEW(widget);

  switch (type) {
    case EVT_POINTER_DOWN:
      lrc_view->pressed = TRUE;
      widget_grab(widget->parent, widget);
      lrc_view_on_pointer_down(lrc_view, (pointer_event_t*)e);
      break;
    case EVT_POINTER_UP: {
      lrc_view->pressed = FALSE;
      lrc_view_on_pointer_up(lrc_view, (pointer_event_t*)e);
      widget_ungrab(widget->parent, widget);
      break;
    }
    case EVT_POINTER_DOWN_ABORT: {
      lrc_view->pressed = FALSE;
      lrc_view->yoffset = lrc_view->yoffset_save;
      break;
    }
    case EVT_KEY_DOWN: {
      key_event_t* evt = (key_event_t*)e;
      if (evt->key == TK_KEY_UP) {
        lrc_view_up(widget);
      } else if (evt->key == TK_KEY_DOWN) {
        lrc_view_down(widget);
      }
      break;
    }
    case EVT_POINTER_MOVE: {
      pointer_event_t* evt = (pointer_event_t*)e;
      if (evt->pressed && lrc_view->pressed) {
        lrc_view_on_pointer_move(lrc_view, evt);
        widget_invalidate(widget, NULL);
        ret = RET_STOP;
      }
      break;
    }
    case EVT_WHEEL: {
      wheel_event_t* evt = (wheel_event_t*)e;

      if (evt->dy > 0) {
        lrc_view_down(widget);
      } else if (evt->dy < 0) {
        lrc_view_up(widget);
      }

      ret = RET_STOP;
    }
    case EVT_RESIZE:
    case EVT_MOVE_RESIZE: {
      break;
    }
    default:
      break;
  }

  return ret;
}

const char* s_lrc_view_properties[] = {NULL};

TK_DECL_VTABLE(lrc_view) = {.size = sizeof(lrc_view_t),
                            .type = WIDGET_TYPE_LRC_VIEW,
                            .clone_properties = s_lrc_view_properties,
                            .persistent_properties = s_lrc_view_properties,
                            .parent = TK_PARENT_VTABLE(widget),
                            .create = lrc_view_create,
                            .on_paint_self = lrc_view_on_paint_self,
                            .set_prop = lrc_view_set_prop,
                            .get_prop = lrc_view_get_prop,
                            .on_event = lrc_view_on_event,
                            .on_destroy = lrc_view_on_destroy};

widget_t* lrc_view_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h) {
  widget_t* widget = widget_create(parent, TK_REF_VTABLE(lrc_view), x, y, w, h);
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  return_value_if_fail(lrc_view != NULL, NULL);

  lrc_view->line_hight = 20;
  lrc_view->current_time = 2000;

  return widget;
}

widget_t* lrc_view_cast(widget_t* widget) {
  return_value_if_fail(WIDGET_IS_INSTANCE_OF(widget, lrc_view), NULL);

  return widget;
}

static ret_t lrc_view_ensure_current_visible(widget_t* widget) {
  int32_t i = 0;
  int32_t y = 0;
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  style_t* style = widget->astyle;
  lrc_t* lrc = lrc_view->lrc;
  lrc_time_tag_list_t* time_tags = lrc->time_tags;

  int32_t yoffset = lrc_view->yoffset;
  uint32_t current_time = lrc_view->current_time;
  int32_t margin = style_get_int(style, STYLE_ID_MARGIN, 5);
  int32_t spacer = style_get_int(style, STYLE_ID_SPACER, 2);
  int32_t margin_top = style_get_int(style, STYLE_ID_MARGIN_TOP, margin);
  int32_t margin_bottom = style_get_int(style, STYLE_ID_MARGIN_BOTTOM, margin);
  int32_t h = widget->h - margin_top - margin_bottom;
  int32_t font_size = style_get_int(style, STYLE_ID_FONT_SIZE, TK_DEFAULT_FONT_SIZE);
  int32_t current_font_size =
      style_get_int(style, STYLE_ID_HIGHLIGHT_FONT_SIZE, TK_DEFAULT_FONT_SIZE);

  y = margin_top;
  for (i = 0; i < time_tags->size; i++) {
    if (lrc_time_tag_list_is_matched(time_tags, i, current_time)) {
      uint32_t bottom = yoffset + h - current_font_size;

      if (y < yoffset) {
        lrc_view_scroll_to(widget, y);
      } else if (y > bottom) {
        int32_t delta = y - bottom;
        if (delta < current_font_size * 2) {
          delta = current_font_size * 2;
        }
        lrc_view_scroll_to(widget, lrc_view->yoffset + delta);
      }

      break;
    } else {
      y += font_size;
    }
    y += spacer;
  }

  return RET_OK;
}

ret_t lrc_view_set_current_time(widget_t* widget, uint32_t current_time) {
  int32_t current_index = 0;
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  return_value_if_fail(lrc_view != NULL, RET_BAD_PARAMS);

  if (lrc_view->lrc != NULL) {
    if (lrc_view->current_time != current_time) {
      widget_dispatch_simple_event(widget, EVT_VALUE_WILL_CHANGE);
      lrc_view->current_time = current_time;
      widget_dispatch_simple_event(widget, EVT_VALUE_CHANGED);
    }

    current_index = lrc_time_tag_list_find_index(lrc_view->lrc->time_tags, current_time);
    if (lrc_view->current_index != current_index) {
      widget_invalidate(widget, NULL);
      if (current_time < 1000) {
        lrc_view->yoffset = 0;
      } else {
        lrc_view_ensure_current_visible(widget);
      }
    }
  }

  return RET_OK;
}

ret_t lrc_view_set_lrc(widget_t* widget, lrc_t* lrc) {
  lrc_view_t* lrc_view = LRC_VIEW(widget);
  return_value_if_fail(lrc_view != NULL, RET_BAD_PARAMS);

  lrc_view->lrc = lrc;
  lrc_view->current_time = 0;
  lrc_view->current_index = 0;
  widget_invalidate(widget, NULL);

  return RET_OK;
}

#include "base/widget_factory.h"

ret_t lrc_view_register(void) {
  return widget_factory_register(widget_factory(), WIDGET_TYPE_LRC_VIEW, lrc_view_create);
}
