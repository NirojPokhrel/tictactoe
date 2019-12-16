#include "GameLogic.h"
#include "AI.h"
#include "GameUtil.h"
#include "Player.h"
#include <gmock/gmock.h>
#include <utility>

namespace {
class MockPlayer : public game_logic::IPlayer
{
public:
  MockPlayer(game_logic::MoveType type) : game_logic::IPlayer(type) {}
  MOCK_METHOD((std::pair<int, int>), FindNextPosition, (game_logic::board_type & arr), (override));

  void Callback(uint8_t x, uint8_t y, game_logic::MoveType move);

  uint8_t x_{ 255 };
  uint8_t y_{ 255 };
  game_logic::MoveType move_{ game_logic::MoveType::kEmpty };
};
using PlayerMove = std::vector<std::pair<uint8_t, uint8_t>>;

uint8_t expected_x_{ 0 };
uint8_t expected_y_{ 0 };
game_logic::MoveType expected_move_{ game_logic::MoveType::kEmpty };
void Callback(uint8_t x, uint8_t y, game_logic::MoveType move) {
  EXPECT_EQ(expected_x_, x);
  EXPECT_EQ(expected_y_, y);
  EXPECT_EQ(expected_move_, move);
}

void SetParams(uint8_t x, uint8_t y, game_logic::MoveType move) {
  expected_x_ = x;
  expected_y_ = y;
  expected_move_ = move;
}
}// namespace

TEST(GameLogic, TwoPlayers) {
  PlayerMove move1 = { { 0, 0 }, { 0, 1 }, { 0, 2 } };
  PlayerMove move2 = { { 1, 0 }, { 2, 0 }, { 2, 2 } };
  uint8_t m1{ 0 }, m2{ 0 };
  MockPlayer p1(game_logic::MoveType::kX);
  MockPlayer p2(game_logic::MoveType::kO);
  game_logic::GameLogic logic{ &p1, &p2, &Callback };

  EXPECT_CALL(p1, FindNextPosition(testing::_))
    .WillRepeatedly([&](game_logic::board_type &arr) {
      auto pos = move1[m1];
      SetParams(pos.first, pos.second, p1.GetMoveType());
      m1++;
      return pos;
    });

  EXPECT_CALL(p2, FindNextPosition(testing::_))
    .WillRepeatedly([&](game_logic::board_type &arr) {
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
  game_logic::VectorOfPairs win_pos;
  EXPECT_EQ(logic.Winner(&win_pos), game_logic::MoveType::kX);
  EXPECT_EQ(win_pos.size(), 3);
  EXPECT_EQ(win_pos[0], std::make_pair(0, 0));
  EXPECT_EQ(win_pos[1], std::make_pair(0, 1));
  EXPECT_EQ(win_pos[2], std::make_pair(0, 2));
  logic.StopGame();
}

TEST(GameLogic, PlayWithAi) {
  MockPlayer p1{ game_logic::MoveType::kX };
  EXPECT_CALL(p1, FindNextPosition(testing::_))
    .WillRepeatedly([&](game_logic::board_type &arr) -> std::pair<int, int> {
      for (uint8_t i = 0; i < 3; ++i) {
        for (uint8_t j = 0; j < 3; ++j) {
          if (arr[i][j] == game_logic::MoveType::kEmpty) {
            return std::make_pair(i, j);
          }
        }
      }
      return std::make_pair(-1, -1);
    });
  game_logic::AITicTacToe tic_tac_toe(game_logic::MoveType::kO, game_logic::MoveType::kX, game_logic::MoveType::kEmpty);
  game_logic::GameLogic logic{ &p1, &tic_tac_toe, [](uint8_t x, uint8_t y, game_logic::MoveType move) {} };
  logic.InitGame();
  logic.StartGame();
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (!logic.GameOver());
  EXPECT_EQ(logic.Winner(), game_logic::MoveType::kO);
  logic.StopGame();
}

TEST(GameLogic, PlayWithAiAiMovesFirst) {
  MockPlayer p1{ game_logic::MoveType::kX };
  EXPECT_CALL(p1, FindNextPosition(testing::_))
    .WillRepeatedly([&](game_logic::board_type &arr) -> std::pair<int, int> {
      for (uint8_t i = 0; i < 3; ++i) {
        for (uint8_t j = 0; j < 3; ++j) {
          if (arr[i][j] == game_logic::MoveType::kEmpty) {
            return std::make_pair(i, j);
          }
        }
      }
      return std::make_pair(-1, -1);
    });
  game_logic::AITicTacToe tic_tac_toe(game_logic::MoveType::kO, game_logic::MoveType::kX, game_logic::MoveType::kEmpty);
  game_logic::GameLogic logic{ &tic_tac_toe, &p1, [](uint8_t x, uint8_t y, game_logic::MoveType move) {} };
  logic.InitGame();
  logic.StartGame();
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (!logic.GameOver());
  EXPECT_EQ(logic.Winner(), game_logic::MoveType::kO);
  logic.StopGame();
}
