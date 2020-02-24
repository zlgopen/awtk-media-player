/**
 * File:   media_player_event.h
 * Author: AWTK Develop Team
 * Brief:  media_player_event
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
 * ===============================================================
 * 2020-02-19 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_MEDIA_PLAYER_EVENT_H
#define TK_MEDIA_PLAYER_EVENT_H

#include "tkc/event.h"
#include "base/bitmap.h"

BEGIN_C_DECLS

/**
 * @enum media_player_event_t
 * @prefix MEDIA_PLAYER_
 * 媒体播放器的事件。
 */
typedef enum _media_player_event_t {
  /**
   * @const EVT_MEDIA_PLAYER_LOADED
   * 加载事件(media_player_loaded_event_t)。
   */
  EVT_MEDIA_PLAYER_LOADED = 1024,

  /**
   * @const EVT_MEDIA_PLAYER_PAUSED
   * 暂停状态。
   */
  EVT_MEDIA_PLAYER_PAUSED,

  /**
   * @const EVT_MEDIA_PLAYER_DONE
   * 播放状态。
   */
  EVT_MEDIA_PLAYER_DONE
} media_player_event_t;

/**
 * @class media_player_loaded_event_t
 * @parent event_t
 * 媒体播放器接口。
 */
typedef struct _media_player_loaded_event_t {
  event_t e;
  /**
   * @property {bool_t} has_audio
   * @annotation ["readable"]
   * 是否有音频。
   */
  bool_t has_audio;
  /**
   * @property {bool_t} has_video
   * @annotation ["readable"]
   * 是否有视频。
   */
  bool_t has_video;
  /**
   * @property {bool_t} has_subtitle
   * @annotation ["readable"]
   * 是否有字幕。
   */
  bool_t has_subtitle;
  /**
   * @property {uint32_t} duration
   * @annotation ["readable"]
   * 时长(ms)。
   */
  uint32_t duration;
  /**
   * @property {uint32_t} video_width
   * @annotation ["readable"]
   * 视频宽度。
   */
  uint32_t video_width;
  /**
   * @property {uint32_t} video_height
   * @annotation ["readable"]
   * 视频高度。
   */
  uint32_t video_height;

  /**
   * @property {uint32_t} display_aspect_ratio_w
   * @annotation ["readable"]
   * display aspect ratio width。
   */
  uint32_t display_aspect_ratio_w;

  /**
   * @property {uint32_t} display_aspect_ratio_h
   * @annotation ["readable"]
   * display aspect ratio width。
   */
  uint32_t display_aspect_ratio_h;
} media_player_loaded_event_t;

/**
 * @method media_player_loaded_event_init
 * 初始化。
 *
 * @param {media_player_loaded_event_t*} edia_player_loaded_event edia_player_loaded_event对象。
 * @param {bool_t} has_audio 是否有音频。
 * @param {bool_t} has_video 是否有视频。
 * @param {bool_t} has_subtitle 是否有字幕。
 * @param {uint32_t} duration 时长(ms)。
 *
 * @return {event_t*} 返回event_t对象。
 */
event_t* media_player_loaded_event_init(media_player_loaded_event_t* event, bool_t has_audio,
                                        bool_t has_video, bool_t has_subtitle, uint32_t duration,
                                        uint32_t video_width, uint32_t video_height);

/**
 * @method media_player_loaded_event_cast
 * @annotation ["cast", "scriptable"]
 * 把event对象转media_player_loaded_event_t对象，主要给脚本语言使用。
 * @param {event_t*} event event对象。
 *
 * @return {media_player_loaded_event_t*}  返回event对象。
 */
media_player_loaded_event_t* media_player_loaded_event_cast(event_t* event);

END_C_DECLS

#endif /*TK_MEDIA_PLAYER_EVENT_H*/
