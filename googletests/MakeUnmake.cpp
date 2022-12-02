#include "gtest/gtest.h"
#include "Board.h"
#include "Algorithms.h"

TEST(BoardTestSuite, MakeUnmakePawnMovesSameHash) {
    Board board;
    ZobristHasher hasher;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);

    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.getLastState().enPassantSquare, ER);
    ASSERT_EQ(board.sideToMove, WHITE);
    ASSERT_EQ(board.currentPly, 1);

    std::vector<Move> pawnMoves = board.movegen->getPawnMoves();
    int64 oldHash = board.getLastState().hash;

    for (Move m: pawnMoves) {
        board.makeMove(m);
        board.unmakeMove();
        int64 newHash = hasher.hashBitBoard(board.bb,
                                            board.sideToMove,
                                            board.getLastState().castlingRights,
                                            board.getLastState().enPassantSquare);

        ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
        ASSERT_EQ(board.getLastState().enPassantSquare, ER);
        ASSERT_EQ(board.sideToMove, WHITE);
        ASSERT_EQ(board.currentPly, 1);

        ASSERT_EQ(oldHash, newHash);
    }
}