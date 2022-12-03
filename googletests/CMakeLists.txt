# 'Google_test' is the subproject name
project(googletests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run ParseFen.cpp ParseMove.cpp MagicMoves.cpp Playground.cpp GetMoves.cpp MakeUnmake.cpp Perft.cpp)
target_link_libraries(Google_Tests_run gtest gmock gtest_main src)

