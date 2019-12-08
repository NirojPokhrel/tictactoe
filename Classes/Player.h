#pragma once

#include <utility>
#include "GameUtil.h"

namespace game {
class IPlayer
{
public:
  explicit IPlayer(util::MoveType move_type) : move_type_(move_type) {}
  virtual ~IPlayer() = default;
  virtual std::pair<int, int> FindNextPosition(util::board_type &arr) = 0;

  util::MoveType GetMoveType() const {
    return move_type_;
  }

protected:
  const util::MoveType move_type_;
};
}// namespace game
