/**
 * File:   lrc_builder.h
 * Author: AWTK Develop Team
 * Brief:  lrc builder interface
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
 * 2020-02-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_LRC_BUILDER_H
#define TK_LRC_BUILDER_H

#include "tkc/types_def.h"

BEGIN_C_DECLS

struct _lrc_builder_t;
typedef struct _lrc_builder_t lrc_builder_t;

typedef ret_t (*lrc_builder_on_id_tag_t)(lrc_builder_t* builder, const char* key,
                                         const char* value);
typedef ret_t (*lrc_builder_on_time_tag_t)(lrc_builder_t* builder, uint32_t start_time);
typedef ret_t (*lrc_builder_on_text_t)(lrc_builder_t* builder, const char* text);
typedef ret_t (*lrc_builder_on_error_t)(lrc_builder_t* builder, const char* error);
typedef ret_t (*lrc_builder_destroy_t)(lrc_builder_t* builder);

typedef struct _lrc_builder_vtable_t {
  lrc_builder_on_text_t on_text;
  lrc_builder_on_error_t on_error;
  lrc_builder_on_id_tag_t on_id_tag;
  lrc_builder_on_time_tag_t on_time_tag;
  lrc_builder_destroy_t destroy;
} lrc_builder_vtable_t;

/**
 * @class lrc_builder_t
 * lrc builder
 */
struct _lrc_builder_t {
  const lrc_builder_vtable_t* vt;
};

/**
 * @method lrc_builder_on_id_tag
 * 处理id标签。
 *
 * @param {lrc_builder_t*} builder lrc_builder对象。
 * @param {const char*} id 名称。
 * @param {const char*} value 值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_builder_on_id_tag(lrc_builder_t* builder, const char* id, const char* value);

/**
 * @method lrc_builder_on_time_tag
 * 处理time标签。
 *
 * @param {lrc_builder_t*} builder lrc_builder对象。
 * @param {uint32_t} timestamp 时间。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_builder_on_time_tag(lrc_builder_t* builder, uint32_t timestamp);

/**
 * @method lrc_builder_on_text
 * 处理歌词。
 *
 * @param {lrc_builder_t*} builder lrc_builder对象。
 * @param {const char*} text 歌词。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_builder_on_text(lrc_builder_t* builder, const char* text);

/**
 * @method lrc_builder_on_error
 * 处理错误。
 *
 * @param {lrc_builder_t*} builder lrc_builder对象。
 * @param {const char*} error 错误。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_builder_on_error(lrc_builder_t* builder, const char* error);

/**
 * @method lrc_builder_destroy
 * 销毁lrc builder对象。
 *
 * @param {lrc_builder_t*} builder lrc_builder对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_builder_destroy(lrc_builder_t* builder);

END_C_DECLS

#endif /*TK_LRC_BUILDER_H*/
