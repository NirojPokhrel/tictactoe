#include "GameUtil.h"


namespace util {

void FillGameBoard(util::board_type &brd, MoveType init_item) {
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 3; ++j) {
      brd[i][j] = init_item;
    }
  }
}

inline bool CheckForEquality(MoveType val1, MoveType val2, MoveType val3, MoveType empty_type) {
  if (empty_type != val1 && val1 == val2 && val1 == val3) {
    return true;
  }
  return false;
}

inline void SetWinningPosition(std::pair<int, int> &&p0, std::pair<int, int> &&p1, std::pair<int, int> &&p2, VectorOfPairs *win_pos) {
  if (win_pos != nullptr) {
    win_pos->push_back(p0);
    win_pos->push_back(p1);
    win_pos->push_back(p2);
  }
}


MoveType IsGameOver(const util::board_type &game_board,
  MoveType empty_type,
  VectorOfPairs *win_pos) {
  auto winner = empty_type;
  if (CheckForEquality(game_board[0][0], game_board[0][1], game_board[0][2], empty_type)) {
    winner = game_board[0][0];
    SetWinningPosition({ 0, 0 }, { 0, 1 }, { 0, 2 }, win_pos);
  }
  if (CheckForEquality(game_board[1][0], game_board[1][1], game_board[1][2], empty_type)) {
    winner = game_board[1][0];
    SetWinningPosition({ 1, 0 }, { 1, 1 }, { 1, 2 }, win_pos);
  }
  if (CheckForEquality(game_board[2][0], game_board[2][1], game_board[2][2], empty_type)) {
    winner = game_board[2][0];
    SetWinningPosition({ 2, 0 }, { 2, 1 }, { 2, 2 }, win_pos);
  }
  if (CheckForEquality(game_board[0][0], game_board[1][0], game_board[2][0], empty_type)) {
    winner = game_board[0][0];
    SetWinningPosition({ 0, 0 }, { 1, 0 }, { 2, 0 }, win_pos);
  }
  if (CheckForEquality(game_board[0][1], game_board[1][1], game_board[2][1], empty_type)) {
    winner = game_board[0][1];
    SetWinningPosition({ 0, 1 }, { 1, 1 }, { 2, 1 }, win_pos);
  }
  if (CheckForEquality(game_board[0][2], game_board[1][2], game_board[2][2], empty_type)) {
    winner = game_board[0][2];
    SetWinningPosition({ 0, 2 }, { 1, 2 }, { 2, 2 }, win_pos);
  }
  if (CheckForEquality(game_board[0][0], game_board[1][1], game_board[2][2], empty_type)) {
    winner = game_board[0][0];
    SetWinningPosition({ 0, 0 }, { 1, 1 }, { 2, 2 }, win_pos);
  }
  if (CheckForEquality(game_board[0][2], game_board[1][1], game_board[2][0], empty_type)) {
    winner = game_board[0][2];
    SetWinningPosition({ 0, 2 }, { 1, 1 }, { 2, 0 }, win_pos);
  }
  return winner;
}

bool CheckIfFull(const board_type &game_board, MoveType empty_id) {
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 3; ++j) {
      if (game_board[i][j] == empty_id) {
        return false;
      }
    }
  }
  return true;
}

inline int CheckHorizontal(const board_type &game_board, int x, int y, MoveType empty_id) {
  int empty_cell = 0;
  for (int i = -2; i <= 2; ++i) {
    if ((x + i) >= 0 && (x + i) <= 2
        && game_board[static_cast<unsigned long>(x + i)][static_cast<unsigned long>(y)] == empty_id) {
      empty_cell++;
    }
  }
  return empty_cell;
}

inline int CheckVeritcal(const board_type &game_board, int x, int y, MoveType empty_id) {
  int empty_cell = 0;
  for (int i = -2; i <= 2; ++i) {
    if ((y + i) >= 0 && (y + i) <= 2
        && game_board[static_cast<unsigned long>(x)][static_cast<unsigned long>(y + i)] == empty_id) {
      empty_cell++;
    }
  }
  return empty_cell;
}

inline int CheckDiagnoal(const board_type &game_board, int x, int y, MoveType empty_id) {
  int empty_cell = 0;
  for (int i = -2; i <= 2; ++i) {
    if ((x + i) >= 0 && (x + i) <= 2 && (y + i) >= 0 && (y + i) <= 2
        && game_board[static_cast<unsigned int>(x + i)][static_cast<unsigned int>(y + i)] == empty_id) {
      empty_cell++;
    }
  }
  return empty_cell;
}

inline int CheckRevDiagnoal(const board_type &game_board, int x, int y, MoveType empty_id) {
  int empty_cell = 0;
  for (int i = 0; i <= 5; ++i) {
    if ((x + i - 2) >= 0 && (x + i - 2) <= 2 && (y - i + 2) >= 0 && (y - i + 2) <= 2
        && game_board[static_cast<unsigned int>(x + i - 2)][static_cast<unsigned int>(y - i + 2)] == empty_id) {
      empty_cell++;
    }
  }
  return empty_cell;
}

uint8_t MaximumPossiblePath(const board_type &game_board, int x, int y, MoveType empty_id) {
  uint8_t count = 0;
  // check horizontal
  if (CheckHorizontal(game_board, x, y, empty_id) == 3) {
    count++;
  }
  // check vertical
  if (CheckVeritcal(game_board, x, y, empty_id) == 3) {
    count++;
  }
  // check diagnoal
  if (CheckDiagnoal(game_board, x, y, empty_id) == 3) {
    count++;
  }
  // check reverse diagonal
  if (CheckRevDiagnoal(game_board, x, y, empty_id) == 3) {
    count++;
  }
  return count;
}
}// namespace util