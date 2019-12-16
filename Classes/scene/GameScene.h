/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#pragma once

#include "Definitions.h"
#include "GameOver.h"
#include "cocos2d.h"
#include "game_logic/AI.h"
#include "game_logic/GameLogic.h"
#include "game_logic/GameUtil.h"
#include "game_logic/HumanPlayer.h"
#include <string>
#include <utility>
#include <vector>

namespace game_scene {
class GameScene : public cocos2d::Layer
{
public:
  GameScene()
    : game_logic_(&human_, &ai_, std::bind(&GameScene::UpdateUI, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)) {
  }
  ~GameScene() {
    game_logic_.StopGame();
    human_.InterruptGame();
  }
  static cocos2d::Scene *createScene();
  virtual bool init() override;
  // implement the "static create()" method manually
  CREATE_FUNC(GameScene);
  void UpdateUI(int x, int y, game_logic::MoveType move);

private:
  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

  void InitGridRects();
  void InitGridPieces();

  void CheckAndPlacePiece(cocos2d::Touch *touch);
  void CheckWin(game_logic::MoveType move);
  void UpdateWinUI(const game_logic::VectorOfPairs &threePoints, game_logic::MoveType move);
  void UpdateSprite(int x, int y, game_logic::MoveType move);

  cocos2d::Sprite *gridSprite;
  cocos2d::Rect gridSpace[3][3];
  cocos2d::Sprite *gridPieces[3][3];

  game_logic::board_type gameArray;
  game_logic::AITicTacToe ai_{ game_logic::MoveType::kO, game_logic::MoveType::kX, game_logic::MoveType::kEmpty };
  game_logic::HumanPlayer human_{ game_logic::MoveType::kX };
  game_logic::GameLogic game_logic_;
  game_scene::GameOver *game_over_;
  game_logic::MoveType turn;

  constants::GameState gameState;
};
}// namespace game_scene
