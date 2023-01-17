#include "gtest/gtest.h"
#include "Board.h"
#include "Algorithms.h"

TEST(MoveGenTestSuite, KingCantCheckItself) {
    Board b;
    Move m;
    ASSERT_EQ(b.setFEN("rnbqkbnr/ppppp1pp/5p2/4N3/8/8/PPPPPPPP/RNBQKB1R b KQkq - 0 1"), 0);
    m = b.parseMove("e8f7");
    ASSERT_FALSE(b.movegen->isLegal(m));
    m = b.parseMove("f6e5");
    ASSERT_TRUE(b.movegen->isLegal(m));

    ASSERT_EQ(b.setFEN("rnbqkbnr/p1pppppp/8/8/1p6/3P4/PPPKPPPP/RNBQ1BNR w HAkq - 0 1"), 0);

    b.movegen->calcAllAttackBitboard(BLACK);

    m = b.parseMove("d2c3");
    ASSERT_FALSE(b.movegen->isLegal(m));
}
