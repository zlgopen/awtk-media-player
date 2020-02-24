/**
 * File:   media_player_ffmpeg.h
 * Author: AWTK Develop Team
 * Brief:  media_player_ffmpeg
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
 * 2020-02-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/rect.h"
#include "tkc/cond.h"
#include "tkc/mutex.h"
#include "tkc/thread.h"
#include "tkc/platform.h"
#include "media_player/audio_device.h"
#include "media_player/media_player_event.h"
#include "media_player/media_player_ffmpeg.h"

static ret_t media_player_ffmpeg_notify(media_player_t* player, event_t* e);
static ret_t media_player_ffmpeg_notify_simple(media_player_t* player, uint32_t type);

#include "ffmpeg_player.inc"

typedef struct _media_player_ffmpeg_t {
  media_player_t media_player;
  VideoState* is;
} media_player_ffmpeg_t;

static ret_t media_player_ffmpeg_notify(media_player_t* player, event_t* e) {
  return media_player_notify(player, e);
}

static ret_t media_player_ffmpeg_notify_simple(media_player_t* player, uint32_t type) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;

  if (type == EVT_MEDIA_PLAYER_DONE) {
    ffmpeg->is = NULL;
  }

  return media_player_notify_simple(player, type);
}

static ret_t media_player_ffmpeg_load(media_player_t* player, const char* url) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;

  if (ffmpeg->is != NULL) {
    stream_close(ffmpeg->is);
  }

  ffmpeg->is = stream_open(url, player);
  if (ffmpeg->is != NULL) {
    ffmpeg->is->frame_width = 0;
    ffmpeg->is->frame_height = 0;
    toggle_pause(ffmpeg->is);
  }

  return RET_OK;
}

static ret_t media_player_ffmpeg_start(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, RET_BAD_PARAMS);

  if (ffmpeg->is->paused) {
    toggle_pause(ffmpeg->is);
  }

  return RET_OK;
}

static ret_t media_player_ffmpeg_pause(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, RET_BAD_PARAMS);

  if (!(ffmpeg->is->paused)) {
    toggle_pause(ffmpeg->is);
  }

  return RET_OK;
}

static ret_t media_player_ffmpeg_stop(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, RET_BAD_PARAMS);

  if (ffmpeg->is != NULL) {
    ffmpeg->is->abort_request = 1;
    ffmpeg->is = NULL;
  }

  return RET_OK;
}

static ret_t media_player_ffmpeg_seek(media_player_t* player, uint32_t offset) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, RET_BAD_PARAMS);

  stream_seek(ffmpeg->is, offset * 1000, 0, 0);

  return RET_OK;
}

static ret_t media_player_ffmpeg_set_volume(media_player_t* player, uint32_t volume) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, RET_BAD_PARAMS);

  ffmpeg->is->audio_volume = av_clip(volume, 0, AUDIO_DEVICE_MAXVOLUME);

  return RET_OK;
}

static ret_t media_player_ffmpeg_toggle_mute(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, RET_BAD_PARAMS);

  toggle_mute(ffmpeg->is);

  return RET_OK;
}

static ret_t media_player_ffmpeg_set_on_event(media_player_t* player, event_func_t on_event,
                                              void* ctx) {
  return RET_OK;
}

static void video_display(VideoState* is) {
  bitmap_t* image = is->image;
  struct SwsContext* swsContext = is->swsContext;

  Frame* vp = frame_queue_peek_last(&is->pictq);
  AVFrame* pFrame = vp->frame;

  if (pFrame->width == 0) {
    return;
  }

  if (swsContext == NULL) {
    enum AVPixelFormat format = from_bitmap_format(image->format);
    swsContext = sws_getContext(pFrame->width, pFrame->height, pFrame->format, image->w, image->h,
                                format, 0, NULL, NULL, NULL);
    /*TODO*/
    is->swsContext = swsContext;
  }

  if (swsContext != NULL && image != NULL) {
    uint8_t* buff = bitmap_lock_buffer_for_write(image);
    int32_t line_length = bitmap_get_line_length(image);
    int linesize[8] = {line_length, 0, 0, 0, 0, 0, 0, 0};
    uint8_t* buffers[8] = {buff, NULL, NULL};
    sws_scale(swsContext, (const uint8_t**)pFrame->data, pFrame->linesize, 0, pFrame->height,
              buffers, linesize);
    bitmap_unlock_buffer(image);
  }
}

static ret_t media_player_ffmpeg_get_video_frame(media_player_t* player, bitmap_t* image) {
  double remaining_time = REFRESH_RATE;
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;

  if (ffmpeg->is == NULL || ffmpeg->is->video_st == NULL) {
    return RET_OK;
  }

  ffmpeg->is->image = image;
  video_refresh(ffmpeg->is, &remaining_time);

  return RET_OK;
}

static ret_t media_player_ffmpeg_destroy(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, RET_BAD_PARAMS);

  media_player_stop(player);
  TKMEM_FREE(player);

  return RET_OK;
}

static media_player_state_t media_player_ffmpeg_get_state(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;

  if (ffmpeg->is == NULL) {
    return MEDIA_PLAYER_NONE;
  }

  return (ffmpeg->is->paused) ? MEDIA_PLAYER_PAUSED : MEDIA_PLAYER_PLAYING;
}

static uint32_t media_player_ffmpeg_get_volume(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, 0);

  return ffmpeg->is->audio_volume;
}

static uint32_t media_player_ffmpeg_get_position(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, 0);

  return tk_max(ffmpeg->is->vidclk.pts, ffmpeg->is->audclk.pts) * 1000;
}

static uint32_t media_player_ffmpeg_get_duration(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, 0);

  return ffmpeg->is->ic != NULL ? ffmpeg->is->ic->duration / 1000 : 0;
}

static uint32_t media_player_ffmpeg_get_video_width(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, 0);

  return ffmpeg->is->frame_width;
}

static uint32_t media_player_ffmpeg_get_video_height(media_player_t* player) {
  media_player_ffmpeg_t* ffmpeg = (media_player_ffmpeg_t*)player;
  return_value_if_fail(ffmpeg->is != NULL, 0);

  return ffmpeg->is->frame_height;
}

static const media_player_vtable_t s_media_player_ffmpeg = {
    .load = media_player_ffmpeg_load,
    .start = media_player_ffmpeg_start,
    .pause = media_player_ffmpeg_pause,
    .stop = media_player_ffmpeg_stop,
    .seek = media_player_ffmpeg_seek,
    .set_volume = media_player_ffmpeg_set_volume,
    .toggle_mute = media_player_ffmpeg_toggle_mute,
    .set_on_event = media_player_ffmpeg_set_on_event,
    .get_video_frame = media_player_ffmpeg_get_video_frame,
    .destroy = media_player_ffmpeg_destroy,
    .get_state = media_player_ffmpeg_get_state,
    .get_volume = media_player_ffmpeg_get_volume,
    .get_position = media_player_ffmpeg_get_position,
    .get_duration = media_player_ffmpeg_get_duration,
    .get_video_width = media_player_ffmpeg_get_video_width,
    .get_video_height = media_player_ffmpeg_get_video_height};

media_player_t* media_player_ffmpeg_create(void) {
  media_player_ffmpeg_t* player = TKMEM_ZALLOC(media_player_ffmpeg_t);
  return_value_if_fail(player != NULL, NULL);

  ffmpeg_init();
  player->media_player.vt = &s_media_player_ffmpeg;

  return (media_player_t*)player;
}
