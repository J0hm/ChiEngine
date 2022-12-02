#include "gtest/gtest.h"
#include "MoveGen.h"
#include "Algorithms.h"

TEST(MoveGenTestSuite, GetPawnMoves) {
    Board board;
    MoveGen m = MoveGen(&board);
    std::vector<Move> pawnMoves;

//    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
//    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves
//    ASSERT_EQ(pawnMoves.size(), 16);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppp2pp/4p3/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3"), 0);
    pawnMoves = m.getPawnMoves();
    //ASSERT_EQ(pawnMoves.size(), 15);

    //std::cout << Algorithms::bitBoardToString(board.bb.emptySquares) << std::endl;

    for(Move m : pawnMoves) std::cout << m;
}
