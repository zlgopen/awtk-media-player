/**
 * File:   audio_decoder_factory.c
 * Author: AWTK Develop Team
 * Brief:  audio decoder factory
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
 * ================================================================
 * 2020-03-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "media_player/base/audio_decoder_factory.h"

static audio_decoder_factory_t* audio_decoder_factory_init(audio_decoder_factory_t* factory);
static ret_t audio_decoder_factory_deinit(audio_decoder_factory_t* factory);

static audio_decoder_factory_t* s_audio_decoder_factory = NULL;

typedef struct _creator_item_t {
  char type[TK_NAME_LEN + 1];
  audio_decoder_create_t create;
} creator_item_t;

static int32_t creator_item_cmp(const creator_item_t* iter, const char* type) {
  return strcmp(iter->type, type);
}

audio_decoder_factory_t* audio_decoder_factory(void) {
  return s_audio_decoder_factory;
}

audio_decoder_factory_t* audio_decoder_factory_create(void) {
  audio_decoder_factory_t* factory = TKMEM_ZALLOC(audio_decoder_factory_t);
  return_value_if_fail(factory != NULL, NULL);

  return audio_decoder_factory_init(factory);
}

static audio_decoder_factory_t* audio_decoder_factory_init(audio_decoder_factory_t* factory) {
  return_value_if_fail(factory != NULL, NULL);

  darray_init(&(factory->creators), 0, default_destroy, (tk_compare_t)creator_item_cmp);

  return factory;
}

ret_t audio_decoder_factory_register(audio_decoder_factory_t* factory, const char* type,
                                     audio_decoder_create_t create) {
  creator_item_t* item = NULL;
  return_value_if_fail(factory != NULL && type != NULL && create != NULL, RET_BAD_PARAMS);

  item = TKMEM_ZALLOC(creator_item_t);
  return_value_if_fail(item != NULL, RET_OOM);

  item->create = create;
  tk_strncpy(item->type, type, TK_NAME_LEN);
  darray_push(&(factory->creators), item);

  return RET_OK;
}

audio_decoder_t* audio_decoder_factory_create_decoder(audio_decoder_factory_t* factory,
                                                      const char* type, data_reader_t* reader) {
  const creator_item_t* iter = NULL;
  return_value_if_fail(factory != NULL && type != NULL && reader != NULL, NULL);

  iter = darray_find(&(factory->creators), (void*)type);
  if (iter != NULL) {
    return iter->create(reader);
  }

  return NULL;
}

ret_t audio_decoder_factory_set(audio_decoder_factory_t* factory) {
  s_audio_decoder_factory = factory;

  return RET_OK;
}

static ret_t audio_decoder_factory_deinit(audio_decoder_factory_t* factory) {
  return_value_if_fail(factory != NULL, RET_BAD_PARAMS);

  darray_deinit(&(factory->creators));

  return RET_OK;
}

ret_t audio_decoder_factory_destroy(audio_decoder_factory_t* factory) {
  return_value_if_fail(factory != NULL, RET_BAD_PARAMS);

  audio_decoder_factory_deinit(factory);
  TKMEM_FREE(factory);

  return RET_OK;
}
