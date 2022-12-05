#include "gtest/gtest.h"
#include "Board.h"
#include "Algorithms.h"

TEST(MoveGenTestSuite, KingCantCheckItself) {
    Board b;
    Move m;
    ASSERT_EQ(b.setFEN("rnbqkbnr/ppppp1pp/5p2/4N3/8/8/PPPPPPPP/RNBQKB1R b KQkq - 0 1"), 0);

    m = b.parseMove("e8f7");
    ASSERT_FALSE(b.movegen->isLegal(m));
    m = b.parseMove("f6xe5");
    ASSERT_TRUE(b.movegen->isLegal(m));
}
