/**
 * File:   lrc_view.h
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

#ifndef TK_LRC_VIEW_H
#define TK_LRC_VIEW_H

#include "base/widget.h"
#include "base/velocity.h"
#include "base/widget_animator.h"
#include "media_player/lrc/lrc.h"

BEGIN_C_DECLS
/**
 * @class lrc_view_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 歌词显示控件。
 *
 * lrc\_view\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于lrc\_view\_t控件。
 *
 * 在xml中使用"lrc\_view"标签创建歌词显示控件。如：
 *
 * ```xml
 * <lrc_view x="c" y="m" w="80" h="30"/>
 * ```
 *
 * 在c代码中使用函数lrc\_view\_create创建歌词显示控件。如：
 *
 * ```c
 *  widget_t* lrc_view = lrc_view_create(win, 10, 10, 128, 30);
 * ```
 *
 * 可用通过style来设置控件的显示风格，如字体的大小和颜色等等。如：
 *
 * ```xml
 * <lrc_view>
 * <style highlight_text_color="red" text_color="black" text_align_h="center">
 *   <normal />
 * </style>
 * </lrc_view>
 * ```
 */
typedef struct _lrc_view_t {
  widget_t widget;

  /*private*/
  lrc_t* lrc;
  bool_t pressed;
  int32_t ydown;
  int32_t yoffset;
  uint32_t line_hight;
  int32_t yoffset_save;
  uint32_t current_time;
  uint32_t current_index;
  widget_animator_t* wa;
  velocity_t velocity;
} lrc_view_t;

/**
 * @event {event_t} EVT_VALUE_WILL_CHANGE
 * 值(当前时间)即将改变事件。
 */

/**
 * @event {event_t} EVT_VALUE_CHANGED
 * 值(当前时间)改变事件。
 */

/**
 * @method lrc_view_create
 * @annotation ["constructor", "scriptable"]
 * 创建lrc_view对象
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* lrc_view_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method lrc_view_set_current_time
 * 设置当前时间(ms)。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget lrc_view对象。
 * @param {uint32_t} current_time 当前时间。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_view_set_current_time(widget_t* widget, uint32_t current_time);

/**
 * @method lrc_view_set_lrc
 * 设置lrc对象(调用者负责管理lrc对象的生命周期)。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget lrc_view对象。
 * @param {lrc_t*} lrc lrc对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_view_set_lrc(widget_t* widget, lrc_t* lrc);

/**
 * @method lrc_view_cast
 * 转换为lrc_view对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget lrc_view对象。
 *
 * @return {widget_t*} lrc_view对象。
 */
widget_t* lrc_view_cast(widget_t* widget);

#define WIDGET_TYPE_LRC_VIEW "lrc_view"

#define LRC_VIEW(widget) ((lrc_view_t*)(lrc_view_cast(WIDGET(widget))))

ret_t lrc_view_register(void);

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(lrc_view);

END_C_DECLS

#endif /*TK_LRC_VIEW_H*/
