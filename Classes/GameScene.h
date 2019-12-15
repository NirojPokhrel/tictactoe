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

#include "AI.h"
#include "Definitions.h"
#include "GameLogic.h"
#include "GameOver.h"
#include "GameUtil.h"
#include "HumanPlayer.h"
#include "cocos2d.h"
#include <string>
#include <utility>
#include <vector>

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
  void UpdateUI(int x, int y, util::MoveType move);

private:
  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

  void InitGridRects();
  void InitGridPieces();

  void CheckAndPlacePiece(cocos2d::Touch *touch);
  void CheckWin(util::MoveType move);
  void UpdateWinUI(const util::VectorOfPairs &threePoints, util::MoveType move);
  void UpdateSprite(int x, int y, util::MoveType move);

  cocos2d::Sprite *gridSprite;
  cocos2d::Rect gridSpace[3][3];
  cocos2d::Sprite *gridPieces[3][3];

  util::board_type gameArray;
  ai::AITicTacToe ai_{ util::MoveType::kO, util::MoveType::kX, util::MoveType::kEmpty };
  game::HumanPlayer human_{ util::MoveType::kX };
  game::GameLogic game_logic_;
  game_scene::GameOver *game_over_;
  util::MoveType turn;

  int gameState;
};
