#pragma once

#include "GameUtil.h"
#include "Player.h"

#include <condition_variable>
#include <mutex>
#include <utility>

namespace game {
class HumanPlayer : public game::IPlayer
{
public:
  HumanPlayer(util::MoveType move) : game::IPlayer(move) {}
  std::pair<int, int> FindNextPosition(util::board_type &arr) override;
  void UpdatePosition(int x, int y);

private:
  std::pair<int, int> selected_point_{ -1, -1 };
  std::condition_variable cv_;
  std::mutex mtx_;
};
}// namespace game