#include "AI.h"
#include "GameUtil.h"
#include <gtest/gtest.h>

namespace {
auto empty_ = game_logic::MoveType::kEmpty;
auto x_player = game_logic::MoveType::kX;
auto ai_player = game_logic::MoveType::kO;

game_logic::AITicTacToe CreateAI() {
  return game_logic::AITicTacToe{ ai_player, x_player, empty_ };
}
}// namespace

TEST(GameUtil, CheckIfFullFalse) {
  game_logic::board_type brd_type;
  game_logic::FillGameBoard(brd_type, empty_);

  EXPECT_FALSE(game_logic::CheckIfFull(brd_type, empty_));
}

TEST(GameUtil, CheckIfFullTrue) {
  game_logic::board_type brd_type;
  game_logic::FillGameBoard(brd_type, ai_player);

  EXPECT_TRUE(game_logic::CheckIfFull(brd_type, empty_));
}

TEST(GameUtil, IsGameOver) {
  game_logic::board_type brd;
  game_logic::FillGameBoard(brd, empty_);

  EXPECT_EQ(game_logic::IsGameOver(brd, empty_), empty_);

  brd[0][0] = brd[0][1] = brd[0][2] = ai_player;
  EXPECT_EQ(game_logic::IsGameOver(brd, empty_), ai_player);

  game_logic::FillGameBoard(brd, empty_);
  brd[1][0] = brd[1][1] = brd[1][2] = ai_player;
  EXPECT_EQ(game_logic::IsGameOver(brd, empty_), ai_player);
}

TEST(GameUtil, MaximumPossiblePathCenter) {
  game_logic::board_type brd;
  game_logic::FillGameBoard(brd, empty_);

  EXPECT_EQ(4, game_logic::MaximumPossiblePath(brd, 1, 1, empty_));
}

TEST(GameUtil, MaximumPossiblePathCorner) {
  game_logic::board_type brd;
  game_logic::FillGameBoard(brd, empty_);

  EXPECT_EQ(3, game_logic::MaximumPossiblePath(brd, 0, 0, empty_));
  EXPECT_EQ(3, game_logic::MaximumPossiblePath(brd, 2, 0, empty_));
  EXPECT_EQ(3, game_logic::MaximumPossiblePath(brd, 0, 2, empty_));
  EXPECT_EQ(3, game_logic::MaximumPossiblePath(brd, 2, 2, empty_));
}

TEST(GameUtil, MaximumPossiblePathNonCorner) {
  game_logic::board_type brd;
  game_logic::FillGameBoard(brd, empty_);

  EXPECT_EQ(2, game_logic::MaximumPossiblePath(brd, 1, 0, empty_));
  EXPECT_EQ(2, game_logic::MaximumPossiblePath(brd, 0, 1, empty_));
  EXPECT_EQ(2, game_logic::MaximumPossiblePath(brd, 2, 1, empty_));
  EXPECT_EQ(2, game_logic::MaximumPossiblePath(brd, 1, 2, empty_));
}

TEST(Ai, EmptyBrdSelectMidPosition) {
  game_logic::board_type brd;
  game_logic::FillGameBoard(brd, empty_);

  game_logic::AITicTacToe computer{ ai_player, x_player, empty_ };

  auto pos = computer.FindNextPosition(brd);
  EXPECT_EQ(pos.first, 1);
  EXPECT_EQ(pos.second, 1);
}

TEST(Ai, SelectWinningPosition) {
  game_logic::board_type brd;
  game_logic::FillGameBoard(brd, empty_);

  /**
   *  ai   0   0
   *  x    ai  0
   *  x    0   0
   */
  brd[0][0] = ai_player;
  brd[2][0] = x_player;
  brd[1][1] = ai_player;
  brd[1][0] = x_player;

  auto ai = CreateAI();
  auto pos = ai.FindNextPosition(brd);
  EXPECT_EQ(pos.first, 2);
  EXPECT_EQ(pos.second, 2);
}

TEST(Ai, PreventWinningPosition) {
  game_logic::board_type brd;
  game_logic::FillGameBoard(brd, empty_);

  /**
   *  x   0   0
   *  ai  x   0
   *  ai  0   0
   */
  brd[0][0] = x_player;
  brd[2][0] = ai_player;
  brd[1][1] = x_player;
  brd[1][0] = ai_player;

  auto ai = CreateAI();
  auto pos = ai.FindNextPosition(brd);
  EXPECT_EQ(pos.first, 2);
  EXPECT_EQ(pos.second, 2);
}