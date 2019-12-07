#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

Scene *GameScene::createScene()
{
  auto scene = cocos2d::Scene::create();
  auto layer = GameScene::create();
  scene->addChild(layer);

  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in "
         "front of filenames in GameSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
  //////////////////////////////
  // 1. super init first
  if (!Layer::init())
  {
    return false;
  }

  auto sprite = Sprite::create(GAME_SCENE_BACKGROUND_FILEPATH);
  sprite->setPosition(this->getBoundingBox().getMidX(),
                      this->getBoundingBox().getMidY());

  this->addChild(sprite, 0);
  gridSprite = Sprite::create(GRID_FILEPATH);
  gridSprite->setPosition(
      Vec2(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY()));
  this->addChild(gridSprite);
  InitGridRects();
  InitGridPieces();

  util::FillGameBoard(gameArray, EMPTY_PIECE);

  turn = PLAYER;
  gameState = STATE_PLAYING;

  auto listener = EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);

  listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
  listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
  listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
  listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

  Director::getInstance()
      ->getEventDispatcher()
      ->addEventListenerWithSceneGraphPriority(listener, this);

  return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
  return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
  if (STATE_PLAYING == gameState)
  {
    CheckAndPlacePiece(touch);
  }
}

void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
}

void GameScene::InitGridRects()
{
  auto grid_width = gridSprite->getBoundingBox().size.width / 3.0;
  auto grid_height = gridSprite->getBoundingBox().size.height / 3.0;
  auto min_x = gridSprite->getBoundingBox().getMinX();
  auto min_y = gridSprite->getBoundingBox().getMinY();
  gridSpace[0][0] = Rect(min_x, min_y, grid_width, grid_height);
  gridSpace[1][0] = Rect(min_x + grid_width, min_y, grid_width, grid_height);
  gridSpace[2][0] =
      Rect(min_x + 2 * grid_width, min_y, grid_width, grid_height);

  gridSpace[0][1] = Rect(min_x, min_y + grid_height, grid_width, grid_height);
  gridSpace[1][1] =
      Rect(min_x + grid_width, min_y + grid_height, grid_width, grid_height);
  gridSpace[2][1] = Rect(min_x + 2 * grid_width, min_y + grid_height,
                         grid_width, grid_height);

  gridSpace[0][2] =
      Rect(min_x, min_y + 2 * grid_height, grid_width, grid_height);
  gridSpace[1][2] = Rect(min_x + grid_width, min_y + 2 * grid_height,
                         grid_width, grid_height);
  gridSpace[2][2] = Rect(min_x + 2 * grid_width, min_y + 2 * grid_height,
                         grid_width, grid_height);
}

void GameScene::InitGridPieces()
{
  for (int x = 0; x < 3; ++x)
  {
    for (int y = 0; y < 3; ++y)
    {
      gridPieces[x][y] = Sprite::create(X_PIECE_FILEPATH);
      gridPieces[x][y]->setPosition(
          Vec2(gridSprite->getPositionX() +
                   (gridPieces[x][y]->getContentSize().width * (x - 1)),
               gridSprite->getPositionY() +
                   (gridPieces[x][y]->getContentSize().height * (y - 1))));
      gridPieces[x][y]->setVisible(false);
      gridPieces[x][y]->setOpacity(0);
      this->addChild(gridPieces[x][y]);
    }
  }
}

void GameScene::CheckAndPlacePiece(cocos2d::Touch *touch)
{
  Rect rec1 = gridSprite->getBoundingBox();
  Point touchPoint = touch->getLocation();
  for (int x = 0; x < 3; ++x)
  {
    for (int y = 0; y < 3; ++y)
    {
      if (gridSpace[x][y].containsPoint(touchPoint))
      {
        if (EMPTY_PIECE == gameArray[x][y])
        {
          UpdatePiece(x, y);
        }
      }
    }
  }
}

void GameScene::UpdatePiece(uint8_t x, uint8_t y)
{
  gameState = STATE_PLACING_PIECE;
  gameArray[x][y] = turn;
  if (PLAYER == turn)
  {
    gridPieces[x][y]->setTexture(X_PIECE_FILEPATH);
  }
  else
  {
    gridPieces[x][y]->setTexture(O_PIECE_FILEPATH);
  }
  gridPieces[x][y]->setVisible(true);
  gridPieces[x][y]->runAction(Sequence::create(
      FadeIn::create(PIECE_FADE_IN_TIME),
      CallFunc::create(std::bind(&GameScene::CheckWin, this, x, y)),
      NULL));
}

void GameScene::CheckWin(int x, int y)
{
  Check3PiecesForMatch({{0, 0}, {1, 0}, {2, 0}});
  Check3PiecesForMatch({{0, 1}, {1, 1}, {2, 1}});
  Check3PiecesForMatch({{0, 2}, {1, 2}, {2, 2}});
  Check3PiecesForMatch({{0, 0}, {0, 1}, {0, 2}});
  Check3PiecesForMatch({{1, 0}, {1, 1}, {1, 2}});
  Check3PiecesForMatch({{2, 0}, {2, 1}, {2, 2}});
  Check3PiecesForMatch({{0, 0}, {1, 1}, {2, 2}});
  Check3PiecesForMatch({{0, 2}, {1, 1}, {2, 0}});

  if (PLAYER == turn)
  {
    turn = AI;
  }
  else
  {
    turn = PLAYER;
  }
  if (STATE_PLACING_PIECE == gameState)
  {
    gameState = STATE_PLAYING;
  }

  if (turn == PLAYER)
  {
    return;
  }
  // next ai turn
  auto pos = ai_.FindNextPosition(gameArray);
  if (pos.first != -1 && pos.second != -1 && gameArray[pos.first][pos.second] == EMPTY_PIECE)
  {
    UpdatePiece(pos.first, pos.second);
  }
}

void GameScene::Check3PiecesForMatch(
    std::vector<std::pair<int, int>> threePoints)
{
  auto &p0 = threePoints[0];
  auto &p1 = threePoints[1];
  auto &p2 = threePoints[2];
  if (turn == gameArray[p0.first][p0.second] &&
      turn == gameArray[p1.first][p1.second] &&
      turn == gameArray[p2.first][p2.second])
  {
    std::string winningPieceStr;
    gameState = STATE_WON;
    if (O_PIECE == turn)
    {
      winningPieceStr = O_WINNING_PIECE_FILEPATH;
    }
    else
    {
      winningPieceStr = X_WINNING_PIECE_FILEPATH;
    }

    Sprite *winningPieces[3];
    winningPieces[0] = Sprite::create(winningPieceStr.c_str());
    winningPieces[0]->setPosition(
        gridPieces[p0.first][p0.second]->getPosition());
    winningPieces[0]->setOpacity(0);
    this->addChild(winningPieces[0]);

    winningPieces[1] = Sprite::create(winningPieceStr.c_str());
    winningPieces[1]->setPosition(
        gridPieces[p1.first][p1.second]->getPosition());
    winningPieces[1]->setOpacity(0);
    this->addChild(winningPieces[1]);

    winningPieces[2] = Sprite::create(winningPieceStr.c_str());
    winningPieces[2]->setPosition(
        gridPieces[p2.first][p2.second]->getPosition());
    winningPieces[2]->setOpacity(0);
    this->addChild(winningPieces[2]);

    winningPieces[0]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));
    winningPieces[1]->runAction(
        Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 0.5),
                         FadeIn::create(PIECE_FADE_IN_TIME), NULL));
    winningPieces[2]->runAction(
        Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 0.5),
                         FadeIn::create(PIECE_FADE_IN_TIME), NULL));
  }
}
