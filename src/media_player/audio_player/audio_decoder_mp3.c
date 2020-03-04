/**
 * File:   audio_decoder_mp3.h
 * Author: AWTK Develop Team
 * Brief:  mp3 audio decoder
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
 * 2020-02-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#define MINIMP3_IMPLEMENTATION 1

#include "tkc/mem.h"
#include "minimp3/minimp3_ex.h"
#include "media_player/base/audio_device.h"
#include "media_player/audio_player/audio_decoder_mp3.h"

typedef struct _audio_decoder_mp3_t {
  audio_decoder_t audio_decoder;

  mp3dec_ex_t mp3;
  data_reader_t* reader;

  mp3dec_io_t io;
  uint64_t io_seek_offset;
} audio_decoder_mp3_t;

static size_t mp3d_read_cb(void* buf, size_t size, void* user_data) {
  int ret = 0;
  audio_decoder_mp3_t* mp3 = (audio_decoder_mp3_t*)user_data;

  ret = data_reader_read(mp3->reader, mp3->io_seek_offset, buf, size);
  if (ret > 0) {
    mp3->io_seek_offset += ret;
  }

  return ret;
}

static int mp3d_seek_cb(uint64_t position, void* user_data) {
  audio_decoder_mp3_t* mp3 = (audio_decoder_mp3_t*)user_data;

  mp3->io_seek_offset = position;

  return 0;
}

static int32_t audio_decoder_mp3_decode(audio_decoder_t* decoder, void* buff, uint32_t size) {
  uint32_t request_samples = size / sizeof(mp3d_sample_t);
  audio_decoder_mp3_t* adecoder = (audio_decoder_mp3_t*)decoder;
  uint32_t samples = mp3dec_ex_read(&(adecoder->mp3), (mp3d_sample_t*)buff, request_samples);

  decoder->position = (adecoder->mp3.cur_sample * 1000) / (decoder->channels * decoder->freq);

  return samples * sizeof(mp3d_sample_t);
}

static ret_t audio_decoder_mp3_seek(audio_decoder_t* decoder, uint32_t offset) {
  uint64_t position = decoder->samples;
  audio_decoder_mp3_t* adecoder = (audio_decoder_mp3_t*)decoder;
  if (offset >= decoder->duration) {
    offset = decoder->duration;
  }

  if (decoder->duration == 0) {
    return RET_BAD_PARAMS;
  }

  position = (position * offset) / decoder->duration;
  mp3dec_ex_seek(&(adecoder->mp3), position);

  return RET_OK;
}

static ret_t audio_decoder_mp3_destroy(audio_decoder_t* decoder) {
  audio_decoder_mp3_t* adecoder = (audio_decoder_mp3_t*)decoder;

  mp3dec_ex_close(&(adecoder->mp3));
  data_reader_destroy(adecoder->reader);
  TKMEM_FREE(decoder);

  return RET_OK;
}

static const audio_decoder_vtable_t s_audio_decoder_mp3_vtable = {
    .decode = audio_decoder_mp3_decode,
    .seek = audio_decoder_mp3_seek,
    .destroy = audio_decoder_mp3_destroy,
};

audio_decoder_t* audio_decoder_mp3_create(data_reader_t* reader) {
  audio_decoder_mp3_t* adecoder = NULL;
  return_value_if_fail(reader != NULL, NULL);

  adecoder = TKMEM_ZALLOC(audio_decoder_mp3_t);
  return_value_if_fail(adecoder != NULL, NULL);

  adecoder->reader = reader;
  adecoder->io.read_data = adecoder;
  adecoder->io.seek_data = adecoder;
  adecoder->io.read = mp3d_read_cb;
  adecoder->io.seek = mp3d_seek_cb;

  adecoder->audio_decoder.vt = &s_audio_decoder_mp3_vtable;

  if (mp3dec_ex_open_cb(&(adecoder->mp3), &(adecoder->io), MP3D_SEEK_TO_SAMPLE) == 0) {
    audio_decoder_t* decoder = (audio_decoder_t*)adecoder;

    decoder->freq = adecoder->mp3.info.hz;
    decoder->channels = adecoder->mp3.info.channels;
    decoder->samples = adecoder->mp3.samples;
    decoder->format = AUDIO_FORMAT_S16SYS;
    decoder->duration = (decoder->samples) / (decoder->channels * decoder->freq/1000);
  } else {
    TKMEM_FREE(adecoder);
  }

  return (audio_decoder_t*)adecoder;
}
