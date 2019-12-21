#pragma once

#include "GameUtil.h"
#include "Player.h"
#include <atomic>
#include <functional>
#include <future>
#include <mutex>

namespace game_logic {
using callback_type = std::function<void(uint8_t x, uint8_t y, game_logic::MoveType move)>;
class GameLogic
{
public:
  /// constructor GameLogic
  /// @p1 - Interface to the first player
  /// @p2 - Interface to the secocnd player
  /// @ui_callback - callback to the UI
  GameLogic(game_logic::IPlayer* p1, game_logic::IPlayer* p2, callback_type ui_callback) : p1_(p1), p2_(p2), ui_callback_(ui_callback) {}

  /// default destructor - stops the game if it is running
  ~GameLogic() {
    StopGame();
    if (game_task_.valid()) {
      game_task_.get();
    }
  }

  /// Initialize the game
  void InitGame();

  /// Start the game loop
  void StartGame();

  /// Get the winner of the game if one, otherwise return the empty type
  /// @win_pos - if win_pos is provided, then the function will return the winning position
  game_logic::MoveType Winner(game_logic::VectorOfPairs* win_pos = nullptr) const;

  /// IsGameDraw
  /// @returns true - if no move left and there is no winner
  /// @returns false - if either move is left or there is a winner
  bool IsGameDraw() const;

  /// StopGame - Stop the game logic
  void StopGame();

  /// GameOver - Check if the game is over or if the game logic is still running
  bool GameOver() const {
    return game_over_;
  }

  /// IsPositionEmpty - check if the position is empty
  /// @x : X-axis coordinate of the point
  /// @y : Y-axis coordinate of the point
  /// @returns true - if the position (x, y) is empty
  /// @returns false - if the position (x, y) is not empty
  bool IsPositionEmpty(int x, int y) const;

private:
  void RunGameLogic();
  bool MakeMove(game_logic::IPlayer* player);
  mutable std::mutex data_mtx_;
  game_logic::board_type game_;// 3x3 game board, cross-thread, needs protection
  game_logic::IPlayer* p1_;// player 1
  game_logic::IPlayer* p2_;// player 2
  std::atomic<bool> game_started_{ false };// check if the game has started
  std::atomic<bool> game_over_{ false };// check if the game is over
  std::future<void> game_task_;// future returned by async task
  const callback_type ui_callback_;// callback to the UI interface for updating UI
};
}// namespace game_logic
