/**
 * File:   audio_encoder_mp3.h
 * Author: AWTK Develop Team
 * Brief:  mp3 audio encoder
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
 * 2021-01-18 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/value.h"
#include "layer3.h"
#include "media_player/base/audio_device.h"
#include "media_player/audio_encoders/audio_encoder_mp3.h"

typedef struct _audio_encoder_mp3_t {
  audio_encoder_t audio_encoder;

  shine_t mp3;
  uint64_t offset;
  shine_config_t config;
  data_writer_t* writer;
} audio_encoder_mp3_t;

static ret_t audio_encoder_mp3_write(audio_encoder_t* encoder, const void* data, int32_t size) {
  audio_encoder_mp3_t* aencoder = (audio_encoder_mp3_t*)encoder;
  return_value_if_fail(aencoder != NULL && data != NULL, RET_BAD_PARAMS);

  if (size > 0) {
    int32_t r = data_writer_write(aencoder->writer, aencoder->offset, data, size);
    if (r > 0) {
      aencoder->offset += r;
    }
  }

  return RET_OK;
}

static uint32_t audio_encoder_mp3_get_one_pass_bytes(audio_encoder_mp3_t* aencoder) {
  uint32_t channels = aencoder->audio_encoder.channels;
  uint32_t samples_per_pass = shine_samples_per_pass(aencoder->mp3);
  uint32_t bytes_per_pass = samples_per_pass * sizeof(uint16_t) * channels;

  return bytes_per_pass;
}

static int32_t audio_encoder_mp3_encode(audio_encoder_t* encoder, const void* buff, uint32_t size) {
  uint32_t i = 0;
  uint32_t n = 0;
  int written = 0;
  uint8_t* data = NULL;
  int16_t* p = (int16_t*)buff;
  uint32_t bytes_per_pass = 0;
  audio_encoder_mp3_t* aencoder = (audio_encoder_mp3_t*)encoder;
  return_value_if_fail(aencoder != NULL && buff != NULL, 0);

  bytes_per_pass = audio_encoder_mp3_get_one_pass_bytes(aencoder);
  if (aencoder->mp3 == NULL) {
    aencoder->mp3 = shine_initialise(&(aencoder->config));
  }

  n = size / bytes_per_pass;
  for (i = 0; i < n; i++) {
    data = shine_encode_buffer_interleaved(aencoder->mp3, p, &written);
    audio_encoder_mp3_write(encoder, data, written);
    p = (int16_t*)((uint8_t*)p + bytes_per_pass);
  }

  return n * bytes_per_pass;
}

static ret_t audio_encoder_mp3_set_prop(audio_encoder_t* encoder, const char* name,
                                        const value_t* v) {
  audio_encoder_mp3_t* aencoder = (audio_encoder_mp3_t*)encoder;

  if (tk_str_eq(name, AUDIO_ENCODER_PROP_CHANNELS)) {
    uint32_t channels = value_uint32(v);
    aencoder->config.wave.channels = channels == 2 ? PCM_STEREO : PCM_MONO;
    aencoder->audio_encoder.channels = channels;
    return RET_OK;
  } else if (tk_str_eq(name, AUDIO_ENCODER_PROP_SAMPLE_RATE)) {
    aencoder->config.wave.samplerate = value_uint32(v);
    aencoder->audio_encoder.freq = value_uint32(v);
    return RET_OK;
  }

  return RET_FAIL;
}

static ret_t audio_encoder_mp3_get_prop(audio_encoder_t* encoder, const char* name, value_t* v) {
  audio_encoder_mp3_t* aencoder = (audio_encoder_mp3_t*)encoder;
  if (tk_str_eq(name, AUDIO_ENCODER_PROP_CHANNELS)) {
    value_set_uint32(v, aencoder->audio_encoder.channels);
    return RET_OK;
  } else if (tk_str_eq(name, AUDIO_ENCODER_PROP_SAMPLE_RATE)) {
    value_set_uint32(v, aencoder->audio_encoder.freq);
    return RET_OK;
  } else if (tk_str_eq(name, AUDIO_ENCODER_PROP_PREFER_BUFFER_SIZE)) {
    uint32_t bytes_per_pass = 0;
    if (aencoder->mp3 == NULL) {
      aencoder->mp3 = shine_initialise(&(aencoder->config));
    }
    bytes_per_pass = audio_encoder_mp3_get_one_pass_bytes(aencoder);
    value_set_uint32(v, bytes_per_pass);
    return RET_OK;
  }

  return RET_FAIL;
}

static ret_t audio_encoder_mp3_destroy(audio_encoder_t* encoder) {
  int written = 0;
  uint8_t* data = NULL;
  audio_encoder_mp3_t* aencoder = (audio_encoder_mp3_t*)encoder;
  return_value_if_fail(aencoder != NULL, RET_BAD_PARAMS);

  data = shine_flush(aencoder->mp3, &written);
  audio_encoder_mp3_write(encoder, data, written);

  shine_close(aencoder->mp3);
  data_writer_destroy(aencoder->writer);
  TKMEM_FREE(encoder);

  return RET_OK;
}

static const audio_encoder_vtable_t s_audio_encoder_mp3_vtable = {
    .encode = audio_encoder_mp3_encode,
    .set_prop = audio_encoder_mp3_set_prop,
    .get_prop = audio_encoder_mp3_get_prop,
    .destroy = audio_encoder_mp3_destroy,
};

audio_encoder_t* audio_encoder_mp3_create(data_writer_t* writer) {
  audio_encoder_mp3_t* aencoder = NULL;
  return_value_if_fail(writer != NULL, NULL);

  aencoder = TKMEM_ZALLOC(audio_encoder_mp3_t);
  return_value_if_fail(aencoder != NULL, NULL);

  aencoder->audio_encoder.vt = &s_audio_encoder_mp3_vtable;
  aencoder->writer = writer;
  shine_set_config_mpeg_defaults(&(aencoder->config.mpeg));

  aencoder->config.wave.channels = PCM_STEREO;
  aencoder->config.wave.samplerate = 44100;
  aencoder->audio_encoder.freq = 44100;
  aencoder->audio_encoder.channels = 2;

  return (audio_encoder_t*)aencoder;
}
