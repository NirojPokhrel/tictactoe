#include "HumanPlayer.h"
#include "GameUtil.h"
#include <future>
#include <gtest/gtest.h>

TEST(HumanPlayer, TestSendingUpdateFirst) {
  game_logic::HumanPlayer player(game_logic::MoveType::kX);

  player.UpdatePosition(3, 4);
  game_logic::board_type brd;
  auto pos = player.FindNextPosition(brd);
  EXPECT_EQ(pos, std::make_pair(3, 4));
}

TEST(HumanPlayer, WaitForEvent) {
  game_logic::HumanPlayer player(game_logic::MoveType::kX);
  auto fut = std::async(std::launch::async, [&]() {
    game_logic::board_type brd;
    return player.FindNextPosition(brd);
  });
  std::this_thread::yield();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));// let other thread call FindNextPosition first
  player.UpdatePosition(3, 4);
  auto pos = fut.get();
  EXPECT_EQ(pos, std::make_pair(3, 4));
}