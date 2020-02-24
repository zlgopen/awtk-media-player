/**
 * File:   audio_device.h
 * Author: AWTK Develop Team
 * Brief:  audio device interface
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
 * 2020-02-21 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_AUDIO_DEVICE_H
#define TK_AUDIO_DEVICE_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

#define AUDIO_DEVICE_MAXVOLUME 128

typedef void (*audio_device_callback_t)(void* userdata, uint8_t* stream, int len);

/**
 * @enum audio_format_t
 * @prefix AUDIO_FORMAT_
 * 音频格式。
 */
typedef enum _audio_format_t {
  /**
   * @const AUDIO_FORMAT_NONE
   * 无效格式。
   */
  AUDIO_FORMAT_NONE = 0,
  /**
   * @const AUDIO_FORMAT_S16SYS
   * 16位有符号采样(系统原生字节顺序)。
   */
  AUDIO_FORMAT_S16SYS,
  /**
   * @const AUDIO_FORMAT_S16LSB
   * 32位有符号采样(小端字节顺序)。
   */
  AUDIO_FORMAT_S16LSB,
  /**
   * @const AUDIO_FORMAT_S16MSB
   * 16位无符号采样(大端字节顺序)。
   */
  AUDIO_FORMAT_S16MSB
} audio_format_t;

/**
 * @class audio_spec_t
 * 音频描述。
 */
typedef struct _audio_spec_t {
  /**
   * @property {int32_t} freq
   * @annotation ["readable"]
   * 每秒采样数量。
   */
  int32_t freq;

  /**
   * @property {uint32_t} format
   * @annotation ["readable"]
   * 音频格式。
   */
  uint32_t format;

  /**
   * @property {uint8_t} channels
   * @annotation ["readable"]
   * 通道数。1表示单声道，2表示立体声。
   */
  uint8_t channels;

  /**
   * @property {uint16_t} samples
   * @annotation ["readable"]
   * 采样数。
   */
  uint16_t samples;

  /**
   * @property {uint32_t} size
   * @annotation ["readable"]
   * 音频缓存大小(根据参数计算得来)。
   */
  uint32_t size;

  /**
   * @property {audio_device_callback_t} callback
   * @annotation ["readable"]
   * 回调函数。
   */
  audio_device_callback_t callback;

  /**
   * @property {void*} callback_ctx
   * @annotation ["readable"]
   * 回调函数的上下文。
   */
  void* callback_ctx;
} audio_spec_t;

struct _audio_device_t;
typedef struct _audio_device_t audio_device_t;

typedef ret_t (*audio_device_mix_t)(audio_device_t* device, uint8_t* dst, const uint8_t* src,
                                    uint32_t len);
typedef uint32_t (*audio_device_dequeue_data_t)(audio_device_t* device, void* data, uint32_t len);
typedef int32_t (*audio_device_queue_data_t)(audio_device_t* device, const void* data,
                                             uint32_t len);
typedef uint32_t (*audio_device_get_queued_data_size_t)(audio_device_t* device);
typedef ret_t (*audio_device_clear_queued_data_t)(audio_device_t* device);
typedef ret_t (*audio_device_set_volume_t)(audio_device_t* device, uint32_t volume);
typedef ret_t (*audio_device_pause_t)(audio_device_t* device);
typedef ret_t (*audio_device_start_t)(audio_device_t* device);
typedef ret_t (*audio_device_destroy_t)(audio_device_t* device);

typedef struct _audio_device_vtable_t {
  audio_device_mix_t mix;
  audio_device_set_volume_t set_volume;
  audio_device_queue_data_t queue_data;
  audio_device_dequeue_data_t dequeue_data;
  audio_device_clear_queued_data_t clear_queued_data;
  audio_device_get_queued_data_size_t get_queued_data_size;
  audio_device_pause_t pause;
  audio_device_start_t start;
  audio_device_destroy_t destroy;
} audio_device_vtable_t;

/**
 * @class audio_device_t
 * 媒体播放器接口。
 */
struct _audio_device_t {
  const audio_device_vtable_t* vt;

  /**
   * @property {uint32_t} volume
   * @annotation ["readable"]
   * 音量。
   */
  uint32_t volume;
};

/**
 * @method audio_device_mix
 * 准备播放的数据(在回调函数中调用)。
 *
 * @param {audio_device_t*} device audio_device对象。
 * @param {uint8_t*} dst 目标缓存区。
 * @param {const uint8_t*} src 目标缓存区。
 * @param {uint32_t} len 数据长度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_device_mix(audio_device_t* device, uint8_t* dst, const uint8_t* src, uint32_t len);

/**
 * @method audio_device_dequeue_data
 * 获取录音的数据。
 *
 * @param {audio_device_t*} device audio_device对象。
 * @param {void*} data 用于返回数据。
 * @param {uint32_t} len 最大数据长度。
 *
 * @return {uint32_t} 返回实际数据长度。
 */
uint32_t audio_device_dequeue_data(audio_device_t* device, void* data, uint32_t len);

/**
 * @method audio_device_queue_data
 * 追加播放的音频数据。
 *
 * @param {audio_device_t*} device audio_device对象。
 * @param {const void*} data 音频数据。
 * @param {uint32_t} len 数据长度。
 *
 * @return {int32_t} 返回实际数据长度。
 */
int32_t audio_device_queue_data(audio_device_t* device, const void* data, uint32_t len);

/**
 * @method audio_device_get_queued_data_size
 * 获取队列中的音频数据长度。
 *
 * @param {audio_device_t*} device audio_device对象。
 *
 * @return {uint32_t} 返回数据长度。
 */
uint32_t audio_device_get_queued_data_size(audio_device_t* device);

/**
 * @method audio_device_clear_queued_data
 * 清除队列中的音频数据。
 *
 * @param {audio_device_t*} device audio_device对象。
 *
 * @return {uint32_t} 返回数据长度。
 */
ret_t audio_device_clear_queued_data(audio_device_t* device);

/**
 * @method audio_device_start
 * 让设备开始工作。
 *
 * @param {audio_device_t*} audio_device audio_device对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_device_start(audio_device_t* device);

/**
 * @method audio_device_pause
 * 让设备暂停工作。
 *
 * @param {audio_device_t*} audio_device audio_device对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_device_pause(audio_device_t* device);

/**
 * @method audio_device_set_volume
 * 设置音量。
 *
 * @param {audio_device_t*} device audio_device对象。
 * @param {uint32_t} volume 音量(0-100)。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_device_set_volume(audio_device_t* device, uint32_t volume);

/**
 * @method audio_device_destroy
 * 销毁audio device对象。
 *
 * @param {audio_device_t*} device audio_device对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_device_destroy(audio_device_t* device);

/**
 * @method audio_device_mixer_create
 * 创建用于播放的音频设备。
 *
 * @param {const char*} name 名称。
 * @param {const audio_spec_t*} desired 期望的audio spec。
 * @param {audio_spec_t*} real 实际支持的audio spec。
 *
 * @return {audio_device_t*} 返回音频设备。
 */
audio_device_t* audio_device_mixer_create(const char* name, const audio_spec_t* desired,
                                          audio_spec_t* real);

/**
 * @method audio_device_recorder_create
 * 创建用于录音的音频设备。
 *
 * @param {const char*} name 名称。
 * @param {const audio_spec_t*} desired 期望的audio spec。
 * @param {audio_spec_t*} real 实际支持的audio spec。
 *
 * @return {audio_device_t*} 返回音频设备。
 */
audio_device_t* audio_device_recorder_create(const char* name, const audio_spec_t* desired,
                                             audio_spec_t* real);

END_C_DECLS

#endif /*TK_AUDIO_DEVICE_H*/
