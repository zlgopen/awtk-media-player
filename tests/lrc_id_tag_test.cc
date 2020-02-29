#include "gtest/gtest.h"
#include "media_player/lrc/lrc_id_tag.h"

TEST(LrcIdTag, basic) {
  lrc_id_tag_list_t* list = lrc_id_tag_list_create();
  ASSERT_EQ(list->size, 0);
  ASSERT_EQ(lrc_id_tag_list_append(list, "name", "song"), RET_OK);
  ASSERT_EQ(lrc_id_tag_list_append(list, "author", "jim"), RET_OK);
  ASSERT_EQ(list->size, 2);

  ASSERT_STREQ(lrc_id_tag_list_find(list, "name"), "song");
  ASSERT_STREQ(lrc_id_tag_list_find(list, "author"), "jim");
  ASSERT_EQ(lrc_id_tag_list_find(list, "none"), (const char*)NULL);

  lrc_id_tag_list_destroy(list);
}
