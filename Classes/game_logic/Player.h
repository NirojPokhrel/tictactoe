#pragma once

#include "GameUtil.h"
#include <utility>

namespace game_logic {
class IPlayer
{
public:
  explicit IPlayer(game_logic::MoveType move_type) : move_type_(move_type) {}
  virtual ~IPlayer() = default;
  virtual std::pair<int, int> FindNextPosition(game_logic::board_type &arr) = 0;

  game_logic::MoveType GetMoveType() const {
    return move_type_;
  }

protected:
  const game_logic::MoveType move_type_;
};
}// namespace game_logic
