#include "gtest/gtest.h"
#include "media_player/lrc/lrc.h"

TEST(Lrc, basic) {
  lrc_t* lrc = lrc_create("[1:2]hello");

  ASSERT_EQ(lrc != NULL, true);
  ASSERT_EQ(lrc->time_tags->size, 1);
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 62 * 1000), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 63 * 1000), "hello");

  lrc_destroy(lrc);
}

TEST(Lrc, basic1) {
  lrc_t* lrc = lrc_create("[1:2]hello\n[1:4]world\n");

  ASSERT_EQ(lrc != NULL, true);
  ASSERT_EQ(lrc->time_tags->size, 2);
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 62 * 1000), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 63 * 1000), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 64 * 1000), "world");

  lrc_destroy(lrc);
}

TEST(Lrc, basic2) {
  lrc_t* lrc = lrc_create("[author:jim]\r\n[name:song]\n[1:2]hello\n[1:4]world\n");

  ASSERT_EQ(lrc != NULL, true);
  ASSERT_EQ(lrc->time_tags->size, 2);
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 62 * 1000), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 63 * 1000), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(lrc->time_tags, 64 * 1000), "world");
  ASSERT_STREQ(lrc_id_tag_list_find(lrc->id_tags, "name"), "song");
  ASSERT_STREQ(lrc_id_tag_list_find(lrc->id_tags, "author"), "jim");

  lrc_destroy(lrc);
}
