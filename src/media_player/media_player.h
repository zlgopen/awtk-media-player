/**
 * File:   media_player.h
 * Author: AWTK Develop Team
 * Brief:  media_player
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
 * 2020-02-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_MEDIA_PLAYER_H
#define TK_MEDIA_PLAYER_H

#include "tkc/event.h"
#include "base/bitmap.h"
#include "media_player/media_player_event.h"

BEGIN_C_DECLS

/**
 * @enum media_player_state_t
 * @prefix MEDIA_PLAYER_
 * 媒体播放器的状态。
 */
typedef enum _media_player_state_t {
  /**
   * @const MEDIA_PLAYER_NONE
   * 无效状态。
   */
  MEDIA_PLAYER_NONE,

  /**
   * @const MEDIA_PLAYER_PAUSED
   * 暂停状态。
   */
  MEDIA_PLAYER_PAUSED,

  /**
   * @const MEDIA_PLAYER_PLAYING
   * 播放状态。
   */
  MEDIA_PLAYER_PLAYING
} media_player_state_t;

struct _media_player_t;
typedef struct _media_player_t media_player_t;

typedef ret_t (*media_player_load_t)(media_player_t* player, const char* url);
typedef ret_t (*media_player_start_t)(media_player_t* player);
typedef ret_t (*media_player_pause_t)(media_player_t* player);
typedef ret_t (*media_player_stop_t)(media_player_t* player);
typedef ret_t (*media_player_seek_t)(media_player_t* player, uint32_t offset);
typedef ret_t (*media_player_set_volume_t)(media_player_t* player, uint32_t volume);
typedef ret_t (*media_player_toggle_mute_t)(media_player_t* player);
typedef ret_t (*media_player_set_on_event_t)(media_player_t* player, event_func_t on_event,
                                             void* ctx);
typedef ret_t (*media_player_get_video_frame_t)(media_player_t* player, bitmap_t* image);
typedef ret_t (*media_player_destroy_t)(media_player_t* player);
typedef media_player_state_t (*media_player_get_state_t)(media_player_t* player);
typedef uint32_t (*media_player_get_volume_t)(media_player_t* player);
typedef uint32_t (*media_player_get_position_t)(media_player_t* player);
typedef uint32_t (*media_player_get_duration_t)(media_player_t* player);
typedef uint32_t (*media_player_get_video_width_t)(media_player_t* player);
typedef uint32_t (*media_player_get_video_height_t)(media_player_t* player);

typedef struct _media_player_vtable_t {
  media_player_load_t load;
  media_player_start_t start;
  media_player_pause_t pause;
  media_player_stop_t stop;
  media_player_seek_t seek;
  media_player_set_volume_t set_volume;
  media_player_toggle_mute_t toggle_mute;
  media_player_set_on_event_t set_on_event;
  media_player_get_video_frame_t get_video_frame;
  media_player_destroy_t destroy;
  media_player_get_state_t get_state;
  media_player_get_volume_t get_volume;
  media_player_get_position_t get_position;
  media_player_get_duration_t get_duration;
  media_player_get_video_width_t get_video_width;
  media_player_get_video_height_t get_video_height;
} media_player_vtable_t;

/**
 * @class media_player_t
 * 媒体播放器接口。
 */
struct _media_player_t {
  const media_player_vtable_t* vt;

  /**
   * @property {void*} user_data
   * @annotation ["readable"]
   * 用户数据。
   */
  void* user_data;

  /*private*/
  void* on_event_ctx;
  event_func_t on_event;
};

/**
 * @method media_player_load
 * 加载指定的文件。
 *
 * @param {media_player_t*} media_player media_player对象。
 * @param {const char*} url 文件名。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_load(media_player_t* player, const char* url);

/**
 * @method media_player_start
 * 开始播放刚加载或暂停的文件。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_start(media_player_t* player);

/**
 * @method media_player_pause
 * 暂停播放。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_pause(media_player_t* player);

/**
 * @method media_player_stop
 * 停止播放。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_stop(media_player_t* player);

/**
 * @method media_player_seek
 * 定位到指定的位置。
 *
 * @param {media_player_t*} media_player media_player对象。
 * @param {uint32_t} offset 偏移量(ms)。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_seek(media_player_t* player, uint32_t offset);

/**
 * @method media_player_set_volume
 * 设置音量。
 *
 * @param {media_player_t*} media_player media_player对象。
 * @param {uint32_t} volume 音量(0-100)。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_set_volume(media_player_t* player, uint32_t volume);

/**
 * @method media_player_toggle_mute
 * 静音开关。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_toggle_mute(media_player_t* player);

/**
 * @method media_player_set_on_event
 * 设置事件回调函数。
 *
 * @param {media_player_t*} media_player media_player对象。
 * @param {event_func_t} on_event 事件回调函数。
 * @param {void*} ctx 事件回调函数的上下文。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_set_on_event(media_player_t* player, event_func_t on_event, void* ctx);

/**
 * @method media_player_get_video_frame
 * 获取视频的一帧图片。
 *
 * @param {media_player_t*} media_player media_player对象。
 * @param {bitmap_t*} image 用于返回图片（图片需要调用者初始化：大小和内存）。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_get_video_frame(media_player_t* player, bitmap_t* image);

/**
 * @method media_player_destroy
 * 销毁媒体播放器对象。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_destroy(media_player_t* player);

/**
 * @method media_player_get_state
 * 获取播放状态。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {media_player_state_t} 返回播放状态。
 */
media_player_state_t media_player_get_state(media_player_t* player);

/**
 * @method media_player_get_volume
 * 获取音量。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {uint32_t} 返回音量。
 */
uint32_t media_player_get_volume(media_player_t* player);

/**
 * @method media_player_get_position
 * 获取当前播放位置。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {uint32_t} 返回当前播放位置(ms)。
 */
uint32_t media_player_get_position(media_player_t* player);

/**
 * @method media_player_get_duration
 * 获取时间长度。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {uint32_t} 返回时间长度(ms)。
 */
uint32_t media_player_get_duration(media_player_t* player);

/**
 * @method media_player_get_video_width
 * 获取视频宽度。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {uint32_t} 返回时间宽度(ms)。
 */
uint32_t media_player_get_video_width(media_player_t* player);

/**
 * @method media_player_get_video_height
 * 获取视频高度。
 *
 * @param {media_player_t*} media_player media_player对象。
 *
 * @return {uint32_t} 返回时间高度(ms)。
 */
uint32_t media_player_get_video_height(media_player_t* player);

/**
 * @method media_player_notify_simple
 * 事件通知。
 *
 * @param {media_player_t*} media_player media_player对象。
 * @param {uint32_t} event_type 事件类型。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_notify_simple(media_player_t* player, uint32_t event_type);

/**
 * @method media_player_notify
 * 事件通知。
 *
 * @param {media_player_t*} media_player media_player对象。
 * @param {event_t*} e 事件对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t media_player_notify(media_player_t* player, event_t* e);

END_C_DECLS

#endif /*TK_MEDIA_PLAYER_H*/
