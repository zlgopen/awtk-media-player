/**
 * File:   lrc_parser.h
 * Author: AWTK Develop Team
 * Brief:  play parser
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

#ifndef TK_LRC_PARSER_H
#define TK_LRC_PARSER_H

#include "tkc/str.h"
#include "media_player/lrc/lrc_builder.h"

BEGIN_C_DECLS

/**
 * @class lrc_parser_t
 * lrc parser
 */
struct _lrc_parser_t;
typedef struct _lrc_parser_t lrc_parser_t;

/**
 * @method lrc_parser_parse
 * 解析歌词。
 *
 * @param {lrc_builder_t*} builder builder对象。
 * @param {const char*} str 歌词数据。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t lrc_parser_parse(lrc_builder_t* builder, const char* str);

END_C_DECLS

#endif /*TK_LRC_PARSER_H*/
