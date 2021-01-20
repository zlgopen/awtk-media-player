/**
 * File:   audio_device.c
 * Author: AWTK Develop Team
 * Brief:  audio device interface
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
 * 2020-02-21 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/time_now.h"
#include "audio_device.h"

ret_t audio_device_mix(audio_device_t* device, uint8_t* dst, const uint8_t* src, uint32_t len) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->mix != NULL, RET_BAD_PARAMS);
  return_value_if_fail(dst != NULL && src != NULL, RET_BAD_PARAMS);

  return device->vt->mix(device, dst, src, len);
}

uint32_t audio_device_dequeue_data(audio_device_t* device, void* data, uint32_t len) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->dequeue_data != NULL, RET_BAD_PARAMS);
  return_value_if_fail(data != NULL, RET_BAD_PARAMS);

  return device->vt->dequeue_data(device, data, len);
}

uint32_t audio_device_dequeue_data_len(audio_device_t* device, void* buff, uint32_t len, uint32_t timeout_ms) {
  uint32_t now = 0;
  uint32_t end = 0;
  int32_t offset = 0;
  int32_t read_bytes = 0;
  uint32_t max_size = len;
  int32_t remain_bytes = max_size;
  uint8_t* p = (uint8_t*)buff;
  return_value_if_fail(buff != NULL, 0);
  return_value_if_fail(buff != NULL && device != NULL, -1);

  now = time_now_ms();
  end = now + timeout_ms;

  do {
    read_bytes = audio_device_dequeue_data(device, p + offset, remain_bytes);

    now = time_now_ms();
    if (read_bytes == 0) {
      if (now > end) {
        break;
      }
      sleep_ms(10);
      continue;
    }

    offset += read_bytes;
    remain_bytes -= read_bytes;

    if (remain_bytes == 0) {
      break;
    }

    if (now > end) {
      break;
    }
  } while (remain_bytes > 0);
    
  if(len != offset) {
    log_debug("read: %d/%u\n", offset, max_size);
  }

  return offset;
}

int32_t audio_device_queue_data(audio_device_t* device, const void* data, uint32_t len) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->queue_data != NULL, RET_BAD_PARAMS);
  return_value_if_fail(data != NULL, RET_BAD_PARAMS);

  return device->vt->queue_data(device, data, len);
}

uint32_t audio_device_get_queued_data_size(audio_device_t* device) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->get_queued_data_size != NULL,
                       RET_BAD_PARAMS);

  return device->vt->get_queued_data_size(device);
}

ret_t audio_device_clear_queued_data(audio_device_t* device) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->clear_queued_data != NULL, RET_BAD_PARAMS);

  return device->vt->clear_queued_data(device);
}

ret_t audio_device_start(audio_device_t* device) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->start != NULL, RET_BAD_PARAMS);

  return device->vt->start(device);
}

ret_t audio_device_pause(audio_device_t* device) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->pause != NULL, RET_BAD_PARAMS);

  return device->vt->pause(device);
}

ret_t audio_device_set_volume(audio_device_t* device, uint32_t volume) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL, RET_BAD_PARAMS);

  device->volume = volume;
  if (device->vt->set_volume != NULL) {
    return device->vt->set_volume(device, volume);
  }

  return RET_OK;
}

ret_t audio_device_destroy(audio_device_t* device) {
  return_value_if_fail(device != NULL, RET_BAD_PARAMS);
  return_value_if_fail(device->vt != NULL && device->vt->destroy != NULL, RET_BAD_PARAMS);

  return device->vt->destroy(device);
}
