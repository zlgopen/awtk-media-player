/**
 * File:   media_player.c
 * Author: AWTK Develop Team
 * Brief:  media_player
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
#include "media_player.h"

ret_t media_player_load(media_player_t* player, const char* url) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->load != NULL, RET_BAD_PARAMS);
  return_value_if_fail(url != NULL, RET_BAD_PARAMS);

  return player->vt->load(player, url);
}

ret_t media_player_start(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->start != NULL, RET_BAD_PARAMS);

  return player->vt->start(player);
}

ret_t media_player_pause(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->pause != NULL, RET_BAD_PARAMS);

  return player->vt->pause(player);
}

ret_t media_player_stop(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->stop != NULL, RET_BAD_PARAMS);

  return player->vt->stop(player);
}

ret_t media_player_seek(media_player_t* player, uint32_t position) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->seek != NULL, RET_BAD_PARAMS);

  return player->vt->seek(player, position);
}

ret_t media_player_set_volume(media_player_t* player, uint32_t volume) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->set_volume != NULL, RET_BAD_PARAMS);

  return player->vt->set_volume(player, volume);
}

ret_t media_player_toggle_mute(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->toggle_mute != NULL, RET_BAD_PARAMS);

  return player->vt->toggle_mute(player);
}

ret_t media_player_set_on_event(media_player_t* player, event_func_t on_event, void* ctx) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);

  player->on_event_ctx = ctx;
  player->on_event = on_event;

  if (player->vt->set_on_event != NULL) {
    return player->vt->set_on_event(player, on_event, ctx);
  }

  return RET_OK;
}

ret_t media_player_notify_simple(media_player_t* player, uint32_t event_type) {
  event_t e = event_init(event_type, player);

  return media_player_notify(player, &e);
}

ret_t media_player_notify(media_player_t* player, event_t* e) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);

  if (player->on_event != NULL) {
    return player->on_event(player->on_event_ctx, e);
  }

  return RET_OK;
}

ret_t media_player_get_video_frame(media_player_t* player, bitmap_t* image) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->get_video_frame != NULL, RET_BAD_PARAMS);
  return_value_if_fail(image != NULL, RET_BAD_PARAMS);

  return player->vt->get_video_frame(player, image);
}

ret_t media_player_destroy(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, RET_BAD_PARAMS);
  return_value_if_fail(player->vt->destroy != NULL, RET_BAD_PARAMS);

  return player->vt->destroy(player);
}

media_player_state_t media_player_get_state(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, MEDIA_PLAYER_NONE);
  return_value_if_fail(player->vt->get_state != NULL, MEDIA_PLAYER_NONE);

  return player->vt->get_state(player);
}

uint32_t media_player_get_volume(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, 0);
  return_value_if_fail(player->vt->get_volume != NULL, 0);

  return player->vt->get_volume(player);
}

uint32_t media_player_get_position(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, 0);
  return_value_if_fail(player->vt->get_position != NULL, 0);

  return player->vt->get_position(player);
}

uint32_t media_player_get_duration(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, 0);
  return_value_if_fail(player->vt->get_duration != NULL, 0);

  return player->vt->get_duration(player);
}

uint32_t media_player_get_video_width(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, 0);
  return_value_if_fail(player->vt->get_video_width != NULL, 0);

  return player->vt->get_video_width(player);
}

uint32_t media_player_get_video_height(media_player_t* player) {
  return_value_if_fail(player != NULL && player->vt != NULL, 0);
  return_value_if_fail(player->vt->get_video_height != NULL, 0);

  return player->vt->get_video_height(player);
}
