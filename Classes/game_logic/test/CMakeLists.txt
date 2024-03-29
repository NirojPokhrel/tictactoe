add_library(logic_lib 
                ../GameUtil.cpp
                ../AI.cc
                ../GameLogic.cc
                ../HumanPlayer.cpp)

target_compile_options(logic_lib PRIVATE -Wall 
                -Wextra 
                -Wunused 
                -Wuninitialized 
                -Wmissing-noreturn 
                -Wunreachable-code
                -Wsign-compare 
                #-Wstrict-null-sentinel 
                -Wreturn-type 
                -Wcast-qual 
                -Wconversion
                -Wenum-compare 
                -Wsign-conversion)
if (CLANGTIDY)
    return()
endif()                
add_executable(unittest_exec
    GameTest.cpp
    GameLogicTest.cpp
    HumanPlayerTest.cpp
)
if (SANITIZER)
    message(STATUS "Sanitizer : ${SANITIZER}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=${SANITIZER}")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=${SANITIZER}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=${SANITIZER}")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=${SANITIZER}")
endif()        

target_link_libraries(unittest_exec ${GTEST_STATIC_LIBRARIES} pthread logic_lib)
find_library (LIBRARY_EXISTS
  NAMES   libgmock.a
  HINTS   "${GTEST_SOURCE_DIR}"
)
if (NOT LIBRARY_EXISTS)
    add_dependencies(unittest_exec googletestlocal)
endif()

enable_testing()
message(STATUS "Executable - ${CMAKE_BINARY_DIR}/Classes/test/unittest_exec")
add_test(
    NAME unittest_run
    COMMAND ${CMAKE_BINARY_DIR}/Classes/test/unittest_exec
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)