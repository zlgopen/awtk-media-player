/**
 * File:   lrc_time_tag.h
 * Author: AWTK Develop Team
 * Brief:  lrc time tag
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

#ifndef TK_LRC_TIME_TAG_H
#define TK_LRC_TIME_TAG_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

/**
 * @class lrc_time_tag_t
 * lrc time tag
 */
typedef struct _lrc_time_tag_t {
  /**
   * @property {uint32_t} timestamp
   * @annotation ["readable"]
   * time stamp。
   */
  uint32_t timestamp;

  /**
   * @property {const char*} text
   * @annotation ["readable"]
   * 文本。
   */
  const char* text;
} lrc_time_tag_t;

/**
 * @class lrc_time_tag_list_t
 * lrc time tag list
 */
typedef struct _lrc_time_tag_list_t {
  /*private*/
  uint32_t size;
  uint32_t cursor;
  uint32_t capacity;
  lrc_time_tag_t* items;
} lrc_time_tag_list_t;

/**
 * @method lrc_time_tag_list_create
 * 创建time tag list对象。
 *
 * @return {lrc_time_tag_list_t*} 返回list对象。
 */
lrc_time_tag_list_t* lrc_time_tag_list_create(void);

/**
 * @method lrc_time_tag_list_append
 * 追加一个tag。
 *
 * @param {lrc_time_tag_list_t*} list lrc_time_tag_list对象。
 * @param {uint32_t} timestamp 时间。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_time_tag_list_append(lrc_time_tag_list_t* list, uint32_t timestamp);

/**
 * @method lrc_time_tag_list_set_text
 * 设置没有text的tag的text。
 *
 * @param {lrc_time_tag_list_t*} list lrc_time_tag_list对象。
 * @param {const char*} text 文本。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_time_tag_list_set_text(lrc_time_tag_list_t* list, const char* text);

/**
 * @method lrc_time_tag_list_sort
 * 按时间对tag进行排序。
 *
 * @param {lrc_time_tag_list_t*} list lrc_time_tag_list对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_time_tag_list_sort(lrc_time_tag_list_t* list);

/**
 * @method lrc_time_tag_list_find
 * 查找指定tag的值。
 *
 * @param {lrc_time_tag_list_t*} list lrc_time_tag_list对象。
 * @param {uint32_t} time time。
 *
 * @return {const char*} 返回值。
 */
const char* lrc_time_tag_list_find(lrc_time_tag_list_t* list, uint32_t timestamp);

/**
 * @method lrc_time_tag_list_destroy
 * 销毁list对象。
 *
 * @param {lrc_time_tag_list_t*} list lrc_time_tag_list对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_time_tag_list_destroy(lrc_time_tag_list_t* list);

END_C_DECLS

#endif /*TK_LRC_TIME_TAG_H*/
