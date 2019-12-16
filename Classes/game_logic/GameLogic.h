#pragma once

#include "GameUtil.h"
#include "Player.h"
#include <atomic>
#include <functional>
#include <future>

namespace game_logic {
using callback_type = std::function<void(uint8_t x, uint8_t y, game_logic::MoveType move)>;
class GameLogic
{
public:
  GameLogic(game_logic::IPlayer* p1, game_logic::IPlayer* p2, callback_type ui_callback) : p1_(p1), p2_(p2), ui_callback_(ui_callback) {}
  ~GameLogic() {
    StopGame();
    if (game_task_.valid()) {
      game_task_.get();
    }
  }
  void InitGame();
  void StartGame();
  game_logic::MoveType Winner(game_logic::VectorOfPairs* win_pos = nullptr) const;
  bool IsGameDraw() const;
  void StopGame();
  bool GameOver() const {
    return game_over_;
  }
  bool IsPositionEmpty(int x, int y) const;

private:
  void RunGameLogic();
  bool MakeMove(game_logic::IPlayer* player);
  game_logic::board_type game_;// 3x3 game board
  game_logic::IPlayer* p1_;// player 1
  game_logic::IPlayer* p2_;// player 2
  std::atomic<bool> game_started_{ false };
  std::atomic<bool> game_over_{ false };
  std::future<void> game_task_;
  const callback_type ui_callback_;
};
}// namespace game_logic
