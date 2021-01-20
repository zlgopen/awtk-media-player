/**
 * File:   audio_recorder.h
 * Author: AWTK Develop Team
 * Brief:  audio_recorder
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
 * 2021-01-20 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_AUDIO_RECODER_H
#define TK_AUDIO_RECODER_H

#include "tkc/action_thread.h"
#include "media_player/base/audio_device.h"
#include "media_player/base/audio_encoder.h"

BEGIN_C_DECLS

/**
 * @enum audio_recorder_state_t
 * @prefix AUDIO_RECODER_
 * 录音状态。
 */
typedef enum _audio_recorder_state_t {
  /**
   * @const AUDIO_RECODER_NONE
   * 无效状态。
   */
  AUDIO_RECODER_NONE,

  /**
   * @const AUDIO_RECODER_PAUSED
   * 暂停状态。
   */
  AUDIO_RECODER_PAUSED,

  /**
   * @const AUDIO_RECODER_RECORDING
   * 录音状态。
   */
  AUDIO_RECODER_RECORDING
} audio_recorder_state_t;

/**
 * @class audio_recorder_t
 * 音频录音。
 *
 * 从音频设备读取声音数据，然后将数据传到音频编码器。
 *
 */
typedef struct _audio_recorder_t {
  /*private*/
  uint32_t volume;
  bool_t paused;
  bool_t abort_request;
  action_thread_t* worker;
  audio_encoder_t* encoder;
} audio_recorder_t;

/**
 * @method audio_recorder_create
 * 创建音频录音对象。
 *
 * @return {audio_recorder_t*} 返回audio_recorder对象。
 */
audio_recorder_t* audio_recorder_create(void);

/**
 * @method audio_recorder_set_volume
 * 设置音量。
 *
 * @param {audio_recorder_t*} audio_recorder audio_recorder对象。
 * @param {uint32_t} volume 音量(0-100)。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_recorder_set_volume(audio_recorder_t* recorder, uint32_t volume);

/**
 * @method audio_recorder_get_volume
 * 获取音量。
 *
 * @param {audio_recorder_t*} audio_recorder audio_recorder对象。
 *
 * @return {uint32_t} 返回音量。
 */
uint32_t audio_recorder_get_volume(audio_recorder_t* recorder);

/**
 * @method audio_recorder_get_state
 * 获取录音状态。
 *
 * @param {audio_recorder_t*} audio_recorder audio_recorder对象。
 *
 * @return {audio_recorder_state_t} 返回录音状态。
 */
audio_recorder_state_t audio_recorder_get_state(audio_recorder_t* recorder);

/**
 * @method audio_recorder_start
 * 开始录音。
 *
 * @param {audio_recorder_t*} audio_recorder audio_recorder对象。
 * @param {const char*} url 保持数据的URL。 
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_recorder_start(audio_recorder_t* recorder, const char* url); 

/**
 * @method audio_recorder_pause
 * 暂停录音。
 *
 * @param {audio_recorder_t*} audio_recorder audio_recorder对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_recorder_pause(audio_recorder_t* recorder);

/**
 * @method audio_recorder_stop
 * 停止录音。
 *
 * @param {audio_recorder_t*} audio_recorder audio_recorder对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_recorder_stop(audio_recorder_t* recorder);

/**
 * @method audio_recorder_destroy
 * 销毁音频录音对象。
 *
 * @param {audio_recorder_t*} audio_recorder audio_recorder对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_recorder_destroy(audio_recorder_t* recorder);

/**
 * @method audio_recorder
 * 获取全局缺省的audio_recorder对象。
 * @annotation ["static"]
 * 
 * @return {audio_recorder_t*} 返回audio_recorder对象。
 */
audio_recorder_t* audio_recorder(void);

/**
 * @method audio_recorder_set
 * 设置全局缺省的audio_recorder对象。
 * @annotation ["static"]
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t audio_recorder_set(audio_recorder_t* audio_recorder);

END_C_DECLS

#endif /*TK_AUDIO_RECODER_H*/

