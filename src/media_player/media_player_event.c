/**
 * File:   media_player_event.c
 * Author: AWTK Develop Team
 * Brief:  media_player_event
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
 * 2020-02-19 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "media_player_event.h"

event_t* media_player_loaded_event_init(media_player_loaded_event_t* event, bool_t has_audio,
                                        bool_t has_video, bool_t has_subtitle, uint32_t duration,
                                        uint32_t video_width, uint32_t video_height) {
  return_value_if_fail(event != NULL, NULL);

  memset(event, 0x00, sizeof(media_player_loaded_event_t));
  event->e.type = EVT_MEDIA_PLAYER_LOADED;
  event->has_audio = has_audio;
  event->has_video = has_video;
  event->has_subtitle = has_subtitle;
  event->duration = duration;
  event->video_width = video_width;
  event->video_height = video_height;

  return (event_t*)event;
}

media_player_loaded_event_t* media_player_loaded_event_cast(event_t* event) {
  return_value_if_fail(event != NULL, NULL);
  return_value_if_fail(event->type == EVT_MEDIA_PLAYER_LOADED, NULL);

  return (media_player_loaded_event_t*)event;
}
