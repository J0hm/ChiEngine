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

TEST(BoardTestSuite, MakeUnmakeKnightMovesSameHash) {
    Board board;
    ZobristHasher hasher;
    ASSERT_EQ(board.setFEN("r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 4"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.getLastState().enPassantSquare, ER);
    ASSERT_EQ(board.sideToMove, WHITE);

    std::vector<Move> knightMoves = board.movegen->getKnightMoves();
    ASSERT_EQ(knightMoves.size(), 10);

    int64 oldHash = board.getLastState().hash;

    for (Move m: knightMoves) {
        board.makeMove(m);
        board.unmakeMove();
        int64 newHash = hasher.hashBitBoard(board.bb,
                                            board.sideToMove,
                                            board.getLastState().castlingRights,
                                            board.getLastState().enPassantSquare);

        ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
        ASSERT_EQ(board.getLastState().enPassantSquare, ER);
        ASSERT_EQ(board.sideToMove, WHITE);

        ASSERT_EQ(oldHash, newHash);
    }
}