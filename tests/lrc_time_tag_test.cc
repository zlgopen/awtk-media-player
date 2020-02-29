#include "gtest/gtest.h"
#include "media_player/lrc/lrc_time_tag.h"

TEST(LrcTimeTag, basic) {
  lrc_time_tag_list_t* list = lrc_time_tag_list_create();

  ASSERT_EQ(list->size, 0);
  ASSERT_EQ(lrc_time_tag_list_append(list, 20), RET_OK);
  ASSERT_EQ(lrc_time_tag_list_append(list, 10), RET_OK);
  ASSERT_EQ(lrc_time_tag_list_append(list, 30), RET_OK);
  ASSERT_EQ(lrc_time_tag_list_set_text(list, "hello"), RET_OK);
  ASSERT_EQ(list->size, 3);

  ASSERT_EQ(lrc_time_tag_list_append(list, 50), RET_OK);
  ASSERT_EQ(lrc_time_tag_list_append(list, 40), RET_OK);
  ASSERT_EQ(lrc_time_tag_list_append(list, 60), RET_OK);
  ASSERT_EQ(lrc_time_tag_list_set_text(list, "world"), RET_OK);
  ASSERT_EQ(list->size, 6);

  ASSERT_EQ(lrc_time_tag_list_sort(list), RET_OK);

  ASSERT_EQ(list->items[0].timestamp, 10);
  ASSERT_EQ(list->items[1].timestamp, 20);
  ASSERT_EQ(list->items[2].timestamp, 30);
  ASSERT_EQ(list->items[3].timestamp, 40);
  ASSERT_EQ(list->items[4].timestamp, 50);
  ASSERT_EQ(list->items[5].timestamp, 60);

  ASSERT_EQ(lrc_time_tag_list_find(list, 0), (const char*)NULL);
  ASSERT_EQ(lrc_time_tag_list_find(list, 9), (const char*)NULL);
  ASSERT_STREQ(lrc_time_tag_list_find(list, 10), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(list, 19), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(list, 29), "hello");
  ASSERT_STREQ(lrc_time_tag_list_find(list, 40), "world");
  ASSERT_STREQ(lrc_time_tag_list_find(list, 49), "world");
  ASSERT_STREQ(lrc_time_tag_list_find(list, 100), "world");

  lrc_time_tag_list_destroy(list);
}
