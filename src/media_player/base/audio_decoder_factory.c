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
#include "tkc/object_default.h"
#include "media_player/base/audio_decoder_factory.h"

static audio_decoder_factory_t* s_audio_decoder_factory = NULL;

audio_decoder_factory_t* audio_decoder_factory(void) {
  return s_audio_decoder_factory;
}

audio_decoder_factory_t* audio_decoder_factory_create(void) {
  audio_decoder_factory_t* factory = TKMEM_ZALLOC(audio_decoder_factory_t);
  return_value_if_fail(factory != NULL, NULL);

  factory->creators = object_default_create();
  if (factory->creators == NULL) {
    TKMEM_FREE(factory);
  }

  return factory;
}

ret_t audio_decoder_factory_register(audio_decoder_factory_t* factory, const char* type,
                                     audio_decoder_create_t create) {
  return_value_if_fail(type != NULL && create != NULL, RET_BAD_PARAMS);
  return_value_if_fail(factory != NULL && factory->creators != NULL, RET_BAD_PARAMS);

  return object_set_prop_pointer(factory->creators, type, create);
}

audio_decoder_t* audio_decoder_factory_create_decoder(audio_decoder_factory_t* factory,
                                                      const char* type, data_reader_t* reader) {
  audio_decoder_create_t create = NULL;
  return_value_if_fail(type != NULL && reader != NULL, NULL);
  return_value_if_fail(factory != NULL && factory->creators != NULL, NULL);
  create = (audio_decoder_create_t)object_get_prop_pointer(factory->creators, type);
  return_value_if_fail(create != NULL, NULL);

  return create(reader);
}

ret_t audio_decoder_factory_set(audio_decoder_factory_t* factory) {
  s_audio_decoder_factory = factory;

  return RET_OK;
}

ret_t audio_decoder_factory_destroy(audio_decoder_factory_t* factory) {
  return_value_if_fail(factory != NULL, RET_BAD_PARAMS);

  OBJECT_UNREF(factory->creators);
  TKMEM_FREE(factory);

  return RET_OK;
}
