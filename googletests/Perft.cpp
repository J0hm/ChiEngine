#include "gtest/gtest.h"
#include "Board.h"

TEST(MoveGenTestSuite, PerftDefaultFEN) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
//    ASSERT_EQ(board.perft(1, 1), 20);
//    ASSERT_EQ(board.perft(2, 2), 400);
//    ASSERT_EQ(board.perft(3, 3), 8902);
//    ASSERT_EQ(board.perft(4, 4), 197281);
//    ASSERT_EQ(board.perft(5, 5), 4865609);
//    ASSERT_EQ(board.perft(6, 6), 119060324);

    ASSERT_EQ(board.setFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "), 0);
    //ASSERT_EQ(board.perft(1, 1), 48);
    //ASSERT_EQ(board.perft(2, 2), 2039); // missing 49 moves
    /* a2a3 - 1 less
     * b2b3 - 1 less
     * g2g3 - 1 less
     * d5d6 - 1 less
     * a2a4 - 1 less
     * g2g4 - 1 less
     */
    //board.makeMove("g2g4");
    //ASSERT_EQ(board.perft(1, 1), 42);

    ASSERT_EQ(board.perft(3, 4), 97862);
    //ASSERT_EQ(board.perft(4, 4), 4085603);
}