#pragma once

#include "GameUtil.h"
#include "Player.h"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <utility>

namespace game_logic {
class HumanPlayer : public game_logic::IPlayer
{
public:
  /// HumanPlayer - Constructor for the HumanPlayer
  /// @move - Set the move type for the HumanPlayer
  HumanPlayer(game_logic::MoveType move) : game_logic::IPlayer(move) {}

  /// InterruptGame - Interrupt the waiting for the USER input
  void InterruptGame() {
    std::lock_guard<std::mutex> _(mtx_);
    stop_game_ = true;
    cv_.notify_one();
  }

  /// FindNextPosition - Wait for the next position selected by human player
  /// @arr - 3x3 board position and current status
  /// @return - (x, y) coordinate of the selected position
  std::pair<int, int> FindNextPosition(game_logic::board_type &arr) override;

  /// UpdatePosition - Update the position in the game board
  /// @x - X coordinate for updating the position
  /// @y - Y coordinate for updating the position
  void UpdatePosition(int x, int y);

private:
  std::pair<int, int> selected_point_{ -1, -1 };// selected point by the user
  bool stop_game_{ false };// stop the waiting for user input
  std::condition_variable cv_;
  std::mutex mtx_;
};
}// namespace game_logic