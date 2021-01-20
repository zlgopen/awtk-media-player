/**
 * File:   play_list.h
 * Author: AWTK Develop Team
 * Brief:  play list
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

#ifndef TK_PLAY_LIST_H
#define TK_PLAY_LIST_H

#include "tkc/darray.h"
#include "tkc/types_def.h"

BEGIN_C_DECLS

/**
 * @enum play_mode_t
 * @prefix PLAY_MODE_
 * 播放模式。
 */
typedef enum _play_mode_t {
  /**
   * @const PLAY_MODE_REPEAT_ALL
   * 全部循环。
   */
  PLAY_MODE_REPEAT_ALL = 0,
  /**
   * @const PLAY_MODE_REPEAT_ONE
   * 单曲循环。
   */
  PLAY_MODE_REPEAT_ONE,
  /**
   * @const PLAY_MODE_SHUFFLE
   * 随机播放
   */
  PLAY_MODE_SHUFFLE
} play_mode_t;

struct _play_list_t;
typedef struct _play_list_t play_list_t;

/**
 * @class play_list_t
 * 媒体播放器接口。
 */
struct _play_list_t {
  /**
   * @property {play_mode_t} mode 
   * @annotation ["readable"]
   * 循环模式。
   */
  play_mode_t mode;

  /**
   * @property {uint32_t} curr
   * @annotation ["readable"]
   * 当前曲目序号。
   */
  uint32_t curr;

  /*private*/
  darray_t arr;
};

/**
 * @method play_list_create
 * 创建播放列表对象。
 *
 * @return {play_list_t*} 返回播放列表对象。
 */
play_list_t* play_list_create(void);

/**
 * @method play_list_append
 * 追加一个媒体文件。
 *
 * @param {play_list_t*} list play_list对象。
 * @param {const char*} filename 文件名。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t play_list_append(play_list_t* list, const char* filename);

/**
 * @method play_list_remove
 * 删除指定的媒体文件。
 *
 * @param {play_list_t*} list play_list对象。
 * @param {const char*} filename 文件名。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t play_list_remove(play_list_t* list, const char* filename);

/**
 * @method play_list_get_size
 * 获取曲目个数。
 *
 * @param {play_list_t*} list play_list对象。
 *
 * @return {uint32_t} 返回曲目个数。
 */
uint32_t play_list_get_size(play_list_t* list);

/**
 * @method play_list_next
 * 选择下一首。
 *
 * @param {play_list_t*} list play_list对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t play_list_next(play_list_t* list);

/**
 * @method play_list_prev
 * 选择前一首。
 *
 * @param {play_list_t*} list play_list对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t play_list_prev(play_list_t* list);

/**
 * @method play_list_curr
 * 获取当前曲目的文件名。
 *
 * @param {play_list_t*} list play_list对象。
 *
 * @return {const char*} 返回当前曲目的文件名。
 */
const char* play_list_curr(play_list_t* list);

/**
 * @method play_list_set_play_mode
 * 设置播放模式。
 *
 * @param {play_list_t*} play_list play_list对象。
 * @param {play_mode_t} mode 播放模式。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t play_list_set_play_mode(play_list_t* list, play_mode_t mode);

/**
 * @method play_list_destroy
 * 销毁play list对象。
 *
 * @param {play_list_t*} list play_list对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t play_list_destroy(play_list_t* list);

END_C_DECLS

#endif /*TK_PLAY_LIST_H*/
