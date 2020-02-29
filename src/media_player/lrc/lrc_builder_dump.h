/**
 * File:   lrc_builder_dump.h
 * Author: AWTK Develop Team
 * Brief:  lrc builder dump
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

#ifndef TK_LRC_BUILDER_DUMP_H
#define TK_LRC_BUILDER_DUMP_H

#include "tkc/str.h"
#include "media_player/lrc/lrc_builder.h"

BEGIN_C_DECLS

/**
 * @class lrc_builder_dump_t
 * lrc builder dump
 */
typedef struct _lrc_builder_dump_t {
  lrc_builder_t lrc_builder;
  str_t result;
} lrc_builder_dump_t;
;

/**
 * @method lrc_builder_dump_create
 * 创建builder对象。
 *
 * @return {lrc_builder_t*} 返回builder对象。
 */
lrc_builder_t* lrc_builder_dump_create(void);

END_C_DECLS

#endif /*TK_LRC_BUILDER_DUMP_H*/
