/**
 * File:   audio_device_alsa.c
 * Author: AWTK Develop Team
 * Brief:  audio device interface implemented with alsa
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
 * 2020-02-22 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"

#ifdef WITH_ALSA

#include "ALSA.h"
#include "media_player/audio_device.h"

typedef struct _audio_device_alsa_t {
  audio_device_t audio_device;
  ALSA_AudioDeviceID devid;
} audio_device_alsa_t;

static ret_t audio_device_alsa_mix(audio_device_t* device, uint8_t* dst, const uint8_t* src,
                                  uint32_t len) {
  ALSA_MixAudio(dst, src, len, device->volume);

  return RET_OK;
}

static uint32_t audio_device_alsa_dequeue_data(audio_device_t* device, void* data, uint32_t len) {
  audio_device_alsa_t* alsa = (audio_device_alsa_t*)device;

  return ALSA_DequeueAudio(alsa->devid, data, len);
}

static int32_t audio_device_alsa_queue_data(audio_device_t* device, const void* data, uint32_t len) {
  audio_device_alsa_t* alsa = (audio_device_alsa_t*)device;

  return ALSA_QueueAudio(alsa->devid, data, len);
}

static uint32_t audio_device_alsa_get_queued_data_size(audio_device_t* device) {
  audio_device_alsa_t* alsa = (audio_device_alsa_t*)device;

  return ALSA_GetQueuedAudioSize(alsa->devid);
}

static ret_t audio_device_alsa_clear_queued_data(audio_device_t* device) {
  audio_device_alsa_t* alsa = (audio_device_alsa_t*)device;

  ALSA_ClearQueuedAudio(alsa->devid);

  return RET_OK;
}

static ret_t audio_device_alsa_start(audio_device_t* device) {
  audio_device_alsa_t* alsa = (audio_device_alsa_t*)device;

  ALSA_PauseAudioDevice(alsa->devid, FALSE);

  return RET_OK;
}

static ret_t audio_device_alsa_pause(audio_device_t* device) {
  audio_device_alsa_t* alsa = (audio_device_alsa_t*)device;

  ALSA_PauseAudioDevice(alsa->devid, TRUE);

  return RET_OK;
}

static ret_t audio_device_alsa_destroy(audio_device_t* device) {
  audio_device_alsa_t* alsa = (audio_device_alsa_t*)device;

  ALSA_CloseAudioDevice(alsa->devid);
  TKMEM_FREE(device);

  return RET_OK;
}

static uint32_t alsa_audio_format_from(uint32_t format) {
  switch (format) {
    case AUDIO_FORMAT_S16SYS: {
      return AUDIO_S16SYS;
    }
    case AUDIO_FORMAT_S16MSB: {
      return AUDIO_S16MSB;
    }
  }

  return AUDIO_S16SYS;
}

static uint32_t alsa_audio_format_to(uint32_t format) {
  switch (format) {
    case AUDIO_S16SYS: {
      return AUDIO_FORMAT_S16SYS;
    }
    case AUDIO_S16MSB: {
      return AUDIO_FORMAT_S16MSB;
    }
  }

  return AUDIO_FORMAT_S16SYS;
}

static ALSA_AudioSpec alsa_audio_spec_from(const audio_spec_t* spec) {
  ALSA_AudioSpec alsa_spec;
  memset(&alsa_spec, 0x00, sizeof(alsa_spec));

  alsa_spec.freq = spec->freq;
  alsa_spec.format = alsa_audio_format_from(spec->format);
  alsa_spec.channels = spec->channels;
  alsa_spec.samples = spec->samples;
  alsa_spec.size = spec->size;
  alsa_spec.callback = spec->callback;
  alsa_spec.userdata = spec->callback_ctx;

  return alsa_spec;
}

static audio_spec_t alsa_audio_spec_to(const ALSA_AudioSpec* alsa_spec) {
  audio_spec_t spec;
  memset(&spec, 0x00, sizeof(spec));

  spec.freq = alsa_spec->freq;
  spec.format = alsa_audio_format_to(alsa_spec->format);
  spec.channels = alsa_spec->channels;
  spec.samples = alsa_spec->samples;
  spec.size = alsa_spec->size;
  spec.callback = alsa_spec->callback;
  spec.callback_ctx = alsa_spec->userdata;

  return spec;
}

static audio_device_vtable_t s_audio_device_vtable = {
    .mix = audio_device_alsa_mix,
    .set_volume = NULL,
    .queue_data = audio_device_alsa_queue_data,
    .dequeue_data = audio_device_alsa_dequeue_data,
    .clear_queued_data = audio_device_alsa_clear_queued_data,
    .get_queued_data_size = audio_device_alsa_get_queued_data_size,
    .pause = audio_device_alsa_pause,
    .start = audio_device_alsa_start,
    .destroy = audio_device_alsa_destroy};

static audio_device_t* audio_device_alsa_create(const char* name, bool_t is_capture,
                                               const audio_spec_t* desired, audio_spec_t* real) {
  audio_device_alsa_t* alsa = NULL;
  ALSA_AudioSpec alsa_real;
  ALSA_AudioSpec alsa_desired;
  ALSA_AudioDeviceID devid = 0;
  uint32_t flags = ALSA_AUDIO_ALLOW_FREQUENCY_CHANGE | ALSA_AUDIO_ALLOW_CHANNELS_CHANGE;
  return_value_if_fail(desired != NULL && real != NULL, NULL);

  alsa_desired = alsa_audio_spec_from(desired);
  memset(&alsa_real, 0x00, sizeof(alsa_real));

  devid = ALSA_OpenAudioDevice(name, is_capture, &alsa_desired, &alsa_real, flags);
  return_value_if_fail(devid != 0, NULL);

  alsa = TKMEM_ZALLOC(audio_device_alsa_t);
  if (alsa != NULL) {
    audio_device_t* device = (audio_device_t*)alsa;

    alsa->devid = devid;
    device->volume = 50;
    device->vt = &s_audio_device_vtable;
    if (real != NULL) {
      *real = alsa_audio_spec_to(&alsa_real);
    }
  } else {
    ALSA_CloseAudioDevice(devid);
  }

  return (audio_device_t*)alsa;
}

audio_device_t* audio_device_mixer_create(const char* name, const audio_spec_t* desired,
                                          audio_spec_t* real) {
  return audio_device_alsa_create(name, FALSE, desired, real);
}

audio_device_t* audio_device_recorder_create(const char* name, const audio_spec_t* desired,
                                             audio_spec_t* real) {
  return audio_device_alsa_create(name, TRUE, desired, real);
}

#endif /*WITH_ALSA*/
