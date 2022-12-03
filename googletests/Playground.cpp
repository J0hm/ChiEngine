#include "gtest/gtest.h"
#include "Algorithms.h"
#include "ZobristHasher.h"

TEST(PlaygroundSuite, Testing) {
    for(int64 n : BB_SQUARES) std::cout << Algorithms::bitBoardToString(n) << std::endl;
}