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

#include "cocos2d.h"
#include "GameUtil.h"
#include "AI.h"
#include "Definitions.h"
#include <string>
#include <utility>
#include <vector>

class GameScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene *createScene();
  virtual bool init() override;
  // implement the "static create()" method manually
  CREATE_FUNC(GameScene);

private:
  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
  void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

  void InitGridRects();
  void InitGridPieces();

  void CheckAndPlacePiece(cocos2d::Touch *touch);
  void CheckWin(int x, int y);
  void Check3PiecesForMatch(std::vector<std::pair<int, int>> threePoints);
  void UpdatePiece(uint8_t x, uint8_t y);

  cocos2d::Sprite *gridSprite;
  cocos2d::Rect gridSpace[3][3];
  cocos2d::Sprite *gridPieces[3][3];

  util::board_type gameArray;
  ai::AITicTacToe ai_{ util::MoveType::kO, util::MoveType::kX, util::MoveType::kEmpty };

  util::MoveType turn;

  int gameState;
};
