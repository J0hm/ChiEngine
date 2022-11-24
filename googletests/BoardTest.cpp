#include "gtest/gtest.h"
#include "Board.cpp"

TEST(BoardTestSuite, DefaultFEN) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);

    ASSERT_EQ(board.sideToMove, WHITE);
    ASSERT_EQ(board.currentPly, 1);

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

TEST(BoardTestSuite, E4FENBB) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"), 0);

    ASSERT_EQ(board.sideToMove, BLACK);
    ASSERT_EQ(board.currentPly, 2);

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
              "\n11110111"
              "\n11111111"
              "\n00001000"
              "\n00000000", emptySquares);

    ASSERT_EQ("\n11111111"
              "\n11111111"
              "\n00000000"
              "\n00000000"
              "\n00001000"
              "\n00000000"
              "\n11110111"
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
              "\n00001000"
              "\n00000000"
              "\n11110111"
              "\n11111111", whiteSquares);

    ASSERT_EQ("\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00000000"
              "\n00001000"
              "\n00000000"
              "\n11110111"
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

TEST(BoardTestSuite, E4FENState) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"), 0);
    BoardState state = board.getLastState();
    ASSERT_EQ(state.castlingRights, 0b1111);
    ASSERT_EQ(state.enPassantSquare, E3);
}

TEST(BoardTestSuite, DefaultFENParseMoveE4) { // checks if parsing the move E2E4 produces the proper result
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"), 0);
    Move m = board.parseMove("e2e4");
    Move m2 = board.parseMove("e2E4");
    Move m3 = board.parseMove("E2e4");
    Move m4 = board.parseMove("E2E4");
    ASSERT_TRUE(m == m2);
    ASSERT_TRUE(m2 == m3);
    ASSERT_TRUE(m3 == m4);

    ASSERT_FALSE(m.isCapture());
    ASSERT_FALSE(m.isEnPassant());
    ASSERT_FALSE(m.isPromotion());
    ASSERT_FALSE(m.isQueenSideCastling());
    ASSERT_FALSE(m.isKingSideCastling());
    ASSERT_TRUE(m.isDoublePawnPush());
    ASSERT_EQ(m.getDest(), E4);
    ASSERT_EQ(m.getOrigin(), E2);
    ASSERT_EQ(m.getPieceType(), PAWN);
    ASSERT_EQ(m.getCapturedPieceType(), NO_PIECE);
    ASSERT_EQ(m.getPreviousCastlingRights(), 0b1111);
}

TEST(BoardTestSuite, DefaultFENParseMoveE3) { // checks if parsing the move E2E3 produces the proper result
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"), 0);
    Move m = board.parseMove("e2e3");

    ASSERT_FALSE(m.isCapture());
    ASSERT_FALSE(m.isEnPassant());
    ASSERT_FALSE(m.isPromotion());
    ASSERT_FALSE(m.isQueenSideCastling());
    ASSERT_FALSE(m.isKingSideCastling());
    ASSERT_FALSE(m.isDoublePawnPush());
    ASSERT_EQ(m.getDest(), E3);
    ASSERT_EQ(m.getOrigin(), E2);
    ASSERT_EQ(m.getPieceType(), PAWN);
    ASSERT_EQ(m.getCapturedPieceType(), NO_PIECE);
    ASSERT_EQ(m.getPreviousCastlingRights(), 0b1111);
}

TEST(BoardTestSuite, ParseMoveEnPassantCapture) { // checks if parsing the move E2E4 produces the proper result
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/ppp1ppp1/8/3pP2p/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.currentPly, 5);

    Move m = board.parseMove("e5xd6");
    Move m2 = board.parseMove("E5xd6");
    Move m3 = board.parseMove("e5xD6");
    Move m4 = board.parseMove("E5xD6");
    ASSERT_TRUE(m == m2);
    ASSERT_TRUE(m2 == m3);
    ASSERT_TRUE(m3 == m4);

    ASSERT_TRUE(m.isCapture());
    ASSERT_TRUE(m.isEnPassant());
    ASSERT_FALSE(m.isPromotion());
    ASSERT_FALSE(m.isQueenSideCastling());
    ASSERT_FALSE(m.isKingSideCastling());
    ASSERT_FALSE(m.isDoublePawnPush());
    ASSERT_EQ(m.getDest(), D6);
    ASSERT_EQ(m.getOrigin(), E5);
    ASSERT_EQ(m.getPieceType(), PAWN);
    ASSERT_EQ(m.getCapturedPieceType(), PAWN);
    ASSERT_EQ(m.getPreviousCastlingRights(), 0b1111);
}

TEST(BoardTestSuite, ParseMoveWhiteCastleKingside) { // checks parsing white castle kingside
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppp2pp/8/4pp2/4P3/5N2/PPPPBPPP/RNBQK2R w KQkq - 0 4"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.currentPly, 7);

    Move m = board.parseMove("e1g1");

    ASSERT_FALSE(m.isCapture());
    ASSERT_FALSE(m.isEnPassant());
    ASSERT_FALSE(m.isPromotion());
    ASSERT_FALSE(m.isQueenSideCastling());
    ASSERT_TRUE(m.isKingSideCastling());
    ASSERT_FALSE(m.isDoublePawnPush());
    ASSERT_EQ(m.getDest(), G1);
    ASSERT_EQ(m.getOrigin(), E1);
    ASSERT_EQ(m.getPieceType(), KING);
    ASSERT_EQ(m.getCapturedPieceType(), NO_PIECE);
    ASSERT_EQ(m.getPreviousCastlingRights(), 0b1111);
}

TEST(BoardTestSuite, ParseMoveWhiteCastleQueenside) { // checks parsing white castle queenside
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/ppp5/3ppppp/8/2P5/2NP4/PPQBPPPP/R3KBNR w KQkq - 0 6"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    Move m = board.parseMove("e1c1");

    ASSERT_FALSE(m.isCapture());
    ASSERT_FALSE(m.isEnPassant());
    ASSERT_FALSE(m.isPromotion());
    ASSERT_TRUE(m.isQueenSideCastling());
    ASSERT_FALSE(m.isKingSideCastling());
    ASSERT_FALSE(m.isDoublePawnPush());
    ASSERT_EQ(m.getDest(), C1);
    ASSERT_EQ(m.getOrigin(), E1);
    ASSERT_EQ(m.getPieceType(), KING);
    ASSERT_EQ(m.getCapturedPieceType(), NO_PIECE);
    ASSERT_EQ(m.getPreviousCastlingRights(), 0b1111);
}

TEST(BoardTestSuite, ParseMoveBlackCastleKingside) { // checks parsing black castle kingside
    Board board;
    ASSERT_EQ(board.setFEN("rnbqk2r/ppppbppp/5n2/4p3/4P1P1/7P/PPPP1P2/RNBQKBNR b KQkq - 0 4"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    Move m = board.parseMove("e8g8");

    ASSERT_FALSE(m.isCapture());
    ASSERT_FALSE(m.isEnPassant());
    ASSERT_FALSE(m.isPromotion());
    ASSERT_FALSE(m.isQueenSideCastling());
    ASSERT_TRUE(m.isKingSideCastling());
    ASSERT_FALSE(m.isDoublePawnPush());
    ASSERT_EQ(m.getDest(), G8);
    ASSERT_EQ(m.getOrigin(), E8);
    ASSERT_EQ(m.getPieceType(), KING);
    ASSERT_EQ(m.getCapturedPieceType(), NO_PIECE);
    ASSERT_EQ(m.getPreviousCastlingRights(), 0b1111);
}

TEST(BoardTestSuite, ParseMoveBlackCastleQueenside) { // checks parsing black castle queenside
    Board board;
    ASSERT_EQ(board.setFEN("r3kbnr/pppqpppp/2n5/3p4/3PP3/7P/PPP2P1P/RNBQKBNR b KQkq - 0 5"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    Move m = board.parseMove("e8c8");

    ASSERT_FALSE(m.isCapture());
    ASSERT_FALSE(m.isEnPassant());
    ASSERT_FALSE(m.isPromotion());
    ASSERT_TRUE(m.isQueenSideCastling());
    ASSERT_FALSE(m.isKingSideCastling());
    ASSERT_FALSE(m.isDoublePawnPush());
    ASSERT_EQ(m.getDest(), C8);
    ASSERT_EQ(m.getOrigin(), E8);
    ASSERT_EQ(m.getPieceType(), KING);
    ASSERT_EQ(m.getCapturedPieceType(), NO_PIECE);
    ASSERT_EQ(m.getPreviousCastlingRights(), 0b1111);
}