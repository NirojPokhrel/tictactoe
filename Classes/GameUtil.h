#pragma once

#include <array>
#include <utility>
#include <vector>

namespace util {
enum class MoveType {
  kX,
  kO,
  kEmpty
};
using board_type = std::array<std::array<MoveType, 3>, 3>;
using VectorOfPairs = std::vector<std::pair<int, int>>;
MoveType IsGameOver(const board_type &game_board, MoveType emtpy_id, std::vector<std::pair<int, int>> *winning_position = nullptr);
bool CheckIfFull(const board_type &game_board, MoveType empty_id);
uint8_t MaximumPossiblePath(const board_type &game_board, int x, int y, MoveType empty_id);
void FillGameBoard(util::board_type &brd, MoveType init_item);
}// namespace util
