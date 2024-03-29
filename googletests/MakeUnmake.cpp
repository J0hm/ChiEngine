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
}

TEST(BoardTestSuite, MakeUnmakeKeyListTest) {
    Board board;
    std::vector<int64> keys;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);

    keys = board.getKeyHistory();
    ASSERT_EQ(keys.size(), 1);
    board.makeMove("b1c3");
    keys = board.getKeyHistory();
    ASSERT_EQ(keys.size(), 2);
//    for(auto key : keys) std::cout << std::hex << key << " ";
//    std::cout << std::endl;
    board.unmakeMove();
    keys = board.getKeyHistory();
    ASSERT_EQ(keys.size(), 1);
//    for(auto key : keys) std::cout << std::hex << key << " ";
//    std::cout << std::endl;

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

TEST(BoardTestSuite, MakeUnmakeAllLegalMovesSameHash) {
    Board board;
    ZobristHasher hasher;
    ASSERT_EQ(board.setFEN("r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 4"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.getLastState().enPassantSquare, ER);
    ASSERT_EQ(board.sideToMove, WHITE);

    std::vector<Move> moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 29);

    int64 oldHash = board.getLastState().hash;

    for (Move m: moves) {
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

        ASSERT_EQ("\n01000010"
                  "\n00001000"
                  "\n11011011"
                  "\n11110111"
                  "\n11110111"
                  "\n11011011"
                  "\n00001000"
                  "\n01000010", emptySquares);

        ASSERT_EQ("\n10111101"
                  "\n11110111"
                  "\n00100100"
                  "\n00001000"
                  "\n00001000"
                  "\n00100100"
                  "\n11110111"
                  "\n10111101", occupiedSquares);

        ASSERT_EQ("\n10111101"
                  "\n11110111"
                  "\n00100100"
                  "\n00001000"
                  "\n00000000"
                  "\n00000000"
                  "\n00000000"
                  "\n00000000", blackSquares);
        ASSERT_EQ("\n00000000"
                  "\n00000000"
                  "\n00000000"
                  "\n00000000"
                  "\n00001000"
                  "\n00100100"
                  "\n11110111"
                  "\n10111101", whiteSquares);

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
                  "\n00100100"
                  "\n00000000"
                  "\n00000000", whiteKnights);
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
                  "\n11110111"
                  "\n00000000"
                  "\n00001000"
                  "\n00000000"
                  "\n00000000"
                  "\n00000000"
                  "\n00000000", blackPawns);
        ASSERT_EQ("\n00000000"
                  "\n00000000"
                  "\n00100100"
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
}

TEST(BoardTestSuite, MakeUnmakeKingPawns) {
    Board board;
    ZobristHasher hasher;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.getLastState().enPassantSquare, ER);
    ASSERT_EQ(board.sideToMove, WHITE);

    std::vector<Move> moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 29);

    int64 oldHash = board.getLastState().hash;

    for (Move m: moves) {
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
                  "\n00001000"
                  "\n11111111"
                  "\n11110111"
                  "\n11110111"
                  "\n11111111"
                  "\n00001000"
                  "\n00000000", emptySquares);

        ASSERT_EQ("\n11111111"
                  "\n11110111"
                  "\n00000000"
                  "\n00001000"
                  "\n00001000"
                  "\n00000000"
                  "\n11110111"
                  "\n11111111", occupiedSquares);

        ASSERT_EQ("\n11111111"
                  "\n11110111"
                  "\n00000000"
                  "\n00001000"
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
                  "\n11110111"
                  "\n00000000"
                  "\n00001000"
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
}

TEST(BoardTestSuite, MakeUnmakeKingPawnsBlack) {
    Board board;
    ZobristHasher hasher;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1"), 0);
    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.getLastState().enPassantSquare, ER);
    ASSERT_EQ(board.sideToMove, BLACK);

    std::vector<Move> moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 29);

    int64 oldHash = board.getLastState().hash;

    for (Move m: moves) {
        board.makeMove(m);
        board.unmakeMove();
        int64 newHash = hasher.hashBitBoard(board.bb,
                                            board.sideToMove,
                                            board.getLastState().castlingRights,
                                            board.getLastState().enPassantSquare);

        ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
        ASSERT_EQ(board.getLastState().enPassantSquare, ER);
        ASSERT_EQ(board.sideToMove, BLACK);

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
                  "\n00001000"
                  "\n11111111"
                  "\n11110111"
                  "\n11110111"
                  "\n11111111"
                  "\n00001000"
                  "\n00000000", emptySquares);

        ASSERT_EQ("\n11111111"
                  "\n11110111"
                  "\n00000000"
                  "\n00001000"
                  "\n00001000"
                  "\n00000000"
                  "\n11110111"
                  "\n11111111", occupiedSquares);

        ASSERT_EQ("\n11111111"
                  "\n11110111"
                  "\n00000000"
                  "\n00001000"
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
                  "\n11110111"
                  "\n00000000"
                  "\n00001000"
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
}

TEST(BoardTestSuite, MakeUnmakeAllMovesRecursive) {
    Board board;
    ZobristHasher hasher;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);

    ASSERT_EQ(board.getLastState().castlingRights, 0b1111);
    ASSERT_EQ(board.getLastState().enPassantSquare, ER);
    ASSERT_EQ(board.sideToMove, WHITE);
    ASSERT_EQ(board.currentPly, 1);

    std::vector<Move> moves = board.movegen->getLegalMoves();
    int64 oldHash = board.getLastState().hash;

    for (Move m: moves) {
        board.makeMove(m);
        std::vector<Move> rMoves = board.movegen->getLegalMoves();
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
        EXPECT_EQ(rMoves.size(), 20);

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
}

TEST(BoardTestSuite, MakeUnmakePawnMoves) {
    Board board;
    MoveGen m = MoveGen(&board);
    std::vector<Move> pawnMoves;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("c2c4");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("d7d5");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("c4d5");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 14);

    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);

    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);
    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);
}

TEST(BoardTestSuite, MakeUnmakeEnPassant) {
    Board board;
    MoveGen m = MoveGen(&board);
    std::vector<Move> pawnMoves;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("d2d4");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("f7f6");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 15);

    board.makeMove("d4d5");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 14);

    board.makeMove("e7e5");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("d5e6");
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 14);

    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);
    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 14);
    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 15);
    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);
    board.unmakeMove();
    pawnMoves = m.getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 16);
}

TEST(BoardTestSuite, MakeUnmakeCastle) {
    Board board;
    BoardBB oldBoard{}, newBoard{};
    std::vector<Move> kingMoves;

    ASSERT_EQ(board.setFEN("8/8/8/8/8/8/8/R3K2R w KQkq - 0 1"), 0);
    kingMoves = board.movegen->getKingMoves();
    ASSERT_EQ(kingMoves.size(), 7);

    oldBoard = Board::copyBB(board.bb);
    board.makeMove("e1g1");
    board.unmakeMove();
    newBoard = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(oldBoard, newBoard));

    oldBoard = Board::copyBB(board.bb);
    board.makeMove("e1c1");
    board.unmakeMove();
    newBoard = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(oldBoard, newBoard));

    ASSERT_EQ(board.setFEN("r3k2r/8/8/8/8/8/8/8 b kq - 0 1"), 0);
    kingMoves = board.movegen->getKingMoves();
    ASSERT_EQ(kingMoves.size(), 7);

    oldBoard = Board::copyBB(board.bb);
    board.makeMove("e8g8");
    board.unmakeMove();
    newBoard = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(oldBoard, newBoard));

    oldBoard = Board::copyBB(board.bb);
    board.makeMove("e8c8");
    board.unmakeMove();
    newBoard = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(oldBoard, newBoard));
}

TEST(BoardTestSuite, MakeUnmakePromotions) {
    Board board;
    BoardBB before{}, after{};
    std::vector<Move> pawnMoves;

    ASSERT_EQ(board.setFEN("4n3/3P4/8/8/8/8/3p4/2R5 b - - 0 1"), 0);
    pawnMoves = board.movegen->getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 8);

    ASSERT_EQ(board.setFEN("4n3/3P4/8/8/8/8/3p4/2R5 w - - 0 1"), 0);
    pawnMoves = board.movegen->getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 8);

    before = Board::copyBB(board.bb);
    board.makeMove("d7d8n");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d7d8q");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d7d8b");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d7d8r");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d7e8q");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    ASSERT_EQ(board.setFEN("4n3/3P4/8/8/8/8/3p4/2R5 b - - 0 1"), 0);
    pawnMoves = board.movegen->getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 8);

    before = Board::copyBB(board.bb);
    board.makeMove("d2d1n");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d2d1q");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d2d1b");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d2d1r");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("d2c1q");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    ASSERT_EQ(board.setFEN("4n3/3P4/8/8/8/8/6p1/7R b - - 0 1"), 0);
    pawnMoves = board.movegen->getPawnMoves();
    ASSERT_EQ(pawnMoves.size(), 8);

    before = Board::copyBB(board.bb);
    board.makeMove("g2g1n");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("g2g1b");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("g2g1r");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("g2g1q");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("g2h1n");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("g2h1b");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("g2h1r");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));

    before = Board::copyBB(board.bb);
    board.makeMove("g2h1q");
    board.unmakeMove();
    after = Board::copyBB(board.bb);
    ASSERT_TRUE(board.bbEqual(before, after));
}