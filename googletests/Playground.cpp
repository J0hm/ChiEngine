#include "gtest/gtest.h"
#include "Algorithms.h"

TEST(PlaygroundSuite, TestGenKngihts) {
    int64 square = BB_SQUARES[A5];
    int64 attacks =
            (((square << 1) | (square >> 9) | (square >> 7))) |
            (square << 7) |
            (square << 8) |
            (square << 9) |
            (square >> 1) |
            (square >> 8);


    std::cout << Algorithms::bitBoardToString(attacks);
}