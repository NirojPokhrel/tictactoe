#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;
using game_scene::MainMenuScene;

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

  auto sprite = Sprite::create(constants::kMainMenuBackgroundFilepath);
  sprite->setPosition(this->getBoundingBox().getMidX(),
    this->getBoundingBox().getMidY());

  this->addChild(sprite, 0);

  auto sprite_title = Sprite::create(constants::kMainMenuTitleFielpath);
  sprite_title->setPosition(Vec2(screenSize.width / 2 + origin.x,
    screenSize.height * 0.75 + origin.y));
  this->addChild(sprite_title);

  auto playButton =
    Button::create(constants::kMainMenuPlayButton, constants::kMainMenuPlayButtonPressed);
  playButton->setPosition(Vec2(
    this->getBoundingBox().getMidX(),
    this->getBoundingBox().getMidY() * 0.60));
  this->addChild(playButton);

  playButton->addTouchEventListener(
    CC_CALLBACK_2(MainMenuScene::touchEvent, this));

  auto playButtonOuter = Sprite::create(constants::kMainMenuPlayButtonOuter);
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
    auto scene = game_scene::GameScene::createScene();
    auto transitionFade = TransitionFade::create(constants::kSceneTransitionTime, scene);
    Director::getInstance()->replaceScene(scene);
    break;
  }
  }
}
