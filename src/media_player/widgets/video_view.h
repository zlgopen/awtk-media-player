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

#ifndef TK_VIDEO_VIEW_H
#define TK_VIDEO_VIEW_H

#include "base/widget.h"
#include "media_player/lrc/lrc.h"
#include "media_player/base/play_list.h"
#include "media_player/base/media_player.h"

BEGIN_C_DECLS

/**
 * @class video_view_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 音频播放控件。
 *
 * video_view\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于video_view\_t控件。
 *
 * 在xml中使用"video_view"标签创建video_view。如：
 *
 * ```xml
 *  <video_view x="0" y="0" w="100%" h="100%" ">
 *  </video_view>
 * ```
 *
 * 可用通过style来设置控件的显示风格，如背景颜色等。如：
 *
 * ```xml
 * <style name="default" border_color="#a0a0a0">
 *   <normal     bg_color="#f0f0f0" />
 * </style>
 * ```
 */
typedef struct _video_view_t {
  widget_t widget;

  /**
   * @property {play_list_t*} play_list
   * @annotation ["readable"]
   * 播放列表对象。
   */
  play_list_t* play_list;

  /*private*/
  uint32_t timer_id;
  media_info_t media_info;
} video_view_t;

/**
 * @method video_view_create
 * 创建video_view对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* video_view_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method video_view_cast
 * 转换为video_view对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget video_view对象。
 *
 * @return {widget_t*} video_view对象。
 */
widget_t* video_view_cast(widget_t* widget);

/**
 * @method video_view_get_play_list
 * 获取播放列表。
 * @param {widget_t*} widget video_view对象。
 *
 * @return {play_list_t*} 返回播放列表。
 */
play_list_t* video_view_get_play_list(widget_t* widget);

#define WIDGET_TYPE_VIDEO_VIEW "video_view"

#define VIDEO_VIEW(widget) ((video_view_t*)(video_view_cast(WIDGET(widget))))

ret_t video_view_register(void);

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(video_view);

END_C_DECLS

#endif /*TK_VIDEO_VIEW_H*/
