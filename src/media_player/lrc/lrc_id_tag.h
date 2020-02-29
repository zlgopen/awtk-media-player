/**
 * File:   lrc_id_tag.h
 * Author: AWTK Develop Team
 * Brief:  lrc id tag
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

#ifndef TK_LRC_ID_TAG_H
#define TK_LRC_ID_TAG_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

/**
 * @class lrc_id_tag_t
 * lrc id tag
 */
typedef struct _lrc_id_tag_t {
  /**
   * @property {const char*} id
   * @annotation ["readable"]
   * ID。
   */
  const char* id;

  /**
   * @property {const char*} value
   * @annotation ["readable"]
   * 值。
   */
  const char* value;
} lrc_id_tag_t;

/**
 * @class lrc_id_tag_list_t
 * lrc id tag list
 */
typedef struct _lrc_id_tag_list_t {
  /*private*/
  uint32_t size;
  uint32_t capacity;
  lrc_id_tag_t* items;
} lrc_id_tag_list_t;

/**
 * @method lrc_id_tag_list_create
 * 创建id tag list对象。
 *
 * @return {lrc_id_tag_list_t*} 返回list对象。
 */
lrc_id_tag_list_t* lrc_id_tag_list_create(void);

/**
 * @method lrc_id_tag_list_append
 * 追加一个tag。
 *
 * @param {lrc_id_tag_list_t*} list lrc_id_tag_list对象。
 * @param {const char*} id id。
 * @param {const char*} value 值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_id_tag_list_append(lrc_id_tag_list_t* list, const char* id, const char* value);

/**
 * @method lrc_id_tag_list_find
 * 查找指定tag的值。
 *
 * @param {lrc_id_tag_list_t*} list lrc_id_tag_list对象。
 * @param {const char*} id id。
 *
 * @return {const char*} 返回值。
 */
const char* lrc_id_tag_list_find(lrc_id_tag_list_t* list, const char* id);

/**
 * @method lrc_id_tag_list_destroy
 * 销毁list对象。
 *
 * @param {lrc_id_tag_list_t*} list lrc_id_tag_list对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_id_tag_list_destroy(lrc_id_tag_list_t* list);

END_C_DECLS

#endif /*TK_LRC_ID_TAG_H*/
