#include "GameOver.h"
#include "Definitions.h"
#include "GameScene.h"
#include "MainMenuScene.h"

using game_scene::GameOver;
USING_NS_CC;

GameOver::GameOver(cocos2d::Layer* layer, constants::GameState& gameState) {
  this->gameState = &gameState;
  Size screenSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  MenuItemSprite* pauseItem = MenuItemSprite::create(
    Sprite::create(constants::kPauseButton),
    Sprite::create(constants::kPauseButtonPressed),
    Sprite::create(constants::kPauseButton),
    CC_CALLBACK_1(GameOver::PauseGame, this));
  pauseItem->setPosition(Vec2(screenSize.width - (pauseItem->getContentSize().width / 2) + origin.x,
    screenSize.height - (pauseItem->getContentSize().height / 2) + origin.y));

  Menu* menuButtons = Menu::create(pauseItem, NULL);
  menuButtons->setPosition(Vec2::ZERO);
  layer->addChild(menuButtons);

  pauseBackground = Sprite::create(constants::kPauseBackground);
  pauseBackground->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  pauseBackground->setOpacity(0);
  layer->addChild(pauseBackground);

  MenuItemImage* overlayPausedMenuItem = MenuItemImage::create(
    constants::kPauseWindow, constants::kPauseWindow, constants::kPauseWindow, nullptr);

  MenuItemSprite* resumeItem = MenuItemSprite::create(
    Sprite::create(constants::kResumeButton),
    Sprite::create(constants::kResumeButton),
    Sprite::create(constants::kResumeButton),
    CC_CALLBACK_1(GameOver::PauseGame, this));
  resumeItem->setPosition(-overlayPausedMenuItem->getContentSize().width / 4, resumeItem->getPositionY());

  MenuItemSprite* mainMenuItem = MenuItemSprite::create(
    Sprite::create(constants::kHomeButton),
    Sprite::create(constants::kHomeButton),
    Sprite::create(constants::kHomeButton),
    CC_CALLBACK_1(GameOver::GoToMainMenu, this));
  mainMenuItem->setPosition(overlayPausedMenuItem->getContentSize().width / 4, mainMenuItem->getPositionY());

  pauseMenu = Menu::create(overlayPausedMenuItem, resumeItem, mainMenuItem, nullptr);
  overlayPausedMenuItem->setEnabled(false);

  pauseMenu->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + screenSize.height));
  layer->addChild(pauseMenu);
}

void GameOver::ShowGameOver(cocos2d::Layer* layer) {
  auto size = Director::getInstance()->getVisibleSize();
  auto background = Sprite::create(constants::kGameOverBackground);
  background->setPosition(Vec2(size.width / 2, size.height / 2));
  background->setOpacity(0);
  layer->addChild(background);
  background->runAction(Sequence::create(DelayTime::create(constants::kPieceFadeInTime * 2.5),
    FadeIn::create(constants::kGameOverBackgroundFadeInTime),
    NULL));
  auto* overlayWindowItem = MenuItemImage::create(
    constants::kGameOverWindow,
    constants::kGameOverWindow,
    constants::kGameOverWindow,
    nullptr);
  auto* retryItem = MenuItemSprite::create(
    Sprite::create(constants::kRetryButton),
    Sprite::create(constants::kRetryButton),
    Sprite::create(constants::kRetryButton),
    CC_CALLBACK_1(GameOver::Retry, this));
  retryItem->setPosition(overlayWindowItem->getContentSize().width / 4, retryItem->getPositionY());

  auto* mainMenuItem = MenuItemSprite::create(
    Sprite::create(constants::kHomeButton),
    Sprite::create(constants::kHomeButton),
    Sprite::create(constants::kHomeButton),
    CC_CALLBACK_1(GameOver::GoToMainMenu, this));
  mainMenuItem->setPosition(-overlayWindowItem->getContentSize().width / 4, retryItem->getPositionY());
  auto* menu = Menu::create(overlayWindowItem, retryItem, mainMenuItem, nullptr);
  overlayWindowItem->setEnabled(false);
  menu->setPosition(Vec2(size.width / 2, size.height / 2 + size.height));
  layer->addChild(menu);

  auto* menuActionEasing = EaseBounceOut::create(MoveTo::create(constants::kMenuMoveBounceDuration,
    Vec2(size.width / 2, size.height / 2)));
  auto* menuShowMenu = Sequence::create(DelayTime::create(constants::kPieceFadeInTime * 2.5), menuActionEasing, NULL);
  menu->runAction(menuShowMenu);
}

void GameOver::Retry(cocos2d::Ref* pSender) {
  pauseMenu->setEnabled(false);
  auto scene = game_scene::GameScene::createScene();
  auto transitionFade = TransitionFade::create(constants::kSceneTransitionTime, scene);
  Director::getInstance()->replaceScene(transitionFade);
}

void GameOver::GoToMainMenu(cocos2d::Ref* pSender) {
  pauseMenu->setEnabled(false);
  auto scene = game_scene::MainMenuScene::createScene();
  auto transitionFade = TransitionFade::create(constants::kSceneTransitionTime, scene);
  Director::getInstance()->replaceScene(transitionFade);
}

void GameOver::PauseGame(cocos2d::Ref* pSender) {
  Size size = Director::getInstance()->getVisibleSize();
  if (*gameState == constants::GameState::kStatePlaying) {
    *gameState = constants::GameState::kStatePause;
    pauseBackground->runAction(FadeIn::create(constants::kPauseBackgroundFadeInTime));
    auto* menuActionEasing = EaseBounceOut::create(MoveTo::create(constants::kMenuMoveBounceDuration,
      Vec2(size.width / 2, size.height / 2)));
    pauseMenu->runAction(menuActionEasing);
  } else if (*gameState == constants::GameState::kStatePause) {
    *gameState = constants::GameState::kStatePlaying;
    pauseBackground->runAction(FadeOut::create(constants::kPauseBackgroundFadeInTime));
    auto* menuActionEasing = EaseBounceOut::create(MoveTo::create(constants::kMenuMoveBounceDuration,
      Vec2(size.width / 2, size.height / 2 + size.height)));
    pauseMenu->runAction(menuActionEasing);
  }
}
