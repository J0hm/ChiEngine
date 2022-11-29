#include "gtest/gtest.h"
#include "Algorithms.h"

TEST(PlaygroundSuite, TestGenKngihts) {
    int64 FILE_H = 0x0101010101010101;
    int64 FILE_A = 0x8080808080808080;
    int64 RANK_1 = 0xFF;
    int64 RANK_8 = 0xFF00000000000000;
    int64 square = BB_SQUARES[A1];
    int64 attacks = (((square << 1) | (square >> 7) | (square << 9)) & ~0x0101010101010101) |
                    (((square >> 9) | (square << 7) | (square >> 1)) & ~0x8080808080808080) |
                    ((square << 8) & ~0xFF) |
                    ((square >> 8) & ~0xFF00000000000000);


    std::cout << Algorithms::bitBoardToString(attacks);
}