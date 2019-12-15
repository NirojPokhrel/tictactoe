#include "SplashScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene *SplashScene::createScene() {
  auto scene = cocos2d::Scene::create();
  auto layer = SplashScene::create();
  scene->addChild(layer);

  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
  printf("Error while loading: %s\n", filename);
  printf(
    "Depending on how you compiled you might have to add 'Resources/' in "
    "front of filenames in SplashSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScene::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }

  auto sprite = Sprite::create(SPLASH_SCENE_BACKGROUND_FILEPATH);
  sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());

  this->addChild(sprite, 0);

  scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::SwitchToMainMenu), SPLASH_SCENE_SHOW_TIME);

  return true;
}

void SplashScene::SwitchToMainMenu(float dt) {
  Scene *scene = MainMenuScene::createScene();
  TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
  Director::getInstance()->replaceScene(transition);
}
