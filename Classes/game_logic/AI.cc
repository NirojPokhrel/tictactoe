#include "AI.h"
#include "GameUtil.h"
#include <algorithm>
#include <functional>
#include <iostream>

using game_logic::AITicTacToe;

std::pair<int, int> AITicTacToe::FindNextPosition(game_logic::board_type &arr) {
  int value = -200;
  uint8_t max_x = kDefaultValue;
  uint8_t max_y = kDefaultValue;
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 3; ++j) {
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
  if (max_x != kDefaultValue && max_y != kDefaultValue) {
    arr[max_x][max_y] = player_;
    is_losing_position = game_logic::IsGameOver(arr, empty_) != game_logic::MoveType::kEmpty;
    arr[max_x][max_y] = empty_;
  }
  if (value <= 0 && !is_losing_position) {
    // no best possible solution
    // find the position with maximum filling capacity
    for (uint8_t i = 0; i < 3; ++i) {
      for (uint8_t j = 0; j < 3; ++j) {
        if (arr[i][j] == empty_) {
          auto current_value = game_logic::MaximumPossiblePath(arr, i, j, empty_);
          if (current_value > value) {
            max_x = i;
            max_y = j;
            value = current_value;
          }
        }
      }
    }
  }
  return { max_x, max_y };
}

int AITicTacToe::BuildGameTree(game_logic::board_type &arr, bool maximizing_player, int depth) {
  // PrintBoard(arr);
  auto game_over = game_logic::IsGameOver(arr, empty_);
  if (game_over != empty_) {
    if (game_over == ai_) {
      return 10 - depth;
    } else {
      return -10 + depth;
    }
  }
  if (game_logic::CheckIfFull(arr, empty_)) {
    return 0;
  }
  if (maximizing_player) {
    return TraverseBreadth(
      arr, maximizing_player, [](int a, int b) { return std::max(a, b); }, depth);
  } else {
    return TraverseBreadth(
      arr, maximizing_player, [](int a, int b) { return std::min(a, b); }, depth);
  }
}

int AITicTacToe::TraverseBreadth(game_logic::board_type &arr, bool is_maximizing, std::function<int(int, int)> func, int depth) {
  int value = is_maximizing ? -100 : 100;
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 3; ++j) {
      if (arr[i][j] == empty_) {
        arr[i][j] = (is_maximizing ? ai_ : player_);
        value = func(value, BuildGameTree(arr, !is_maximizing, depth + 1));
        arr[i][j] = empty_;
      }
    }
  }
  return value;
}
