#include "AI.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include "GameUtil.h"

using ai::AITicTacToe;

std::pair<int, int> AITicTacToe::FindNextPosition(util::board_type &arr) {
  int value = -200;
  int max_x = -1;
  int max_y = -1;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (arr[i][j] == empty_) {
        arr[i][j] = ai_;
        int current_value = BuildGameTree(arr, false, 0);
        if (current_value > value) {
          max_x = i;
          max_y = j;
          value = current_value;
        }
        arr[i][j] = empty_;
      }
    }
  }
  bool is_losing_position = false;
  if (max_x != -1 && max_y != -1) {
    arr[max_x][max_y] = player_;
    is_losing_position = util::IsGameOver(arr, empty_) != util::MoveType::kEmpty;
    arr[max_x][max_y] = empty_;
  }
  if (value <= 0 && !is_losing_position) {
    // no best possible solution
    // find the position with maximum filling capacity
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (arr[i][j] == empty_) {
          auto current_value = util::MaximumPossiblePath(arr, i, j, empty_);
          if (current_value > value) {
            max_x = i;
            max_y = j;
            value = current_value;
          }
        }
      }
    }
  }
  return {max_x, max_y};
}

int AITicTacToe::BuildGameTree(util::board_type &arr, bool maximizing_player,
                               int depth) {
  // PrintBoard(arr);
  auto game_over = util::IsGameOver(arr, empty_);
  if (game_over != empty_) {
    if (game_over == ai_) {
      return 10 - depth;
    } else {
      return -10 + depth;
    }
  }
  if (util::CheckIfFull(arr, empty_)) {
    return 0;
  }
  if (maximizing_player) {
    return TraverseBreadth(
        arr, maximizing_player, [](int a, int b) { return std::max(a, b); },
        depth);
  } else {
    return TraverseBreadth(
        arr, maximizing_player, [](int a, int b) { return std::min(a, b); },
        depth);
  }
}

int AITicTacToe::TraverseBreadth(util::board_type &arr, bool is_maximizing,
                                 std::function<int(int, int)> func, int depth) {
  int value = is_maximizing ? -100 : 100;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (arr[i][j] == empty_) {
        arr[i][j] = (is_maximizing ? ai_ : player_);
        value = func(value, BuildGameTree(arr, !is_maximizing, depth + 1));
        arr[i][j] = empty_;
      }
    }
  }
  return value;
}
