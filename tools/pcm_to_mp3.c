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
#include "media_player/media_player_helper.h"

int main(int argc, char* argv[]) {
  value_t v;
  int32_t ret = 0;
  pcm_header_t pcm;
  int16_t buff[2 * 1152];
  uint64_t offset = 0;
  const char* infile = NULL;
  const char* outfile = NULL;
  data_reader_t* reader = NULL;
  audio_encoder_t* encoder = NULL;
  data_writer_t* writer = NULL;
  if (argc != 3) {
    log_debug("Usage: %s infile.pcm outfile.mp3\n", argv[0]);
    return 0;
  }

  platform_prepare();
  media_player_init();
  log_set_log_level(LOG_LEVEL_DEBUG);

  infile = argv[1];
  outfile = argv[2];
  reader = data_reader_file_create(infile);
  writer = data_writer_file_create(outfile);
  encoder = audio_encoder_factory_create_encoder(audio_encoder_factory(), "mp3", writer);
  
  memset(&pcm,0x00,sizeof(pcm));
  offset = data_reader_read(reader, offset, &pcm, sizeof(pcm));
  
  audio_encoder_set_prop(encoder, AUDIO_ENCODER_PROP_CHANNELS, value_set_int(&v, pcm.channels));
  audio_encoder_set_prop(encoder, AUDIO_ENCODER_PROP_SAMPLE_RATE, value_set_int(&v, pcm.samplerate));

  do {
    ret = data_reader_read(reader, offset, buff, sizeof(buff));
    if(ret > 0) {
      if(ret > 0) {
        offset += ret;
      }
      ret = audio_encoder_encode(encoder, buff, sizeof(buff));
    } else {
      break;
    }
    log_debug("offset=%d\n", (int32_t)offset);
  }while(TRUE);
  
  data_reader_destroy(reader);
  audio_encoder_destroy(encoder);
  media_player_deinit();

  return RET_OK;
}

