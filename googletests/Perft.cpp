#include "gtest/gtest.h"
#include "Board.h"
#include <bitset>

/* For default position depth 5:
 * 6.723s before removing validity checking
 * 4.152s after
 */
TEST(MoveGenTestSuite, PerftDefaultFEN) {
    Board board;
    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    ASSERT_EQ(board.perft(1, 10), 20);
    ASSERT_EQ(board.perft(2, 20), 400);
    ASSERT_EQ(board.perft(3, 30), 8902);
    ASSERT_EQ(board.perft(4, 40), 197281);
//    ASSERT_EQ(board.perft(5, 5), 4865609);
//    ASSERT_EQ(board.perft(6, 6), 119060324);

    ASSERT_EQ(board.setFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "), 0);
    ASSERT_EQ(board.perft(1, 10), 48);
    ASSERT_EQ(board.perft(2, 20), 2039); // missing 46
    ASSERT_EQ(board.perft(3, 30), 97862);
//    ASSERT_EQ(board.perft(4, 4), 4085603);

    ASSERT_EQ(board.setFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"), 0);
    ASSERT_EQ(board.perft(1, 10), 14);
    ASSERT_EQ(board.perft(2, 20), 191);
    ASSERT_EQ(board.perft(3, 30), 2812);
    ASSERT_EQ(board.perft(4, 40), 43238);
    ASSERT_EQ(board.perft(5, 50), 674624);

    ASSERT_EQ(board.setFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"), 0);
    ASSERT_EQ(board.perft(1, 10), 6);
    ASSERT_EQ(board.perft(2, 20), 264);
    ASSERT_EQ(board.perft(3, 30), 9467);
    ASSERT_EQ(board.perft(4, 40), 422333);

    ASSERT_EQ(board.setFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"), 0);
    ASSERT_EQ(board.perft(1, 1), 44);
    ASSERT_EQ(board.perft(2, 20), 1486);
    ASSERT_EQ(board.perft(3, 30), 62379);
//    ASSERT_EQ(board.perft(4, 4), 2103487);

    ASSERT_EQ(board.setFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"), 0);
    ASSERT_EQ(board.perft(1, 10), 46);
    ASSERT_EQ(board.perft(2, 20), 2079);
    ASSERT_EQ(board.perft(3, 30), 89890);
}