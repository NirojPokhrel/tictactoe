#include <gtest/gtest.h>
#include "AI.h"
#include "GameUtil.h"

namespace
{
auto empty_ = util::MoveType::kEmpty;
auto x_player = util::MoveType::kX;
auto ai_player = util::MoveType::kO;

ai::AITicTacToe CreateAI()
{
  return ai::AITicTacToe{ai_player, x_player, empty_};
}
} // namespace

TEST(GameUtil, CheckIfFullFalse)
{
  util::board_type brd_type;
  util::FillGameBoard(brd_type, empty_);

  EXPECT_FALSE(util::CheckIfFull(brd_type, empty_));
}

TEST(GameUtil, CheckIfFullTrue)
{
  util::board_type brd_type;
  util::FillGameBoard(brd_type, ai_player);

  EXPECT_TRUE(util::CheckIfFull(brd_type, empty_));
}

TEST(GameUtil, IsGameOver)
{
  util::board_type brd;
  util::FillGameBoard(brd, empty_);

  EXPECT_EQ(util::IsGameOver(brd, empty_), empty_);

  brd[0][0] = brd[0][1] = brd[0][2] = ai_player;
  EXPECT_EQ(util::IsGameOver(brd, empty_), ai_player);

  util::FillGameBoard(brd, empty_);
  brd[1][0] = brd[1][1] = brd[1][2] = ai_player;
  EXPECT_EQ(util::IsGameOver(brd, empty_), ai_player);
}

TEST(GameUtil, MaximumPossiblePathCenter)
{
  util::board_type brd;
  util::FillGameBoard(brd, empty_);

  EXPECT_EQ(4, util::MaximumPossiblePath(brd, 1, 1, empty_));
}

TEST(GameUtil, MaximumPossiblePathCorner)
{
  util::board_type brd;
  util::FillGameBoard(brd, empty_);

  EXPECT_EQ(3, util::MaximumPossiblePath(brd, 0, 0, empty_));
  EXPECT_EQ(3, util::MaximumPossiblePath(brd, 2, 0, empty_));
  EXPECT_EQ(3, util::MaximumPossiblePath(brd, 0, 2, empty_));
  EXPECT_EQ(3, util::MaximumPossiblePath(brd, 2, 2, empty_));
}

TEST(GameUtil, MaximumPossiblePathNonCorner)
{
  util::board_type brd;
  util::FillGameBoard(brd, empty_);

  EXPECT_EQ(2, util::MaximumPossiblePath(brd, 1, 0, empty_));
  EXPECT_EQ(2, util::MaximumPossiblePath(brd, 0, 1, empty_));
  EXPECT_EQ(2, util::MaximumPossiblePath(brd, 2, 1, empty_));
  EXPECT_EQ(2, util::MaximumPossiblePath(brd, 1, 2, empty_));
}

TEST(Ai, EmptyBrdSelectMidPosition)
{
  util::board_type brd;
  util::FillGameBoard(brd, empty_);

  ai::AITicTacToe computer{ai_player, x_player, empty_};

  auto pos = computer.FindNextPosition(brd);
  EXPECT_EQ(pos.first, 1);
  EXPECT_EQ(pos.second, 1);
}

TEST(Ai, SelectWinningPosition)
{
  util::board_type brd;
  util::FillGameBoard(brd, empty_);

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

TEST(Ai, PreventWinningPosition)
{
  util::board_type brd;
  util::FillGameBoard(brd, empty_);

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