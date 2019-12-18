#pragma once

#include "GameUtil.h"
#include "Player.h"
#include <array>
#include <functional>
#include <utility>

namespace game_logic {
class AITicTacToe : public game_logic::IPlayer
{
public:
  /// Constructor
  /// @param ai - ai id
  /// @param player - player id
  /// @param empty - empty id
  AITicTacToe(game_logic::MoveType ai, game_logic::MoveType player, game_logic::MoveType empty)
    : game_logic::IPlayer(ai), ai_(ai), player_(player), empty_(empty) {}

  /// FindNextPosition - find the next move for AI from current game
  /// @param arr - Current game status
  /// @return - pair of (x, y) coordinate for the next move of AI
  ///           returns (-1, -1) if move not possible
  std::pair<int, int> FindNextPosition(game_logic::board_type &arr) override;

private:
  int BuildGameTree(game_logic::board_type &arr, bool maximizing_player, int depth);
  int TraverseBreadth(game_logic::board_type &arr, bool is_maximizing, const std::function<int(int, int)> &func, int depth);

  game_logic::MoveType ai_;// identification for ai player in game array
  game_logic::MoveType player_;// identification for human player
  game_logic::MoveType empty_;// identification for empty position
  static const uint8_t kDefaultValue = 255;
};
}// namespace game_logic
