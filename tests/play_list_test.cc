#include "gtest/gtest.h"
#include "media_player/base/play_list.h"

TEST(PlayList, basic) {
  play_list_t* list = play_list_create();

  ASSERT_EQ(play_list_get_size(list), 0);

  play_list_destroy(list);
}

TEST(PlayList, curr) {
  play_list_t* list = play_list_create();

  ASSERT_EQ(play_list_append(list, "a"), RET_OK);
  ASSERT_EQ(play_list_append(list, "b"), RET_OK);
  ASSERT_EQ(play_list_append(list, "c"), RET_OK);
  ASSERT_EQ(play_list_get_size(list), 3);

  list->curr = 0;
  ASSERT_STREQ(play_list_curr(list), "a");

  list->curr = 1;
  ASSERT_STREQ(play_list_curr(list), "b");

  list->curr = 2;
  ASSERT_STREQ(play_list_curr(list), "c");

  play_list_destroy(list);
}

TEST(PlayList, repeat_one) {
  play_list_t* list = play_list_create();

  ASSERT_EQ(play_list_append(list, "a"), RET_OK);
  ASSERT_EQ(play_list_append(list, "b"), RET_OK);
  ASSERT_EQ(play_list_append(list, "c"), RET_OK);

  ASSERT_STREQ(play_list_curr(list), "a");

  list->curr = 1;
  ASSERT_STREQ(play_list_curr(list), "b");

  ASSERT_EQ(play_list_set_play_mode(list, PLAY_MODE_REPEAT_ONE), RET_OK);
  ASSERT_EQ(list->mode, PLAY_MODE_REPEAT_ONE);
  ASSERT_EQ(play_list_next(list), RET_OK);
  ASSERT_STREQ(play_list_curr(list), "b");

  ASSERT_EQ(play_list_prev(list), RET_OK);
  ASSERT_STREQ(play_list_curr(list), "b");

  play_list_destroy(list);
}

TEST(PlayList, repeat_all) {
  play_list_t* list = play_list_create();

  ASSERT_EQ(play_list_append(list, "a"), RET_OK);
  ASSERT_EQ(play_list_append(list, "b"), RET_OK);
  ASSERT_EQ(play_list_append(list, "c"), RET_OK);

  ASSERT_STREQ(play_list_curr(list), "a");

  list->curr = 1;
  ASSERT_STREQ(play_list_curr(list), "b");

  ASSERT_EQ(play_list_set_play_mode(list, PLAY_MODE_REPEAT_ALL), RET_OK);
  ASSERT_EQ(list->mode, PLAY_MODE_REPEAT_ALL);
  ASSERT_EQ(play_list_next(list), RET_OK);
  ASSERT_STREQ(play_list_curr(list), "c");

  ASSERT_EQ(play_list_next(list), RET_OK);
  ASSERT_STREQ(play_list_curr(list), "a");

  ASSERT_EQ(play_list_prev(list), RET_OK);
  ASSERT_STREQ(play_list_curr(list), "c");

  ASSERT_EQ(play_list_prev(list), RET_OK);
  ASSERT_STREQ(play_list_curr(list), "b");

  play_list_destroy(list);
}

TEST(PlayList, repeat_shuffle) {
  play_list_t* list = play_list_create();

  ASSERT_EQ(play_list_append(list, "a"), RET_OK);
  ASSERT_EQ(play_list_append(list, "b"), RET_OK);
  ASSERT_EQ(play_list_append(list, "c"), RET_OK);

  ASSERT_EQ(play_list_set_play_mode(list, PLAY_MODE_SHUFFLE), RET_OK);
  ASSERT_EQ(list->mode, PLAY_MODE_SHUFFLE);

  ASSERT_EQ(play_list_next(list), RET_OK);
  ASSERT_STRNE(play_list_curr(list), "a");

  play_list_destroy(list);
}

TEST(PlayList, remove) {
  play_list_t* list = play_list_create();

  ASSERT_EQ(play_list_append(list, "a"), RET_OK);
  ASSERT_EQ(play_list_append(list, "b"), RET_OK);
  ASSERT_EQ(play_list_append(list, "c"), RET_OK);
  ASSERT_EQ(play_list_get_size(list), 3);

  ASSERT_EQ(play_list_remove(list, "a"), RET_OK);
  ASSERT_EQ(play_list_get_size(list), 2);

  ASSERT_EQ(play_list_remove(list, "c"), RET_OK);
  ASSERT_EQ(play_list_get_size(list), 1);

  ASSERT_EQ(play_list_remove(list, "b"), RET_OK);
  ASSERT_EQ(play_list_get_size(list), 0);

  play_list_destroy(list);
}
