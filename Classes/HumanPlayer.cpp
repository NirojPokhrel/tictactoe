#include "HumanPlayer.h"

using game::HumanPlayer;

std::pair<int, int> HumanPlayer::FindNextPosition(util::board_type &arr) {
  std::unique_lock<std::mutex> ulk(mtx_);
  cv_.wait(ulk, [this]() { return selected_point_.first != -1; });
  auto res = selected_point_;
  selected_point_.first = -1;
  selected_point_.second = -1;
  return res;
}

void HumanPlayer::UpdatePosition(int x, int y) {
  {
    std::lock_guard<std::mutex> _(mtx_);
    selected_point_.first = x;
    selected_point_.second = y;
  }
  cv_.notify_one();
}