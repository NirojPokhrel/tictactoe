#include "GameLogic.h"
#include <vector>

using game::GameLogic;

void GameLogic::InitGame() {
  util::FillGameBoard(game_, util::MoveType::kEmpty);
}

void GameLogic::StartGame() {
  game_started_ = true;
  game_task_ = std::async(std::launch::async, &GameLogic::RunGameLogic, this);
}

void GameLogic::RunGameLogic() {
  game::IPlayer* turn;
  std::vector<game::IPlayer*> players{ p1_, p2_ };
  uint8_t pos = 0;
  turn = players[pos];
  while (game_started_) {
    if (MakeMove(turn)) {
      if (Winner() != util::MoveType::kEmpty) {
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
  if (game_task_.valid()) {
    game_task_.get();
  }
}

bool GameLogic::MakeMove(game::IPlayer* player) {
  auto position = static_cast<std::pair<uint8_t, uint8_t>>(player->FindNextPosition(game_));
  if (position.first == 255 || position.second == 255 || game_[position.first][position.second] != util::MoveType::kEmpty) {
    return false;
  }
  ui_callback_(position.first, position.second, player->GetMoveType());
  game_[position.first][position.second] = player->GetMoveType();
  return true;
}

util::MoveType GameLogic::Winner(util::VectorOfPairs* win_pos) const {
  return util::IsGameOver(game_, util::MoveType::kEmpty, win_pos);
}

bool GameLogic::IsGameDraw() const {
  return util::IsGameOver(game_, util::MoveType::kEmpty) == util::MoveType::kEmpty
         && util::CheckIfFull(game_, util::MoveType::kEmpty);
}
