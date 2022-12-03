#include "gtest/gtest.h"
#include "MagicMoves.h"
#include "Algorithms.h"

TEST(MagicMovesTestSuite, RookNoBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    magic->initMagics();

    attacks = magic->getRookAttacks(SHIFTED_SQUARE[E5], BB_SQUARES[E5]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n11110111"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000");

    attacks = magic->getRookAttacks(SHIFTED_SQUARE[A1], BB_SQUARES[A1]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n01111111");

    attacks = magic->getRookAttacks(SHIFTED_SQUARE[H1], BB_SQUARES[H1]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n00000001"
              "\n11111110");

    attacks = magic->getRookAttacks(SHIFTED_SQUARE[A8], BB_SQUARES[A8]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n01111111"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000");

    attacks = magic->getRookAttacks(SHIFTED_SQUARE[H8], BB_SQUARES[H8]);
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

    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[E5], BB_SQUARES[E5]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n01000001"
              "\n00100010"
              "\n00010100"
              "\n00000000"
              "\n00010100"
              "\n00100010"
              "\n01000001"
              "\n10000000");

    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[A1], BB_SQUARES[A1]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000001"
              "\n00000010"
              "\n00000100"
              "\n00001000"
              "\n00010000"
              "\n00100000"
              "\n01000000"
              "\n00000000");

    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[H1], BB_SQUARES[H1]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n10000000"
              "\n01000000"
              "\n00100000"
              "\n00010000"
              "\n00001000"
              "\n00000100"
              "\n00000010"
              "\n00000000");

    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[A8], BB_SQUARES[A8]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n01000000"
              "\n00100000"
              "\n00010000"
              "\n00001000"
              "\n00000100"
              "\n00000010"
              "\n00000001");

    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[H8], BB_SQUARES[H8]);
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

TEST(MagicMovesTestSuite, QueenNoBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    magic->initMagics();

    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[E5], BB_SQUARES[E5]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n01001001"
              "\n00101010"
              "\n00011100"
              "\n11110111"
              "\n00011100"
              "\n00101010"
              "\n01001001"
              "\n10001000");

    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[A1], BB_SQUARES[A1]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n10000001"
              "\n10000010"
              "\n10000100"
              "\n10001000"
              "\n10010000"
              "\n10100000"
              "\n11000000"
              "\n01111111");

    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[H1], BB_SQUARES[H1]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n10000001"
              "\n01000001"
              "\n00100001"
              "\n00010001"
              "\n00001001"
              "\n00000101"
              "\n00000011"
              "\n11111110");

    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[A8], BB_SQUARES[A8]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n01111111"
              "\n11000000"
              "\n10100000"
              "\n10010000"
              "\n10001000"
              "\n10000100"
              "\n10000010"
              "\n10000001");

    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[H8], BB_SQUARES[H8]);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n11111110"
              "\n00000011"
              "\n00000101"
              "\n00001001"
              "\n00010001"
              "\n00100001"
              "\n01000001"
              "\n10000001");
}

TEST(MagicMovesTestSuite, RookWithBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    int64 occupancy;
    magic->initMagics();

    occupancy = 0xFFFF000000000000 | BB_SQUARES[E6];
    attacks = magic->getRookAttacks(SHIFTED_SQUARE[E6], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00001000"
              "\n11110111"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000");

    occupancy = 0xFFFF000000000000 | BB_SQUARES[A1];
    attacks = magic->getRookAttacks(SHIFTED_SQUARE[A1], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n01111111");

    occupancy = 0x00FF000000000000 | BB_SQUARES[E6];
    attacks = magic->getRookAttacks(SHIFTED_SQUARE[E6], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00001000"
              "\n11110111"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000"
              "\n00001000");

    occupancy = 0x00FF000000000000 | BB_SQUARES[A1];
    attacks = magic->getRookAttacks(SHIFTED_SQUARE[A1], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n10000000"
              "\n01111111");
}

TEST(MagicMovesTestSuite, BishopWithBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    int64 occupancy;
    magic->initMagics();

    occupancy = (0xFFFF000000000000 | BB_SQUARES[E6]);
    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[E6], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00010100"
              "\n00000000"
              "\n00010100"
              "\n00100010"
              "\n01000001"
              "\n10000000"
              "\n00000000");

    occupancy = 0xFFFF000000000000 | BB_SQUARES[A1];
    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[A1], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00000010"
              "\n00000100"
              "\n00001000"
              "\n00010000"
              "\n00100000"
              "\n01000000"
              "\n00000000");

    occupancy = 0x00FF000000000000 | BB_SQUARES[E6];
    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[E6], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00010100"
              "\n00000000"
              "\n00010100"
              "\n00100010"
              "\n01000001"
              "\n10000000"
              "\n00000000");

    occupancy = 0x00FF000000000000 | BB_SQUARES[A1];
    attacks = magic->getBishopAttacks(SHIFTED_SQUARE[A1], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00000010"
              "\n00000100"
              "\n00001000"
              "\n00010000"
              "\n00100000"
              "\n01000000"
              "\n00000000");
}

TEST(MagicMovesTestSuite, QueenWithBlockers) {
    auto *magic = new MagicMoves();
    EBitBoard attacks;
    int64 occupancy;
    magic->initMagics();

    occupancy = (0xFFFF000000000000 | BB_SQUARES[E6]);
    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[E6], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00011100"
              "\n11110111"
              "\n00011100"
              "\n00101010"
              "\n01001001"
              "\n10001000"
              "\n00001000");

    occupancy = 0xFFFF000000000000 | BB_SQUARES[A1];
    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[A1], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n10000010"
              "\n10000100"
              "\n10001000"
              "\n10010000"
              "\n10100000"
              "\n11000000"
              "\n01111111");

    occupancy = 0x00FF000000000000 | BB_SQUARES[E6];
    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[E6], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n00011100"
              "\n11110111"
              "\n00011100"
              "\n00101010"
              "\n01001001"
              "\n10001000"
              "\n00001000");

    occupancy = 0x00FF000000000000 | BB_SQUARES[A1];
    attacks = magic->getQueenAttacks(SHIFTED_SQUARE[A1], occupancy);
    ASSERT_EQ(Algorithms::bitBoardToString(attacks),
              "\n00000000"
              "\n10000010"
              "\n10000100"
              "\n10001000"
              "\n10010000"
              "\n10100000"
              "\n11000000"
              "\n01111111");
}