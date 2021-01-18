/**
 * File:   audio_encoder_factory.c
 * Author: AWTK Develop Team
 * Brief:  audio encoder factory
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
 * 2021-01-18 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "tkc/object_default.h"
#include "media_player/base/audio_encoder_factory.h"

static audio_encoder_factory_t* s_audio_encoder_factory = NULL;

audio_encoder_factory_t* audio_encoder_factory(void) {
  return s_audio_encoder_factory;
}

audio_encoder_factory_t* audio_encoder_factory_create(void) {
  audio_encoder_factory_t* factory = TKMEM_ZALLOC(audio_encoder_factory_t);
  return_value_if_fail(factory != NULL, NULL);

  factory->creators = object_default_create();
  if (factory->creators == NULL) {
    TKMEM_FREE(factory);
  }

  return factory;
}

ret_t audio_encoder_factory_register(audio_encoder_factory_t* factory, const char* type,
                                     audio_encoder_create_t create) {
  return_value_if_fail(type != NULL && create != NULL, RET_BAD_PARAMS);
  return_value_if_fail(factory != NULL && factory->creators != NULL, RET_BAD_PARAMS);

  return object_set_prop_pointer(factory->creators, type, create);
}

audio_encoder_t* audio_encoder_factory_create_encoder(audio_encoder_factory_t* factory,
                                                      const char* type, data_writer_t* writer) {
  audio_encoder_create_t create = NULL;
  return_value_if_fail(type != NULL && writer != NULL, NULL);
  return_value_if_fail(factory != NULL && factory->creators != NULL, NULL);
  create = (audio_encoder_create_t)object_get_prop_pointer(factory->creators, type);
  return_value_if_fail(create != NULL, NULL);

  return create(writer);
}

ret_t audio_encoder_factory_set(audio_encoder_factory_t* factory) {
  s_audio_encoder_factory = factory;

  return RET_OK;
}

ret_t audio_encoder_factory_destroy(audio_encoder_factory_t* factory) {
  return_value_if_fail(factory != NULL, RET_BAD_PARAMS);

  OBJECT_UNREF(factory->creators);
  TKMEM_FREE(factory);

  return RET_OK;
}
