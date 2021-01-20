/**
 * File:   media_player_helper.h
 * Author: AWTK Develop Team
 * Brief:  audio encoder factory
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
 * ================================================================
 * 2021-01-20 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "media_player/widgets/lrc_view.h"
#include "media_player/widgets/audio_view.h"
#include "media_player/base/media_player.h"
#include "media_player/base/audio_encoder_factory.h"
#include "media_player/audio_encoders/audio_encoder_mp3.h"
#include "media_player/base/audio_decoder_factory.h"
#include "media_player/audio_decoders/audio_decoder_mp3.h"
#include "media_player/audio_player/media_player_audio.h"
#include "media_player/widgets/video_view.h"
#include "media_player/base/media_player.h"
#include "media_player/audio_recorder/audio_recorder.h"

#ifdef WITH_PLAYER_FFMPEG 
#include "media_player/ffmpeg/media_player_ffmpeg.h"
#endif/*WITH_PLAYER_FFMPEG*/

ret_t media_player_init(bool_t audio_player_only) {

  if (widget_factory() != NULL) {
    lrc_view_register();
    video_view_register();
    audio_view_register();
  }

  audio_recorder_set(audio_recorder_create());

  if (audio_player_only) {
    media_player_set(media_player_audio_create());
  } else {
#ifdef WITH_PLAYER_FFMPEG 
    media_player_set(media_player_ffmpeg_create());
#endif/*WITH_PLAYER_FFMPEG */
  }
  
  if(data_reader_factory() == NULL) {
    data_reader_factory_set(data_reader_factory_create());
    data_reader_factory_register(data_reader_factory(), "file", data_reader_file_create);
  }
  
  if(data_writer_factory() == NULL) {
    data_writer_factory_set(data_writer_factory_create());
    data_writer_factory_register(data_writer_factory(), "file", data_writer_file_create);
  }
  
  audio_decoder_factory_set(audio_decoder_factory_create());
  audio_decoder_factory_register(audio_decoder_factory(), "mp3", audio_decoder_mp3_create);

  audio_encoder_factory_set(audio_encoder_factory_create());
  audio_encoder_factory_register(audio_encoder_factory(), "mp3", audio_encoder_mp3_create);

  return RET_OK;
}

ret_t media_player_deinit(void) {
  audio_recorder_destroy(audio_recorder());
  audio_recorder_set(NULL);

  media_player_destroy(media_player());
  media_player_set(NULL);

  audio_decoder_factory_destroy(audio_decoder_factory());
  audio_decoder_factory_set(NULL);
  
  audio_encoder_factory_destroy(audio_encoder_factory());
  audio_encoder_factory_set(NULL);

  return RET_OK;
}

