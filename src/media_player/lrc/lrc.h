/**
 * File:   lrc.h
 * Author: AWTK Develop Team
 * Brief:  lrc
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

#ifndef TK_LRC_H
#define TK_LRC_H

#include "media_player/lrc/lrc_id_tag.h"
#include "media_player/lrc/lrc_time_tag.h"

BEGIN_C_DECLS

/**
 * @class lrc_t
 * lrc
 */
typedef struct _lrc_t {
  /**
   * @property {lrc_id_tag_list_t*} id_tags
   * @annotation ["readable"]
   * id tags。
   */
  lrc_id_tag_list_t* id_tags;

  /**
   * @property {lrc_time_tag_list_t*} time_tags
   * @annotation ["readable"]
   * time tags。
   */
  lrc_time_tag_list_t* time_tags;

  /*private*/
  char* strs;
} lrc_t;

/**
 * @method lrc_create
 * 创建lrc对象。
 * @param {const char*} text 歌词文本。
 *
 * @return {lrc_t*} 返回list对象。
 */
lrc_t* lrc_create(const char* text);

/**
 * @method lrc_destroy
 * 销毁lrc对象。
 *
 * @param {lrc_t*} list lrc对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_destroy(lrc_t* list);

#define LRC_ID_BY "by"
#define LRC_ID_TITLE "ti"
#define LRC_ID_AUTHOR "ar"

END_C_DECLS

#endif /*TK_LRC_H*/
