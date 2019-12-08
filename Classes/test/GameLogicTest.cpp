#include "GameLogic.h"
#include "AI.h"
#include "GameUtil.h"
#include "Player.h"
#include <gmock/gmock.h>
#include <utility>

namespace {
class MockPlayer : public game::IPlayer
{
public:
  MockPlayer(util::MoveType type) : game::IPlayer(type) {}
  MOCK_METHOD((std::pair<int, int>), FindNextPosition, (util::board_type & arr), (override));

  void Callback(uint8_t x, uint8_t y, util::MoveType move);

  uint8_t x_{ 255 };
  uint8_t y_{ 255 };
  util::MoveType move_{ util::MoveType::kEmpty };
};
using PlayerMove = std::vector<std::pair<uint8_t, uint8_t>>;

uint8_t expected_x_{ 0 };
uint8_t expected_y_{ 0 };
util::MoveType expected_move_{ util::MoveType::kEmpty };
void Callback(uint8_t x, uint8_t y, util::MoveType move) {
  EXPECT_EQ(expected_x_, x);
  EXPECT_EQ(expected_y_, y);
  EXPECT_EQ(expected_move_, move);
}

void SetParams(uint8_t x, uint8_t y, util::MoveType move) {
  expected_x_ = x;
  expected_y_ = y;
  expected_move_ = move;
}
}// namespace

TEST(GameLogic, TwoPlayers) {
  PlayerMove move1 = { { 0, 0 }, { 0, 1 }, { 0, 2 } };
  PlayerMove move2 = { { 1, 0 }, { 2, 0 }, { 2, 2 } };
  uint8_t m1{ 0 }, m2{ 0 };
  MockPlayer p1(util::MoveType::kX);
  MockPlayer p2(util::MoveType::kO);
  game::GameLogic logic{ &p1, &p2, &Callback };

  EXPECT_CALL(p1, FindNextPosition(testing::_))
    .WillRepeatedly([&](util::board_type &arr) {
      auto pos = move1[m1];
      SetParams(pos.first, pos.second, p1.GetMoveType());
      m1++;
      return pos;
    });

  EXPECT_CALL(p2, FindNextPosition(testing::_))
    .WillRepeatedly([&](util::board_type &arr) {
      auto pos = move2[m2];
      SetParams(pos.first, pos.second, p2.GetMoveType());
      m2++;
      return pos;
    });
  logic.InitGame();
  logic.StartGame();
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (!logic.GameOver());
  util::VectorOfPairs win_pos;
  EXPECT_EQ(logic.Winner(&win_pos), util::MoveType::kX);
  EXPECT_EQ(win_pos.size(), 3);
  EXPECT_EQ(win_pos[0], std::make_pair(0, 0));
  EXPECT_EQ(win_pos[1], std::make_pair(0, 1));
  EXPECT_EQ(win_pos[2], std::make_pair(0, 2));
  logic.StopGame();
}

TEST(GameLogic, PlayWithAi) {
  MockPlayer p1{ util::MoveType::kX };
  EXPECT_CALL(p1, FindNextPosition(testing::_))
    .WillRepeatedly([&](util::board_type &arr) -> std::pair<int, int> {
      for (uint8_t i = 0; i < 3; ++i) {
        for (uint8_t j = 0; j < 3; ++j) {
          if (arr[i][j] == util::MoveType::kEmpty) {
            return std::make_pair(i, j);
          }
        }
      }
      return std::make_pair(-1, -1);
    });
  ai::AITicTacToe tic_tac_toe(util::MoveType::kO, util::MoveType::kX, util::MoveType::kEmpty);
  game::GameLogic logic{ &p1, &tic_tac_toe, [](uint8_t x, uint8_t y, util::MoveType move) {} };
  logic.InitGame();
  logic.StartGame();
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (!logic.GameOver());
  EXPECT_EQ(logic.Winner(), util::MoveType::kO);
  logic.StopGame();
}

TEST(GameLogic, PlayWithAiAiMovesFirst) {
  MockPlayer p1{ util::MoveType::kX };
  EXPECT_CALL(p1, FindNextPosition(testing::_))
    .WillRepeatedly([&](util::board_type &arr) -> std::pair<int, int> {
      for (uint8_t i = 0; i < 3; ++i) {
        for (uint8_t j = 0; j < 3; ++j) {
          if (arr[i][j] == util::MoveType::kEmpty) {
            return std::make_pair(i, j);
          }
        }
      }
      return std::make_pair(-1, -1);
    });
  ai::AITicTacToe tic_tac_toe(util::MoveType::kO, util::MoveType::kX, util::MoveType::kEmpty);
  game::GameLogic logic{ &tic_tac_toe, &p1, [](uint8_t x, uint8_t y, util::MoveType move) {} };
  logic.InitGame();
  logic.StartGame();
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (!logic.GameOver());
  EXPECT_EQ(logic.Winner(), util::MoveType::kO);
  logic.StopGame();
}
