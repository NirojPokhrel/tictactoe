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

#include "Definitions.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene *MainMenuScene::createScene() {
  auto scene = cocos2d::Scene::create();
  auto layer = MainMenuScene::create();
  scene->addChild(layer);

  return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }
  Size screenSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  auto sprite = Sprite::create(MAIN_MENU_BACKGROUND_FILEPATH);
  sprite->setPosition(this->getBoundingBox().getMidX(),
                      this->getBoundingBox().getMidY());

  this->addChild(sprite, 0);

  auto sprite_title = Sprite::create(MAIN_MENU_TITLE_FILEPATH);
  sprite_title->setPosition(Vec2(screenSize.width / 2 + origin.x,
                                 screenSize.height * 0.75 + origin.y));
  this->addChild(sprite_title);

  auto playButton =
      Button::create(MAIN_MENU_PLAY_BUTTON, MAIN_MENU_PLAY_BUTTON_PRESSED);
  playButton->setPosition(Vec2(this->getBoundingBox().getMidX(),
                               this->getBoundingBox().getMidY() * 0.60));
  this->addChild(playButton);

  playButton->addTouchEventListener(
      CC_CALLBACK_2(MainMenuScene::touchEvent, this));
  playButton->setTag(TAG_MAIN_MENU_PLAY_BUTTON);

  auto playButtonOuter = Sprite::create(MAIN_MENU_PLAY_BUTTON_OUTER);
  playButtonOuter->setPosition(Vec2(this->getBoundingBox().getMidX(),
                                    this->getBoundingBox().getMidY() * 0.60));
  this->addChild(playButtonOuter);

  return true;
}

void MainMenuScene::touchEvent(Ref *sender, Widget::TouchEventType type) {
  switch (type) {
  case Widget::TouchEventType::BEGAN: {
    break;
  }
  case Widget::TouchEventType::MOVED: {
    break;
  }
  case Widget::TouchEventType::CANCELED: {
    break;
  }
  case Widget::TouchEventType::ENDED: {
    auto scene = GameScene::createScene();
    auto transitionFade = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(scene);
    break;
  }
  }
}