#include "gtest/gtest.h"
#include "Board.cpp"

TEST(BoardTestSuite, DefaultFENBB) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    std::string emptySquares = Algorithms::bitBoardToString(board.bb.emptySquares);
    std::string occupiedSquares = Algorithms::bitBoardToString(board.bb.occupiedSquares);
    std::string blackSquares = Algorithms::bitBoardToString(board.bb.pcsOfColor[BLACK]);
    std::string whiteSquares = Algorithms::bitBoardToString(board.bb.pcsOfColor[WHITE]);

    std::string whitePawns = Algorithms::bitBoardToString(board.bb.pcs[W_PAWN]);
    std::string whiteKnights = Algorithms::bitBoardToString(board.bb.pcs[W_KNIGHT]);
    std::string whiteKing = Algorithms::bitBoardToString(board.bb.pcs[W_KING]);
    std::string whiteQueen = Algorithms::bitBoardToString(board.bb.pcs[W_QUEEN]);
    std::string whiteBishop = Algorithms::bitBoardToString(board.bb.pcs[W_BISHOP]);
    std::string whiteRook = Algorithms::bitBoardToString(board.bb.pcs[W_ROOK]);

    std::string blackPawns = Algorithms::bitBoardToString(board.bb.pcs[B_PAWN]);
    std::string blackKnights = Algorithms::bitBoardToString(board.bb.pcs[B_KNIGHT]);
    std::string blackKing = Algorithms::bitBoardToString(board.bb.pcs[B_KING]);
    std::string blackQueen = Algorithms::bitBoardToString(board.bb.pcs[B_QUEEN]);
    std::string blackBishop = Algorithms::bitBoardToString(board.bb.pcs[B_BISHOP]);
    std::string blackRook = Algorithms::bitBoardToString(board.bb.pcs[B_ROOK]);

    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n11111111"
              "\n11111111"
              "\n11111111"
              "\n11111111"
              "\n00000000"
              "\n00000000", emptySquares);

    ASSERT_EQ("\n11111111"
              "\n11111111"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n11111111"
              "\n11111111", occupiedSquares);

    ASSERT_EQ("\n11111111"
              "\n11111111"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000", blackSquares);
    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n11111111"
              "\n11111111", whiteSquares);

    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n11111111"
              "\n00000000", whitePawns);
    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n01000010", whiteKnights);
    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00001000", whiteKing);
    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00010000", whiteQueen);
    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00100100", whiteBishop);
    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n10000001", whiteRook);

    ASSERT_EQ("\n00000000"
              "\n11111111"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000", blackPawns);
    ASSERT_EQ("\n01000010"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000", blackKnights);
    ASSERT_EQ("\n00001000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000", blackKing);
    ASSERT_EQ("\n00010000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000", blackQueen);
    ASSERT_EQ("\n00100100"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000", blackBishop);
    ASSERT_EQ("\n10000001"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000", blackRook);
}

TEST(BoardTestSuite, DefaultFenState) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);

}