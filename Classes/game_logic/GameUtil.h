#pragma once

#include <array>
#include <utility>
#include <vector>

namespace game_logic {
enum class MoveType {
  kX,
  kO,
  kEmpty
};
using board_type = std::array<std::array<MoveType, 3>, 3>;
using VectorOfPairs = std::vector<std::pair<int, int>>;
MoveType IsGameOver(const board_type &game_board, MoveType empty_type, std::vector<std::pair<int, int>> *win_pos = nullptr);
bool CheckIfFull(const board_type &game_board, MoveType empty_id);
uint8_t MaximumPossiblePath(const board_type &game_board, int x, int y, MoveType empty_id);
void FillGameBoard(game_logic::board_type &brd, MoveType init_item);
}// namespace game_logic
