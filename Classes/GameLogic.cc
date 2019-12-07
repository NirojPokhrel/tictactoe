#include "GameLogic.h"

using game::GameLogic;

void GameLogic::InitGame() {
  util::FillGameBoard(game_, util::MoveType::kEmpty);
}

void GameLogic::StartGame() {
  game_started_ = true;
  game_task_ = std::async(std::launch::async, &GameLogic::RunGameLogic, this);
}

void GameLogic::RunGameLogic() {
  while (game_started_) {
    // player 1 turn
    if (!MakeMove(p1_)) {
      break;
    }
    // player 2 turn
    if (!MakeMove(p2_)) {
      break;
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
  auto position = player->FindNextPosition(game_);
  if (position.first == -1 || position.second == -1 ||
      game_[position.first][position.second] != util::MoveType::kEmpty) {
    return false;
  }
  ui_callback_(position.first, position.second, p1_->GetMoveType());
  game_[position.first][position.second] = player->GetMoveType();
  return true;
}

util::MoveType GameLogic::Winner() const {
  return util::IsGameOver(game_, util::MoveType::kEmpty);
}

bool GameLogic::IsGameDraw() const {
  return util::IsGameOver(game_, util::MoveType::kEmpty) == util::MoveType::kEmpty
          && util::CheckIfFull(game_, util::MoveType::kEmpty);
}