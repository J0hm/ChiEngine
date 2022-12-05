#include "gtest/gtest.h"
#include "Board.h"
#include "Algorithms.h"

TEST(MoveGenTestSuire, CalcAttackBitboard) {
    Board board;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);

    board.movegen->calcAllAttackBitboard(BLACK);
    std::cout << Algorithms::bitBoardToString(board.movegen->allAttackBitBoard[BLACK]) << std::endl;
}