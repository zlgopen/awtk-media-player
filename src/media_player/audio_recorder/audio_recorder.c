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

#include "tkc/mem.h"
#include "tkc/rect.h"
#include "tkc/cond.h"
#include "tkc/mutex.h"
#include "tkc/platform.h"
#include "tkc/action_thread.h"
#include "tkc/data_writer_factory.h"
#include "media_player/base/audio_device.h"
#include "media_player/base/audio_encoder_factory.h"
#include "media_player/audio_recorder/audio_recorder.h"

typedef struct _action_play_info_t {
  audio_recorder_t* recorder;
} action_play_info_t;

#define AUDIO_ENCODE_BUFFER_SIZE 4 * 1024

static ret_t qaction_exec_decode(qaction_t* action) {
  value_t v;
  int32_t ret = 0;
  audio_spec_t real;
  int16_t* buff = NULL;
  audio_spec_t desired;
  audio_device_t* device = NULL;
  int32_t buff_size = AUDIO_ENCODE_BUFFER_SIZE;
  action_play_info_t* info = (action_play_info_t*)(action->args);
  audio_recorder_t* recorder = info->recorder;
  audio_encoder_t* encoder = recorder->encoder;
  uint32_t volume = recorder->volume;
  bool_t paused = recorder->paused;

  memset(&real, 0x00, sizeof(real));
  memset(&desired, 0x00, sizeof(desired));

  desired.format = AUDIO_FORMAT_S16SYS;
  desired.freq = recorder->encoder->freq;
  desired.channels = recorder->encoder->channels;

  device = audio_device_recorder_create(NULL, &desired, &real);
  return_value_if_fail(device != NULL, RET_FAIL);

  audio_device_set_volume(device, volume);
  audio_device_start(device);

  if (audio_encoder_get_prop(encoder, AUDIO_ENCODER_PROP_PREFER_BUFFER_SIZE, &v) == RET_OK) {
    buff_size = value_uint32(&v);
  }
  buff = (int16_t*)TKMEM_ALLOC(buff_size);
  return_value_if_fail(buff != NULL, RET_BAD_PARAMS);

  while (!(recorder->abort_request)) {
    memset(buff, 0, buff_size);

    if (volume != recorder->volume) {
      volume = recorder->volume;
      audio_device_set_volume(device, volume);
    }

    if (paused != recorder->paused) {
      paused = recorder->paused;
      if (paused) {
        audio_device_pause(device);
      } else {
        audio_device_start(device);
      }
    }

    if (paused) {
      sleep_ms(10);
      continue;
    }

    ret = audio_device_dequeue_data_len(device, buff, buff_size, 1000);
    if (ret == buff_size) {
      ret = audio_encoder_encode(encoder, buff, ret);
      ENSURE(ret == buff_size);
    } else if (ret == 0) {
      sleep_ms(10);
      continue;
    } else if (ret < buff_size) {
      log_debug("x");
    } else {
      log_debug("decode done\n");
      break;
    }
  }

  recorder->encoder = NULL;
  recorder->abort_request = FALSE;
  TKMEM_FREE(buff);
  audio_device_destroy(device);
  audio_encoder_destroy(encoder);

  return RET_OK;
}

static ret_t audio_recorder_create_encoder(audio_recorder_t* recorder, const char* url) {
  const char* type = strrchr(url, '.');

  if (type != NULL) {
    data_writer_t* writer = data_writer_factory_create_writer(data_writer_factory(), url);
    return_value_if_fail(writer != NULL, RET_BAD_PARAMS);

    type++;
    recorder->encoder = audio_encoder_factory_create_encoder(audio_encoder_factory(), type, writer);
    if (recorder->encoder == NULL) {
      data_writer_destroy(writer);
    }
  }

  return recorder->encoder != NULL ? RET_OK : RET_FAIL;
}

ret_t audio_recorder_start(audio_recorder_t* recorder, const char* url) {
  return_value_if_fail(recorder != NULL, RET_BAD_PARAMS);

  if (recorder->encoder != NULL) {
    audio_recorder_stop(recorder);
  }

  return_value_if_fail(audio_recorder_create_encoder(recorder, url) == RET_OK, RET_FAIL);

  if (recorder->encoder != NULL) {
    action_play_info_t info = {recorder};
    qaction_t* action = qaction_create(qaction_exec_decode, &info, sizeof(info));
    action_thread_exec(recorder->worker, action);
  }

  return RET_OK;
}

ret_t audio_recorder_pause(audio_recorder_t* recorder) {
  return_value_if_fail(recorder != NULL && recorder->encoder != NULL, RET_BAD_PARAMS);

  if (!(recorder->paused)) {
    recorder->paused = TRUE;
  }

  return RET_OK;
}

ret_t audio_recorder_stop(audio_recorder_t* recorder) {
  return_value_if_fail(recorder != NULL && recorder->encoder != NULL, RET_BAD_PARAMS);

  if (recorder->encoder != NULL) {
    recorder->abort_request = 1;
  }

  while (recorder->encoder != NULL) {
    sleep_ms(10);
  }

  return RET_OK;
}

ret_t audio_recorder_set_volume(audio_recorder_t* recorder, uint32_t volume) {
  return_value_if_fail(recorder != NULL && recorder->encoder != NULL, RET_BAD_PARAMS);

  recorder->volume = volume;

  return RET_OK;
}

ret_t audio_recorder_destroy(audio_recorder_t* recorder) {
  return_value_if_fail(recorder != NULL, RET_BAD_PARAMS);

  if (recorder->encoder != NULL) {
    audio_recorder_stop(recorder);
  }
  action_thread_destroy(recorder->worker);
  TKMEM_FREE(recorder);

  return RET_OK;
}

audio_recorder_state_t audio_recorder_get_state(audio_recorder_t* recorder) {
  return_value_if_fail(recorder != NULL, AUDIO_RECODER_NONE);

  if (recorder->encoder == NULL) {
    return AUDIO_RECODER_NONE;
  }

  return (recorder->paused) ? AUDIO_RECODER_PAUSED : AUDIO_RECODER_RECORDING;
}

uint32_t audio_recorder_get_volume(audio_recorder_t* recorder) {
  return_value_if_fail(recorder != NULL, 0);

  return recorder->volume;
}

audio_recorder_t* audio_recorder_create(void) {
  audio_recorder_t* recorder = TKMEM_ZALLOC(audio_recorder_t);
  return_value_if_fail(recorder != NULL, NULL);

  recorder->volume = 60;
  recorder->worker = action_thread_create();

  return (audio_recorder_t*)recorder;
}

static audio_recorder_t* s_recorder;

audio_recorder_t* audio_recorder(void) {
  return s_recorder;
}

ret_t audio_recorder_set(audio_recorder_t* audio_recorder) {
  s_recorder = audio_recorder;

  return RET_OK;
}
