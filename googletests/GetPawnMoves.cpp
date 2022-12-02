#include "gtest/gtest.h"
#include "MoveGen.h"
#include "Algorithms.h"

TEST(MoveGenTestSuite, GetPawnMoves) {
    Board board;
    MoveGen m = MoveGen(&board);
    std::vector<Move> pawnMoves;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves
    ASSERT_EQ(pawnMoves.size(), 16);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppp2pp/4p3/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3"), 0);
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 15);

    ASSERT_EQ(board.setFEN("2q1r3/3P4/8/8/8/8/8/8 w - - 0 1"), 0);
    pawnMoves = m.getPawnMoves();
    EXPECT_EQ(pawnMoves.size(), 12);

    ASSERT_EQ(board.setFEN("4r3/3P4/8/8/8/8/8/8 w - - 0 1"), 0);
    pawnMoves = m.getPawnMoves();
    EXPECT_EQ(pawnMoves.size(), 8);

    ASSERT_EQ(board.setFEN("8/8/8/8/8/8/3p4/2R1R3 b - - 0 1"), 0);
    pawnMoves = m.getPawnMoves();
    EXPECT_EQ(pawnMoves.size(), 12);

    ASSERT_EQ(board.setFEN("8/8/8/8/8/8/3p4/4R3 b - - 0 1"), 0);
    pawnMoves = m.getPawnMoves();
    EXPECT_EQ(pawnMoves.size(), 8);
}
