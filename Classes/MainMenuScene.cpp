#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"

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
  playButton->setPosition(Vec2(
    this->getBoundingBox().getMidX(),
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
