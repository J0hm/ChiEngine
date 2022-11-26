#include "gtest/gtest.h"
#include "MagicMoves.h"
#include "Algorithms.h"

TEST(MagicMovesTestSuite, RookNoBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    magic->initMagics();

    attacks = magic->getRookAttacks(E5, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n11110111"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000");

    attacks = magic->getRookAttacks(A1, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n01111111");

    attacks = magic->getRookAttacks(H1, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n11111110");

    attacks = magic->getRookAttacks(A8, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n01111111"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000");

    attacks = magic->getRookAttacks(H8, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n11111110"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001");
}

TEST(MagicMovesTestSuite, BishopNoBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    magic->initMagics();

    attacks = magic->getBishopAttacks(E5, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n01000001"
              "\n00100010"
              "\n00010100"
              "\n00000000"
              "\n00010100"
              "\n00100010"
              "\n01000001"
              "\n10000000");

    attacks = magic->getBishopAttacks(A1, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000001"
              "\n00000010"
              "\n00000100"
              "\n00001000"
              "\n00010000"
              "\n00100000"
              "\n01000000"
              "\n00000000");

    attacks = magic->getBishopAttacks(H1, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n10000000"
              "\n01000000"
              "\n00100000"
              "\n00010000"
              "\n00001000"
              "\n00000100"
              "\n00000010"
              "\n00000000");

    attacks = magic->getBishopAttacks(A8, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n01000000"
              "\n00100000"
              "\n00010000"
              "\n00001000"
              "\n00000100"
              "\n00000010"
              "\n00000001");

    attacks = magic->getBishopAttacks(H8, 0);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00000010"
              "\n00000100"
              "\n00001000"
              "\n00010000"
              "\n00100000"
              "\n01000000"
              "\n10000000");
}

TEST(MagicMovesTestSuite, RookWithBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    magic->initMagics();

    // occupancy:
    /* 11111111
     * 11111111
     * 00000000
     * 00000000
     * 00000000
     * 00000000
     */
//    attacks = magic->getRookAttacks(E5, 0xFFFF00000000);
//    std::cout << Algorithms::bitBoardToString(attacks) << std::endl;
//    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
//              "\n00000000"
//              "\n00000000"
//              "\n11110111"
//              "\n00001000"
//              "\n00001000"
//              "\n00001000"
//              "\n00001000"
//              "\n00001000");

    attacks = magic->getRookAttacks(A1, 0xFFFF00000000);
    std::cout << Algorithms::bitBoardToString(attacks) << std::endl;
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n01111111");

    // occupancy:
    /* 00000000
     * 11111111
     * 00000000
     * 00000000
     * 00000000
     * 00000000
     */
    attacks = magic->getRookAttacks(E5, 0x00FF00000000);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00000000"
              "\n11110111"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000");

    attacks = magic->getRookAttacks(A1, 0x00FF00000000);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n01111111");

//    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
//              "\n00000000"
//              "\n00000000"
//              "\n00000000"
//              "\n00000000"
//              "\n00000000"
//              "\n00000000"
//              "\n00000000"
//              "\n00000000");
}