#pragma once

#include "GameUtil.h"
#include <atomic>
#include <functional>
#include <future>
#include "Player.h"

namespace game {
using callback_type = std::function<void(uint8_t x, uint8_t y, util::MoveType move)>;
class GameLogic {
 public:
  GameLogic(game::IPlayer* p1, game::IPlayer* p2, callback_type ui_callback) :
    p1_(p1)
  , p2_(p2)
  , ui_callback_(ui_callback) {}
  ~GameLogic() {
    StopGame();
  }
  void InitGame();
  void StartGame();
  util::MoveType Winner() const;
  bool IsGameDraw() const;
  void StopGame();
  bool GameOver() const {
    return game_over_;
  }

  private:
    void RunGameLogic();
    bool MakeMove(game::IPlayer* player);
    util::board_type game_;  // 3x3 game board
    game::IPlayer* p1_; // player 1
    game::IPlayer* p2_; // player 2
    std::atomic<bool> game_started_{false};
    std::atomic<bool> game_over_{false};
    std::future<void> game_task_;
    const callback_type ui_callback_;
};
}