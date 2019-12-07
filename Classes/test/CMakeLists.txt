add_executable(unittest_exec
    ../GameUtil.cpp
    ../AI.cc
    ../GameLogic.cc
    GameTest.cpp
    GameLogicTest.cpp
)

target_link_libraries(unittest_exec ${GTEST_STATIC_LIBRARIES} pthread)
