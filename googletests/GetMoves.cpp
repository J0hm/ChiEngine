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

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1"), 0);
    pawnMoves = m.getPawnMoves();
    EXPECT_EQ(pawnMoves.size(), 16);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppp1p/8/6p1/7P/8/PPPPPPP1/RNBQKBNR w KQkq - 0 1"), 0);
    pawnMoves = m.getPawnMoves();
    EXPECT_EQ(pawnMoves.size(), 16);

    ASSERT_EQ(board.setFEN("rnbqk1nr/pppp1ppp/8/4p3/1b5P/1P6/P1PPPPP1/RNBQKBNR w KQkq - 0 1"), 0);
    pawnMoves = m.getPawnMoves();

    EXPECT_EQ(pawnMoves.size(), 13);
}

TEST(MoveGenTestSuite, GetPawnMovesEnPassant) { // literal "edge" case lol en passant on edge of board
    Board board;
    MoveGen m = MoveGen(&board);
    std::vector<Move> pawnMoves;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves for white
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("h2h4");
    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves for black
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("a7a5");
    pawnMoves = m.getPawnMoves(); // moves for white after h2h4

    ASSERT_EQ(pawnMoves.size(), 15);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves for white
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("e2e3");
    pawnMoves = m.getPawnMoves(); // should get the 16 initial pawn moves for black
    ASSERT_EQ(pawnMoves.size(), 16);

    board.makeMove("a7a5");
    pawnMoves = m.getPawnMoves(); // moves for white after h2h4
    ASSERT_EQ(pawnMoves.size(), 15);

    board.makeMove("h2h4");
    pawnMoves = m.getPawnMoves(); // moves for white after h2h4
    ASSERT_EQ(pawnMoves.size(), 15);


}

TEST(MoveGenTestSuite, GetKnightMoves) {
    Board board;
    MoveGen m = MoveGen(&board);
    std::vector<Move> knightMoves;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    knightMoves = m.getKnightMoves(); // should get the 16 initial pawn moves
    ASSERT_EQ(knightMoves.size(), 4);

    ASSERT_EQ(board.setFEN("N7/2q5/4N3/8/8/8/8/7N"), 0);
    knightMoves = m.getKnightMoves(); // should get the 16 initial pawn moves
    ASSERT_EQ(knightMoves.size(), 12);
}

TEST(MoveGenTestSuite, GetBishopMoves) {
    Board board;
    MoveGen m = MoveGen(&board);
    std::vector<Move> bishopMoves;

    ASSERT_EQ(board.setFEN("8/1r6/8/3B4/8/8/8/8 w - - 0 1"), 0);
    bishopMoves = m.getBishopMoves(); // should get the 16 initial pawn moves
    ASSERT_EQ(bishopMoves.size(), 12);
}

TEST(MoveGenTestSuite, GetAllLegalMoves) {
    Board board;
    std::vector<Move> moves;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    ASSERT_EQ(board.setFEN("r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 4"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 29);

    ASSERT_EQ(board.setFEN("8/8/8/8/8/2b5/1B6/K7 w - - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 3);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/7P/8/PPPPPPP1/RNBQKBNR b KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    ASSERT_EQ(board.setFEN("rnbqkbnr/ppppp1pp/8/5p2/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 31);

    ASSERT_EQ(board.setFEN("rnbqkbnr/ppppppp1/8/7p/8/7P/PPPPPPP1/RNBQKBNR w KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 19);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);
    board.makeMove("h2h3");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);
    board.makeMove("h7h5");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 19);
    board.unmakeMove();
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);
    board.unmakeMove();
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.makeMove("g2g4");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.makeMove("g7g5");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.makeMove("f1h3");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.unmakeMove();
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.unmakeMove();
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.unmakeMove();
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.makeMove("g2g4");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.makeMove("h7h5");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 22);

    board.makeMove("g4g5");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 20);

    board.makeMove("f7f5");
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 22);
}

TEST(MoveGenTestSuite, GetAllLegalMovesFrom) {
    Board board;
    std::vector<Move> legalMoves;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    legalMoves = board.movegen->getLegalMoves(); // should get the 20 initial moves
    ASSERT_EQ(legalMoves.size(), 20);

    board.makeMove("d2d3");
    board.makeMove("b7b5");
    board.makeMove("e1d2");
    board.makeMove("b5b4");
    legalMoves = board.movegen->getLegalMoves();
    ASSERT_EQ(legalMoves.size(), 21);

    for(Move m : legalMoves) std::cout << m << std::endl;
}

TEST(MoveGenTestSuite, GetKingCastleMoves) {
    Board board;
    std::vector<Move> kingMoves;

    ASSERT_EQ(board.setFEN("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"), 0);
    kingMoves = board.movegen->getKingMoves();
    ASSERT_EQ(kingMoves.size(), 7);

    ASSERT_EQ(board.setFEN("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1"), 0);
    kingMoves = board.movegen->getKingMoves();
    ASSERT_EQ(kingMoves.size(), 7);

    ASSERT_EQ(board.setFEN("8/8/8/8/8/8/8/R3K2R w KQkq - 0 1"), 0);
    kingMoves = board.movegen->getKingMoves();
    ASSERT_EQ(kingMoves.size(), 7);

    ASSERT_EQ(board.setFEN("r3k2r/8/8/8/8/8/8/8 b KQkq - 0 1"), 0);
    kingMoves = board.movegen->getKingMoves();
    ASSERT_EQ(kingMoves.size(), 7);
}


TEST(MoveGenTestSuite, UnknownEdgeCase) {
    Board board;
    std::vector<Move> moves;

    ASSERT_EQ(board.setFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"), 0);
    moves = board.movegen->getLegalMoves();
    ASSERT_EQ(moves.size(), 44);
}

