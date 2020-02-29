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

#include "tkc/utils.h"
#include "media_player/lrc/lrc_parser.h"

struct _lrc_parser_t {
  lrc_builder_t* builder;
  const char* str;
  const char* p;
  str_t temp;
};

static ret_t lrc_parser_init(lrc_parser_t* parser, lrc_builder_t* builder, const char* str) {
  return_value_if_fail(builder != NULL && str != NULL, RET_BAD_PARAMS);

  parser->builder = builder;
  parser->str = str;
  parser->p = str;

  return str_init(&(parser->temp), 0) != NULL ? RET_OK : RET_OOM;
}

static ret_t lrc_parser_deinit(lrc_parser_t* parser) {
  return str_reset(&(parser->temp));
}

static ret_t lrc_parser_skip_to_chars(lrc_parser_t* parser, const char* chars) {
  char c = 0;
  while (TRUE) {
    c = parser->p[0];
    if (c == '\0') {
      break;
    }

    if (strchr(chars, c) != NULL) {
      break;
    }

    parser->p++;
  }

  return RET_OK;
}

static ret_t lrc_parser_skip_chars(lrc_parser_t* parser, const char* chars) {
  char c = 0;
  while (TRUE) {
    c = parser->p[0];
    if (c == '\0') {
      break;
    }

    if (strchr(chars, c) == NULL) {
      break;
    }

    parser->p++;
  }

  return RET_OK;
}
static ret_t lrc_parser_skip_text(lrc_parser_t* parser) {
  return lrc_parser_skip_to_chars(parser, "[");
}

static ret_t lrc_parser_parse_text(lrc_parser_t* parser) {
  const char* start = parser->p;

  lrc_parser_skip_text(parser);

  if (start < parser->p) {
    str_set_with_len(&(parser->temp), start, (parser->p - start));
    lrc_builder_on_text(parser->builder, parser->temp.str);
  } else {
    lrc_builder_on_error(parser->builder, "empty text");
  }

  return RET_OK;
}

static ret_t lrc_parser_parse_id_tag(lrc_parser_t* parser) {
  char* value = NULL;
  const char* start = parser->p;
  lrc_parser_skip_to_chars(parser, "]");

  if (start < parser->p) {
    return_value_if_fail(str_set_with_len(&(parser->temp), start, (parser->p - start)) == RET_OK,
                         RET_OOM);

    value = strchr(parser->temp.str, ':');
    if (value != NULL) {
      *value = '\0';
      value++;
      lrc_builder_on_id_tag(parser->builder, parser->temp.str, value);
    } else {
      lrc_builder_on_error(parser->builder, "tag no value");
    }
  } else {
    lrc_builder_on_error(parser->builder, "empty tag");
  }

  return RET_OK;
}

static ret_t lrc_parser_parse_time_tag(lrc_parser_t* parser) {
  char* p = NULL;
  const char* start = parser->p;

  lrc_parser_skip_to_chars(parser, "]");

  if (start < parser->p) {
    double s = 0;
    uint32_t ms = 0;
    uint32_t m = tk_atoi(start);

    return_value_if_fail(str_set_with_len(&(parser->temp), start, (parser->p - start)) == RET_OK,
                         RET_OOM);

    p = strchr(parser->temp.str, ':');
    if (p != NULL) {
      p++;
      s = tk_atof(p);
    }

    ms = m * 60 * 1000 + s * 1000;
    lrc_builder_on_time_tag(parser->builder, ms);
  }

  return RET_OK;
}

static ret_t lrc_parser_parse_tag(lrc_parser_t* parser) {
  lrc_parser_skip_chars(parser, "\t \r\n");

  if (parser->p[0] == '\0') {
    return RET_OK;
  }

  if (isdigit(parser->p[0])) {
    return lrc_parser_parse_time_tag(parser);
  } else {
    return lrc_parser_parse_id_tag(parser);
  }
}

static ret_t lrc_parser_parse_impl(lrc_parser_t* parser) {
  lrc_parser_skip_text(parser);

  while (TRUE) {
    char c = parser->p[0];

    if (c == '\0') {
      break;
    }

    if (c == '[') {
      parser->p++;
      lrc_parser_parse_tag(parser);
      if (parser->p[0] == ']') {
        parser->p++;
      }
    } else {
      lrc_parser_parse_text(parser);
    }
  }

  return RET_OK;
}

ret_t lrc_parser_parse(lrc_builder_t* builder, const char* str) {
  lrc_parser_t p;
  ret_t ret = RET_OK;

  return_value_if_fail(lrc_parser_init(&p, builder, str) == RET_OK, RET_BAD_PARAMS);
  ret = lrc_parser_parse_impl(&p);
  lrc_parser_deinit(&p);

  return ret;
}
