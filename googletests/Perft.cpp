#include "gtest/gtest.h"
#include "Board.h"

TEST(MoveGenTestSuite, PerftDefaultFEN) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);

    //ASSERT_EQ(board.perft(1), 20);
    //ASSERT_EQ(board.perft(2), 400);
    //ASSERT_EQ(board.perft(3), 8902);
    //ASSERT_EQ(board.perft(4), 197281);

    ASSERT_EQ(board.perft(5), 4865609); // 35 moves over

//    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/6P1/8/PPPPPP1P/RNBQKBNR b KQkq - 0 1"), 0);
//    ASSERT_EQ(board.perft(2), 421);
}