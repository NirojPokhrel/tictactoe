#include "GameScene.h"
#include "Definitions.h"

using game_scene::GameScene;
USING_NS_CC;

Scene *GameScene::createScene() {
  auto scene = cocos2d::Scene::create();
  auto layer = GameScene::create();
  scene->addChild(layer);

  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
  printf("Error while loading: %s\n", filename);
  printf(
    "Depending on how you compiled you might have to add 'Resources/' in "
    "front of filenames in GameSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }

  auto sprite = Sprite::create(constants::kGameSceneBackgroundFilepath);
  sprite->setPosition(this->getBoundingBox().getMidX(),
    this->getBoundingBox().getMidY());

  this->addChild(sprite, 0);
  gridSprite = Sprite::create(constants::kGridFilepath);
  gridSprite->setPosition(
    Vec2(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY()));
  this->addChild(gridSprite);
  InitGridRects();
  InitGridPieces();


  auto listener = EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);

  listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
  listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
  listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
  listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

  Director::getInstance()
    ->getEventDispatcher()
    ->addEventListenerWithSceneGraphPriority(listener, this);
  gameState = constants::GameState::kStatePlaying;
  game_over_ = new game_scene::GameOver(this, gameState);
  game_logic_.InitGame();
  game_logic_.StartGame();
  return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
  return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
  if (constants::GameState::kStatePlaying == gameState) {
    CheckAndPlacePiece(touch);
  }
}

void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) {
}

void GameScene::InitGridRects() {
  auto grid_width = gridSprite->getBoundingBox().size.width / 3.0;
  auto grid_height = gridSprite->getBoundingBox().size.height / 3.0;
  auto min_x = gridSprite->getBoundingBox().getMinX();
  auto min_y = gridSprite->getBoundingBox().getMinY();
  for (auto i = 0; i < 3; ++i) {
    for (auto j = 0; j < 3; ++j) {
      gridSpace[i][j] = Rect(min_x + i * grid_width, min_y + j * grid_height, grid_width, grid_height);
    }
  }
}

void GameScene::InitGridPieces() {
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      gridPieces[x][y] = Sprite::create(constants::kXPieceFilepath);
      gridPieces[x][y]->setPosition(
        Vec2(gridSprite->getPositionX() + (gridPieces[x][y]->getContentSize().width * (x - 1)),
          gridSprite->getPositionY() + (gridPieces[x][y]->getContentSize().height * (y - 1))));
      gridPieces[x][y]->setVisible(false);
      gridPieces[x][y]->setOpacity(0);
      this->addChild(gridPieces[x][y]);
    }
  }
}

void GameScene::CheckAndPlacePiece(cocos2d::Touch *touch) {
  Rect rec1 = gridSprite->getBoundingBox();
  Point touchPoint = touch->getLocation();
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      if (gridSpace[x][y].containsPoint(touchPoint) && game_logic_.IsPositionEmpty(x, y)) {
        human_.UpdatePosition(x, y);
      }
    }
  }
}

void GameScene::UpdateUI(int x, int y, game_logic::MoveType move) {
  Director *dir = Director::getInstance();
  Scheduler *sched = dir->getScheduler();
  sched->performFunctionInCocosThread(std::bind(&GameScene::UpdateSprite, this, x, y, move));
}

void GameScene::UpdateSprite(int x, int y, game_logic::MoveType move) {
  gameState = constants::GameState::kStatePlacingPiece;
  if (game_logic::MoveType::kX == move) {
    gridPieces[x][y]->setTexture(constants::kXPieceFilepath);
  } else {
    gridPieces[x][y]->setTexture(constants::kOPieceFilepath);
  }
  gridPieces[x][y]->setVisible(true);
  gridPieces[x][y]->runAction(Sequence::create(
    FadeIn::create(constants::kPieceFadeInTime),
    CallFunc::create(std::bind(&GameScene::CheckWin, this, move)),
    NULL));
}

void GameScene::CheckWin(game_logic::MoveType move) {
  game_logic::VectorOfPairs win_pos;
  const auto winner = game_logic_.Winner(&win_pos);
  if (winner != game_logic::MoveType::kEmpty) {
    UpdateWinUI(win_pos, move);
  } else if (game_logic_.IsGameDraw()) {
    gameState = constants::GameState::kStateDraw;
  } else {
    gameState = constants::GameState::kStatePlaying;
  }
  if (gameState != constants::GameState::kStatePlaying) {
    game_over_->ShowGameOver(this);
  }
}

void GameScene::UpdateWinUI(const game_logic::VectorOfPairs &threePoints, game_logic::MoveType move) {
  std::string winningPieceStr;
  gameState = constants::GameState::kStateWon;
  if (game_logic::MoveType::kO == move) {
    winningPieceStr = constants::kOWinningPieceFilepath;
  } else {
    winningPieceStr = constants::kXWinningPieceFilepath;
  }

  Sprite *winningPieces[3];
  for (auto i = 0; i < 3; ++i) {
    winningPieces[i] = Sprite::create(winningPieceStr.c_str());
    winningPieces[i]->setPosition(
      gridPieces[threePoints[i].first][threePoints[i].second]->getPosition());
    winningPieces[i]->setOpacity(0);
    this->addChild(winningPieces[i]);
  }

  winningPieces[0]->runAction(FadeIn::create(constants::kPieceFadeInTime));
  winningPieces[1]->runAction(
    Sequence::create(DelayTime::create(constants::kPieceFadeInTime * 0.5),
      FadeIn::create(constants::kPieceFadeInTime),
      NULL));
  winningPieces[2]->runAction(
    Sequence::create(DelayTime::create(constants::kPieceFadeInTime * 0.5),
      FadeIn::create(constants::kPieceFadeInTime),
      NULL));
}
