#pragma once

#include "GameUtil.h"
#include "Player.h"
#include <array>
#include <functional>
#include <utility>

namespace ai {
class AITicTacToe : public game::IPlayer
{
public:
  /// Constructor
  /// @param ai - ai id
  /// @param player - player id
  /// @param empty - empty id
  AITicTacToe(util::MoveType ai, util::MoveType player, util::MoveType empty)
    : ai_(ai), player_(player), empty_(empty), game::IPlayer(ai) {}

  /// FindNextPosition - find the next move for AI from current game
  /// @param arr - Current game status
  /// @return - pair of (x, y) coordinate for the next move of AI
  ///           returns (-1, -1) if move not possible
  std::pair<int, int> FindNextPosition(util::board_type &arr) override;

private:
  int BuildGameTree(util::board_type &arr, bool maximizing_player, int depth);
  int TraverseBreadth(util::board_type &arr, bool is_maximizing, std::function<int(int, int)> func, int depth);

  util::MoveType ai_;// identification for ai player in game array
  util::MoveType player_;// identification for human player
  util::MoveType empty_;// identification for empty position
};
}// namespace ai
