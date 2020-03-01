/**
 * File:   media_player_audio.h
 * Author: AWTK Develop Team
 * Brief:  media_player_audio
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
 * 2020-02-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/rect.h"
#include "tkc/cond.h"
#include "tkc/mutex.h"
#include "tkc/platform.h"
#include "tkc/action_thread.h"
#include "tkc/data_reader_factory.h"
#include "media_player/base/audio_device.h"
#include "media_player/audio_player/audio_decoder_factory.h"
#include "media_player/audio_player/media_player_audio.h"
#include "media_player/base/media_player_event.h"

typedef struct _media_player_audio_t {
  media_player_t media_player;
  audio_decoder_t* decoder;

  uint32_t duration;
  uint32_t position;
  uint32_t volume;

  bool_t paused;
  bool_t muted;
  bool_t abort_request;
  action_thread_t* worker;
} media_player_audio_t;

typedef struct _action_play_info_t {
  media_player_audio_t* player;
} action_play_info_t;

static ret_t qaction_exec_decode(qaction_t* action) {
  int32_t ret = 0;
  uint16_t buff[1024];
  audio_spec_t real;
  audio_spec_t desired;
  action_play_info_t* info = (action_play_info_t*)(action->args);
  media_player_audio_t* player = info->player;
  audio_decoder_t* decoder = player->decoder;
  audio_device_t* device = NULL;

  memset(&real, 0x00, sizeof(real));
  memset(&desired, 0x00, sizeof(desired));

  desired.freq = player->decoder->freq;
  desired.format = player->decoder->format;
  desired.channels = player->decoder->channels;

  player->abort_request = FALSE;
  device = audio_device_mixer_create(NULL, &desired, &real);
  while (player->abort_request == FALSE) {
    uint32_t queued_data_size = 0;

    memset(buff, 0, sizeof(buff));

    if (player->paused) {
      sleep_ms(10);
      continue;
    }

    queued_data_size = audio_device_get_queued_data_size(device);
    if (queued_data_size > 20480) {
      sleep_ms(10);
      continue;
    }

    ret = audio_decoder_decode(decoder, buff, sizeof(buff));
    if (ret > 0) {
      audio_device_start(device);
      ret = audio_device_queue_data(device, buff, ret);
    } else {
      log_debug("decode done\n");
      break;
    }
  }

  audio_device_destroy(device);
  audio_decoder_destroy(decoder);
  player->decoder = NULL;

  return RET_OK;
}

static ret_t media_player_audio_create_decoder(media_player_audio_t* player, const char* url) {
  const char* type = strrchr(url, '.');
  if(type != NULL) {
    data_reader_t* reader = data_reader_factory_create_reader(data_reader_factory(), url);
    return_value_if_fail(reader != NULL, RET_BAD_PARAMS);
   
    type++;
    player->decoder = audio_decoder_factory_create_decoder(audio_decoder_factory(), type, reader);
    if(player->decoder == NULL) {
      data_reader_destroy(reader);
    }
  }

  return player->decoder != NULL ? RET_OK : RET_FAIL;
}

static ret_t media_player_audio_load(media_player_t* player, const char* url) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;

  if (aplayer->decoder != NULL) {
    media_player_stop(player);
  }

  return_value_if_fail(media_player_audio_create_decoder(aplayer, url) == RET_OK, RET_FAIL);

  if (aplayer->decoder != NULL) {
    aplayer->paused = TRUE;
    action_play_info_t info = {aplayer};
    qaction_t* action = qaction_create(qaction_exec_decode, &info, sizeof(info));
    action_thread_exec(aplayer->worker, action);
  }

  return RET_OK;
}

static ret_t media_player_audio_start(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, RET_BAD_PARAMS);

  if (aplayer->paused) {
    aplayer->paused = FALSE;
  }

  return RET_OK;
}

static ret_t media_player_audio_pause(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, RET_BAD_PARAMS);

  if (!(aplayer->paused)) {
    aplayer->paused = TRUE;
  }

  return RET_OK;
}

static ret_t media_player_audio_stop(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, RET_BAD_PARAMS);

  if (aplayer->decoder != NULL) {
    aplayer->abort_request = 1;
  }

  while (aplayer->decoder != NULL) {
    sleep_ms(10);
  }

  return RET_OK;
}

static ret_t media_player_audio_seek(media_player_t* player, uint32_t offset) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, RET_BAD_PARAMS);

  return audio_decoder_seek(aplayer->decoder, offset);
}

static ret_t media_player_audio_set_volume(media_player_t* player, uint32_t volume) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, RET_BAD_PARAMS);

  aplayer->volume = volume;

  return RET_OK;
}

static ret_t media_player_audio_toggle_mute(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, RET_BAD_PARAMS);

  aplayer->muted = !aplayer->muted;

  return RET_OK;
}

static ret_t media_player_audio_set_on_event(media_player_t* player, event_func_t on_event,
                                             void* ctx) {
  return RET_OK;
}

static ret_t media_player_audio_destroy(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, RET_BAD_PARAMS);

  media_player_stop(player);
  action_thread_destroy(aplayer->worker);
  TKMEM_FREE(player);

  return RET_OK;
}

static media_player_state_t media_player_audio_get_state(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;

  if (aplayer->decoder == NULL) {
    return MEDIA_PLAYER_NONE;
  }

  return (aplayer->paused) ? MEDIA_PLAYER_PAUSED : MEDIA_PLAYER_PLAYING;
}

static uint32_t media_player_audio_get_volume(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, 0);

  return aplayer->volume;
  ;
}

static uint32_t media_player_audio_get_position(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, 0);

  return aplayer->position;
}

static uint32_t media_player_audio_get_duration(media_player_t* player) {
  media_player_audio_t* aplayer = (media_player_audio_t*)player;
  return_value_if_fail(aplayer->decoder != NULL, 0);

  return aplayer->duration;
}

static const media_player_vtable_t s_media_player_audio = {
    .load = media_player_audio_load,
    .start = media_player_audio_start,
    .pause = media_player_audio_pause,
    .stop = media_player_audio_stop,
    .seek = media_player_audio_seek,
    .set_volume = media_player_audio_set_volume,
    .toggle_mute = media_player_audio_toggle_mute,
    .set_on_event = media_player_audio_set_on_event,
    .destroy = media_player_audio_destroy,
    .get_state = media_player_audio_get_state,
    .get_volume = media_player_audio_get_volume,
    .get_position = media_player_audio_get_position,
    .get_duration = media_player_audio_get_duration};

media_player_t* media_player_audio_create(void) {
  media_player_audio_t* player = TKMEM_ZALLOC(media_player_audio_t);
  return_value_if_fail(player != NULL, NULL);

  player->worker = action_thread_create();
  player->media_player.vt = &s_media_player_audio;

  return (media_player_t*)player;
}
