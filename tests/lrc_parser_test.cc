#include "gtest/gtest.h"
#include "media_player/lrc/lrc_parser.h"
#include "media_player/lrc/lrc_builder_dump.h"

TEST(LrcParser, id_tag_normall) {
  lrc_builder_t* builder = lrc_builder_dump_create();
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  ASSERT_EQ(lrc_parser_parse(builder, "[author:jim]"), RET_OK);
  ASSERT_STREQ(dump->result.str, "[author:jim]");
  lrc_builder_destroy(builder);
}

TEST(LrcParser, id_tag_empty) {
  lrc_builder_t* builder = lrc_builder_dump_create();
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  ASSERT_EQ(lrc_parser_parse(builder, "[]"), RET_OK);
  ASSERT_STREQ(dump->result.str, "empty tag");
  lrc_builder_destroy(builder);
}

TEST(LrcParser, time_tag1) {
  lrc_builder_t* builder = lrc_builder_dump_create();
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  ASSERT_EQ(lrc_parser_parse(builder, "[1:0]"), RET_OK);
  ASSERT_STREQ(dump->result.str, "[01:0.00]");
  lrc_builder_destroy(builder);
}

TEST(LrcParser, time_tag2) {
  lrc_builder_t* builder = lrc_builder_dump_create();
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  ASSERT_EQ(lrc_parser_parse(builder, "[1:1.0]"), RET_OK);
  ASSERT_STREQ(dump->result.str, "[01:1.00]");
  lrc_builder_destroy(builder);
}

TEST(LrcParser, time_text) {
  lrc_builder_t* builder = lrc_builder_dump_create();
  lrc_builder_dump_t* dump = (lrc_builder_dump_t*)builder;

  ASSERT_EQ(lrc_parser_parse(builder, "[1:1.0]hello"), RET_OK);
  ASSERT_STREQ(dump->result.str, "[01:1.00]hello");
  lrc_builder_destroy(builder);
}
