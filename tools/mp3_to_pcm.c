/**
 * File:   mp3_to_pcm.c
 * Author: AWTK Develop Team
 * Brief:  media_player demo
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2019-05-10 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "pcm.h"
#include "awtk.h"
#include "media_player/widgets/lrc_view.h"
#include "media_player/widgets/audio_view.h"
#include "media_player/base/media_player.h"
#include "media_player/base/audio_decoder_factory.h"
#include "media_player/audio_decoders/audio_decoder_mp3.h"
#include "media_player/base/audio_encoder_factory.h"
#include "media_player/audio_encoders/audio_encoder_mp3.h"
#include "media_player/audio_player/media_player_audio.h"

static ret_t app_global_init(void) {
  data_reader_factory_set(data_reader_factory_create());
  data_writer_factory_set(data_writer_factory_create());

  data_reader_factory_register(data_reader_factory(), "file", data_reader_file_create);
  data_writer_factory_register(data_writer_factory(), "file", data_writer_file_create);

  audio_decoder_factory_set(audio_decoder_factory_create());
  audio_decoder_factory_register(audio_decoder_factory(), "mp3", audio_decoder_mp3_create);

  audio_encoder_factory_set(audio_encoder_factory_create());
  audio_encoder_factory_register(audio_encoder_factory(), "mp3", audio_encoder_mp3_create);

  return RET_OK;
}

int main(int argc, char* argv[]) {
  int32_t ret = 0;
  pcm_header_t pcm;
  int16_t buff[1024];
  uint64_t offset = 0;
  const char* infile = NULL;
  const char* outfile = NULL;
  data_reader_t* reader = NULL;
  audio_decoder_t* decoder = NULL;
  data_writer_t* writer = NULL;
  if (argc != 3) {
    log_debug("Usage: %s infile.mp3 outfile.pcm\n", argv[0]);
    return 0;
  }

  platform_prepare();
  app_global_init();
  log_set_log_level(LOG_LEVEL_DEBUG);

  infile = argv[1];
  outfile = argv[2];
  reader = data_reader_file_create(infile);
  writer = data_writer_file_create(outfile);
  decoder = audio_decoder_factory_create_decoder(audio_decoder_factory(), "mp3", reader);

  memset(&pcm,0x00,sizeof(pcm));
  pcm.version = 1;
  pcm.samplerate = decoder->freq;
  pcm.samples = decoder->samples;
  pcm.channels = decoder->channels;
  
  offset = data_writer_write(writer, offset, &pcm, sizeof(pcm));
  do {
    ret = audio_decoder_decode(decoder, buff, sizeof(buff));
    if(ret > 0) {
      log_debug("offset=%d\n", (int)offset);
      ret = data_writer_write(writer, offset, buff, ret);
      if(ret > 0) {
        offset += ret;
      }
    } else {
      break;
    }
  }while(TRUE);
  
  data_writer_destroy(writer);
  audio_decoder_destroy(decoder);

  return RET_OK;
}

