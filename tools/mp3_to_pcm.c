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
  media_player_init(TRUE);
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
  media_player_deinit();

  return RET_OK;
}

