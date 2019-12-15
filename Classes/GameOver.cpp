#include "GameOver.h"
#include "Definitions.h"
#include "GameScene.h"
#include "MainMenuScene.h"

using game_scene::GameOver;
USING_NS_CC;

GameOver::GameOver(cocos2d::Layer* layer, int& gameState) {
  this->gameState = &gameState;
  Size screenSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  MenuItemSprite* pauseItem = MenuItemSprite::create(
    Sprite::create(PAUSE_BUTTON),
    Sprite::create(PAUSE_BUTTON_PRESSED),
    Sprite::create(PAUSE_BUTTON),
    CC_CALLBACK_1(GameOver::PauseGame, this));
  pauseItem->setPosition(Vec2(screenSize.width - (pauseItem->getContentSize().width / 2) + origin.x,
    screenSize.height - (pauseItem->getContentSize().height / 2) + origin.y));

  Menu* menuButtons = Menu::create(pauseItem, NULL);
  menuButtons->setPosition(Vec2::ZERO);
  layer->addChild(menuButtons);

  pauseBackground = Sprite::create(PAUSE_BACKGROUND);
  pauseBackground->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  pauseBackground->setOpacity(0);
  layer->addChild(pauseBackground);

  MenuItemImage* overlayPausedMenuItem = MenuItemImage::create(
    PAUSE_WINDOW, PAUSE_WINDOW, PAUSE_WINDOW, nullptr);

  MenuItemSprite* resumeItem = MenuItemSprite::create(
    Sprite::create(RESUME_BUTTON),
    Sprite::create(RESUME_BUTTON),
    Sprite::create(RESUME_BUTTON),
    CC_CALLBACK_1(GameOver::PauseGame, this));
  resumeItem->setPosition(-overlayPausedMenuItem->getContentSize().width / 4, resumeItem->getPositionY());

  MenuItemSprite* mainMenuItem = MenuItemSprite::create(
    Sprite::create(HOME_BUTTON),
    Sprite::create(HOME_BUTTON),
    Sprite::create(HOME_BUTTON),
    CC_CALLBACK_1(GameOver::GoToMainMenu, this));
  mainMenuItem->setPosition(overlayPausedMenuItem->getContentSize().width / 4, mainMenuItem->getPositionY());

  pauseMenu = Menu::create(overlayPausedMenuItem, resumeItem, mainMenuItem, nullptr);
  overlayPausedMenuItem->setEnabled(false);

  pauseMenu->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + screenSize.height));
  layer->addChild(pauseMenu);
}

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
  auto* menu = Menu::create(overlayWindowItem, retryItem, mainMenuItem, nullptr);
  overlayWindowItem->setEnabled(false);
  menu->setPosition(Vec2(size.width / 2, size.height / 2 + size.height));
  layer->addChild(menu);

  auto* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION,
    Vec2(size.width / 2, size.height / 2)));
  auto* menuShowMenu = Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 2.5), menuActionEasing, NULL);
  menu->runAction(menuShowMenu);
}

void GameOver::Retry(cocos2d::Ref* pSender) {
  pauseMenu->setEnabled(false);
  auto scene = GameScene::createScene();
  auto transitionFade = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
  Director::getInstance()->replaceScene(transitionFade);
}

void GameOver::GoToMainMenu(cocos2d::Ref* pSender) {
  pauseMenu->setEnabled(false);
  auto scene = MainMenuScene::createScene();
  auto transitionFade = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
  Director::getInstance()->replaceScene(transitionFade);
}

void GameOver::PauseGame(cocos2d::Ref* pSender) {
  Size size = Director::getInstance()->getVisibleSize();
  if (*gameState == STATE_PLAYING) {
    *gameState = STATE_PAUSE;
    pauseBackground->runAction(FadeIn::create(PAUSE_BACKGROUND_FADE_IN_TIME));
    auto* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION,
      Vec2(size.width / 2, size.height / 2)));
    pauseMenu->runAction(menuActionEasing);
  } else if (*gameState == STATE_PAUSE) {
    *gameState = STATE_PLAYING;
    pauseBackground->runAction(FadeOut::create(PAUSE_BACKGROUND_FADE_IN_TIME));
    auto* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION,
      Vec2(size.width / 2, size.height / 2 + size.height)));
    pauseMenu->runAction(menuActionEasing);
  }
}
