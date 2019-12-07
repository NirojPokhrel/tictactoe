#include <gmock/gmock.h>
#include "GameLogic.h"
#include "GameUtil.h"
#include "Player.h"

class MockPlayer : public game::IPlayer {
public:
  MockPlayer(util::MoveType type) : game::IPlayer (type) {}
  MOCK_METHOD((std::pair<int, int>), FindNextPosition, (util::board_type &arr), (override));
};

TEST(GameLogic, TestGame) {

}