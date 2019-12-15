#pragma once

#include "cocos2d.h"

class SplashScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene *createScene();
  virtual bool init() override;
  // implement the "static create()" method manually
  CREATE_FUNC(SplashScene);

private:
  void SwitchToMainMenu(float dt);
  cocos2d::Sprite *sprite;
};
