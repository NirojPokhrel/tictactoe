#include "GameOver.h"
#include "Definitions.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include <iostream>

using game_scene::GameOver;
USING_NS_CC;

GameOver::GameOver(cocos2d::Layer* layer) {}

void GameOver::ShowGameOver(cocos2d::Layer* layer) {
  auto size = Director::getInstance()->getVisibleSize();
  auto background = Sprite::create(GAME_OVER_BACKGROUND);
  background->setPosition(Vec2(size.width / 2, size.height / 2));
  background->setOpacity(0);
  layer->addChild(background);
  background->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 2.5),
    FadeIn::create(GAME_OVER_BACKGROUND_FADE_IN_TIME),
    NULL));
  auto* overlayWindowItem = MenuItemImage::create(
    GAME_OVER_WINDOW,
    GAME_OVER_WINDOW,
    GAME_OVER_WINDOW,
    nullptr);
  auto* retryItem = MenuItemSprite::create(
    Sprite::create(RETRY_BUTTON),
    Sprite::create(RETRY_BUTTON),
    Sprite::create(RETRY_BUTTON),
    CC_CALLBACK_1(GameOver::Retry, this));
  retryItem->setPosition(overlayWindowItem->getContentSize().width / 4, retryItem->getPositionY());

  auto* mainMenuItem = MenuItemSprite::create(
    Sprite::create(HOME_BUTTON),
    Sprite::create(HOME_BUTTON),
    Sprite::create(HOME_BUTTON),
    CC_CALLBACK_1(GameOver::GoToMainMenu, this));
  mainMenuItem->setPosition(-overlayWindowItem->getContentSize().width / 4, retryItem->getPositionY());
  auto* menu = Menu::create(retryItem, mainMenuItem, nullptr);
  menu->setPosition(Vec2(size.width / 2, size.height / 2 + size.height));
  layer->addChild(menu);

  auto* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION,
    Vec2(size.width / 2, size.height / 2)));
  auto* menuShowMenu = Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 2.5), menuActionEasing, NULL);
  menu->runAction(menuShowMenu);
}

void GameOver::Retry(cocos2d::Ref* pSender) {
  std::cout << "Retry" << std::endl;
  auto scene = GameScene::createScene();
  auto transitionFade = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
  Director::getInstance()->replaceScene(scene);
}

void GameOver::GoToMainMenu(cocos2d::Ref* pSender) {
  std::cout << "GoToMainMenu" << std::endl;
  auto scene = MainMenuScene::createScene();
  auto transitionFade = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
  Director::getInstance()->replaceScene(scene);
}
