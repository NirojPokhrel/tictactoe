# Tic Tac Toe Game 
Tic-tac-toe with cocos2d may be the Hello World program in game development, but I have take this moment to appreciate a quality C++ by integrating several quality code required for this project.

## Targeted system
This program has been developed and tested in Ubuntu-18.04.

## Requirements 
- Cocos2d build environment
- Clang Format setup
- Clang Tidy setup (Static Analysis)
- Sanitizer (Dynamic Analysis)
- Setting up bitbucket pipelines for CI pipelines
- Git LFS
- UI properties from sonargames

### Cocos2d build environment
Install the dependencies from [this link](https://docs.cocos2d-x.org/cocos2d-x/v3/en/installation/Linux.html). Installing cocos2d itself is not required as the source code is part of the git lfs.

### Clang-format
Install clang-format using apt.
`sudo apt-get install clang-format`

### Clang-tidy
For static analysis with clang-tidy, install clang-tidy.
`sudo apt-get install clang-tidy`
If you encounter into clang-diagnostic-error, because clang-tidy cannot see the system header files, then the easiest solution is to install the clang itself.
`sudo apt-get install clang`
If you do not want to install clang but try other solutions, try searching in google. There are several solutions in stackoverflow, you can check out which one works for you.

### Sanitizers
The thread, address and undefined sanitizers are used as a dynamic analysis tools. These are used for running on googletest.

## Pre-push hook
There is a pre-push hook in tools/pre-push. This hook can be used for running clang-tidy before pushing it to the remote server. It ensures that static analysis is done before pushing any changes to remote server. The pre-push hook can be copied to .git/hoooks/pre-push file. If there is already pre-push hook (usually if you have git lfs enabled, it might already be there), you can append it on the file before other part of the script is run.

## Special Thanks
The UI materials and concept has been driven from Sonar System tutorial. The youtube link for the tutorial is [here](https://www.youtube.com/watch?v=CvG9dJFxQ1U&list=PLRtjMdoYXLf5H1O_AOZtc415UmSQCVs93).
