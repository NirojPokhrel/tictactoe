#include "GameLogic.h"
#include <vector>

using game_logic::GameLogic;

void GameLogic::InitGame() {
  game_logic::FillGameBoard(game_, game_logic::MoveType::kEmpty);
}

void GameLogic::StartGame() {
  game_started_ = true;
  game_task_ = std::async(std::launch::async, &GameLogic::RunGameLogic, this);
}

void GameLogic::RunGameLogic() {
  game_logic::IPlayer* turn;
  std::vector<game_logic::IPlayer*> players{ p1_, p2_ };
  uint8_t pos = 0;
  turn = players[pos];
  while (game_started_) {
    if (MakeMove(turn)) {
      if (Winner() != game_logic::MoveType::kEmpty || IsGameDraw()) {
        game_over_ = true;
        break;
      }
      pos = static_cast<uint8_t>((pos + 1) % 2);
      turn = players[pos];
    }
  }
}

void GameLogic::StopGame() {
  game_started_ = false;
}

bool GameLogic::MakeMove(game_logic::IPlayer* player) {
  auto position = static_cast<std::pair<uint8_t, uint8_t>>(player->FindNextPosition(game_));
  if (position.first == 255 || position.second == 255 || game_[position.first][position.second] != game_logic::MoveType::kEmpty) {
    return false;
  }
  ui_callback_(position.first, position.second, player->GetMoveType());
  game_[position.first][position.second] = player->GetMoveType();
  return true;
}

game_logic::MoveType GameLogic::Winner(game_logic::VectorOfPairs* win_pos) const {
  return game_logic::IsGameOver(game_, game_logic::MoveType::kEmpty, win_pos);
}

bool GameLogic::IsGameDraw() const {
  return game_logic::IsGameOver(game_, game_logic::MoveType::kEmpty) == game_logic::MoveType::kEmpty
         && game_logic::CheckIfFull(game_, game_logic::MoveType::kEmpty);
}

bool GameLogic::IsPositionEmpty(int x, int y) const {
  return game_[static_cast<uint8_t>(x)][static_cast<uint8_t>(y)] == game_logic::MoveType::kEmpty;
}
