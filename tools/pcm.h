/**
 * File:   pcm.h
 * Author: AWTK Develop Team
 * Brief:  pcm
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

#ifndef TK_PCM_H
#define TK_PCM_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

/**
 * @class pcm_header_t
 * pcm
 */
typedef struct _pcm_header_t {
  /**
   * @property {uint32_t} version
   * @annotation ["readable"]
   * version。
   */
  uint32_t version;
  /**
   * @property {uint32_t} samplerate
   * @annotation ["readable"]
   * 采样率。
   */
  uint32_t samplerate;
  /**
   * @property {uint32_t} samples
   * @annotation ["readable"]
   * 采样数。
   */
  uint32_t samples;
  /**
   * @property {uint16_t} channels
   * @annotation ["readable"]
   * 通道数。
   */
  uint16_t channels;
  /**
   * @property {uint16_t} reserved
   * @annotation ["readable"]
   * reserved
   */
  uint16_t reserved;
} pcm_header_t;

END_C_DECLS

#endif /*TK_PCM_H*/
