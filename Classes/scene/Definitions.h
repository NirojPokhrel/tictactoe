#pragma once
#include <cstddef>
#include <string>

namespace constants {
const std::string kSplashSceneBackgroundFilepath = "res/Splash Background.png";
const std::string kMainMenuBackgroundFilepath = "res/Main Menu Background.png";
const std::string kGameSceneBackgroundFilepath = "res/Main Menu Background.png";
const double kSplashSceneShowTime = 2.0;
const double kSceneTransitionTime = 1.0;

const std::string kMainMenuTitleFielpath = "res/Game Title.png";

const std::string kMainMenuPlayButton = "res/Play Button.png";
const std::string kMainMenuPlayButtonPressed = "res/Play Button.png";
const std::string kRetryButton = "res/Retry Button.png";
const std::string kHomeButton = "res/Home Button.png";
const std::string kPauseButton = "res/Pause Button.png";
const std::string kPauseButtonPressed = "res/Pause Button.png";
const std::string kResumeButton = "res/Resume Button.png";

const std::string kMainMenuPlayButtonOuter = "res/Play Button Outer.png";
const std::string kGameOverBackground = "res/Pause Background.png";
const std::string kGameOverWindow = "res/Pause Window.png";
const std::string kPauseBackground = "res/Pause Background.png";
const std::string kPauseWindow = "res/Pause Window.png";

const std::string kGridFilepath = "res/Grid.png";
const std::string kXPieceFilepath = "res/X.png";
const std::string kOPieceFilepath = "res/O.png";
const std::string kXWinningPieceFilepath = "res/X Win.png";
const std::string kOWinningPieceFilepath = "res/O Win.png";

const int kXId = 2;
const int kOId = 1;
const int kEmptyId = 0;

const int kStatePlaying = 98;
const int kStatePause = 97;
const int kStateWon = 96;
const int kStatePlacingPiece = 94;
const int kStateDraw = 92;

enum class GameState {
  kStatePlaying = 98,
  kStatePause = 97,
  kStateWon = 96,
  kStatePlacingPiece = 94,
  kStateDraw = 92
};

const double kPieceFadeInTime = 0.5;
const double kGameOverBackgroundFadeInTime = 0.5;
const double kPauseBackgroundFadeInTime = 0.5;
const double kMenuMoveBounceDuration = 1.5;
}// namespace constants
