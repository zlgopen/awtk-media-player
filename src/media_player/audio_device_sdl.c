/**
 * File:   audio_device_sdl.c
 * Author: AWTK Develop Team
 * Brief:  audio device interface implemented with sdl
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

#ifdef WITH_SDL

#include "SDL.h"
#include "media_player/audio_device.h"

typedef struct _audio_device_sdl_t {
  audio_device_t audio_device;
  SDL_AudioDeviceID devid;
} audio_device_sdl_t;

static ret_t audio_device_sdl_mix(audio_device_t* device, uint8_t* dst, const uint8_t* src,
                                  uint32_t len) {
  SDL_MixAudio(dst, src, len, device->volume);

  return RET_OK;
}

static uint32_t audio_device_sdl_dequeue_data(audio_device_t* device, void* data, uint32_t len) {
  audio_device_sdl_t* sdl = (audio_device_sdl_t*)device;

  return SDL_DequeueAudio(sdl->devid, data, len);
}

static int32_t audio_device_sdl_queue_data(audio_device_t* device, const void* data, uint32_t len) {
  audio_device_sdl_t* sdl = (audio_device_sdl_t*)device;

  return SDL_QueueAudio(sdl->devid, data, len);
}

static uint32_t audio_device_sdl_get_queued_data_size(audio_device_t* device) {
  audio_device_sdl_t* sdl = (audio_device_sdl_t*)device;

  return SDL_GetQueuedAudioSize(sdl->devid);
}

static ret_t audio_device_sdl_clear_queued_data(audio_device_t* device) {
  audio_device_sdl_t* sdl = (audio_device_sdl_t*)device;

  SDL_ClearQueuedAudio(sdl->devid);

  return RET_OK;
}

static ret_t audio_device_sdl_start(audio_device_t* device) {
  audio_device_sdl_t* sdl = (audio_device_sdl_t*)device;

  SDL_PauseAudioDevice(sdl->devid, FALSE);

  return RET_OK;
}

static ret_t audio_device_sdl_pause(audio_device_t* device) {
  audio_device_sdl_t* sdl = (audio_device_sdl_t*)device;

  SDL_PauseAudioDevice(sdl->devid, TRUE);

  return RET_OK;
}

static ret_t audio_device_sdl_destroy(audio_device_t* device) {
  audio_device_sdl_t* sdl = (audio_device_sdl_t*)device;

  SDL_CloseAudioDevice(sdl->devid);
  TKMEM_FREE(device);

  return RET_OK;
}

static uint32_t sdl_audio_format_from(uint32_t format) {
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

static uint32_t sdl_audio_format_to(uint32_t format) {
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

static SDL_AudioSpec sdl_audio_spec_from(const audio_spec_t* spec) {
  SDL_AudioSpec sdl_spec;
  memset(&sdl_spec, 0x00, sizeof(sdl_spec));

  sdl_spec.freq = spec->freq;
  sdl_spec.format = sdl_audio_format_from(spec->format);
  sdl_spec.channels = spec->channels;
  sdl_spec.samples = spec->samples;
  sdl_spec.size = spec->size;
  sdl_spec.callback = spec->callback;
  sdl_spec.userdata = spec->callback_ctx;

  return sdl_spec;
}

static audio_spec_t sdl_audio_spec_to(const SDL_AudioSpec* sdl_spec) {
  audio_spec_t spec;
  memset(&spec, 0x00, sizeof(spec));

  spec.freq = sdl_spec->freq;
  spec.format = sdl_audio_format_to(sdl_spec->format);
  spec.channels = sdl_spec->channels;
  spec.samples = sdl_spec->samples;
  spec.size = sdl_spec->size;
  spec.callback = sdl_spec->callback;
  spec.callback_ctx = sdl_spec->userdata;

  return spec;
}

static audio_device_vtable_t s_audio_device_vtable = {
    .mix = audio_device_sdl_mix,
    .set_volume = NULL,
    .queue_data = audio_device_sdl_queue_data,
    .dequeue_data = audio_device_sdl_dequeue_data,
    .clear_queued_data = audio_device_sdl_clear_queued_data,
    .get_queued_data_size = audio_device_sdl_get_queued_data_size,
    .pause = audio_device_sdl_pause,
    .start = audio_device_sdl_start,
    .destroy = audio_device_sdl_destroy};

static audio_device_t* audio_device_sdl_create(const char* name, bool_t is_capture,
                                               const audio_spec_t* desired, audio_spec_t* real) {
  audio_device_sdl_t* sdl = NULL;
  SDL_AudioSpec sdl_real;
  SDL_AudioSpec sdl_desired;
  SDL_AudioDeviceID devid = 0;
  uint32_t flags = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE;
  return_value_if_fail(desired != NULL && real != NULL, NULL);

  sdl_desired = sdl_audio_spec_from(desired);
  memset(&sdl_real, 0x00, sizeof(sdl_real));

  devid = SDL_OpenAudioDevice(name, is_capture, &sdl_desired, &sdl_real, flags);
  return_value_if_fail(devid != 0, NULL);

  sdl = TKMEM_ZALLOC(audio_device_sdl_t);
  if (sdl != NULL) {
    audio_device_t* device = (audio_device_t*)sdl;

    sdl->devid = devid;
    device->volume = 50;
    device->vt = &s_audio_device_vtable;
    if (real != NULL) {
      *real = sdl_audio_spec_to(&sdl_real);
    }
  } else {
    SDL_CloseAudioDevice(devid);
  }

  return (audio_device_t*)sdl;
}

audio_device_t* audio_device_mixer_create(const char* name, const audio_spec_t* desired,
                                          audio_spec_t* real) {
  return audio_device_sdl_create(name, FALSE, desired, real);
}

audio_device_t* audio_device_recorder_create(const char* name, const audio_spec_t* desired,
                                             audio_spec_t* real) {
  return audio_device_sdl_create(name, TRUE, desired, real);
}

#endif /*WITH_SDL*/
