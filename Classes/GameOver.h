#pragma once

#include "cocos2d.h"

namespace game_scene {
class GameOver
{
public:
  GameOver(cocos2d::Layer* layer);
  void ShowGameOver(cocos2d::Layer* layer);

private:
  void Retry(cocos2d::Ref* pSender);
  void GoToMainMenu(cocos2d::Ref* pSender);
};
}// namespace game_scene