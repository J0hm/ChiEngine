#include "gtest/gtest.h"
#include "Board.h"
#include "Search.h"
#include <chrono>

#if 0
void benchmarkPerftNPS(Board &board, int depth) {
    auto start = std::chrono::high_resolution_clock::now();
    int64 nodes = board.perft(depth, depth + 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    int nps = ((double)nodes / duration.count()) * 1000;
    std::cout << nps << " nodes per second." << std::endl;
}

/*
973121 nodes per second.
1021400 nodes per second.
1103008 nodes per second.
879627 nodes per second.
1051743 nodes per second.
973648 nodes per second.

5904865 nodes per second.
6079766 nodes per second.
7007676 nodes per second.
5588878 nodes per second.
6354945 nodes per second.
6133218 nodes per second.
 */
TEST(BenchmarkSuite, PerftBenchmark) {
    Board board;

    ASSERT_EQ(board.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    benchmarkPerftNPS(board, 5);

    ASSERT_EQ(board.setFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "), 0);
    benchmarkPerftNPS(board, 4);

    ASSERT_EQ(board.setFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"), 0);
    benchmarkPerftNPS(board, 6);

    ASSERT_EQ(board.setFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"), 0);
    benchmarkPerftNPS(board, 5);

    ASSERT_EQ(board.setFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"), 0);
    benchmarkPerftNPS(board, 4);

    ASSERT_EQ(board.setFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"), 0);
    benchmarkPerftNPS(board, 4);
}

void benchmarkSearchNPS(Search &search, int depth) {

    auto start = std::chrono::high_resolution_clock::now();
    search.negaMaxRoot(depth);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    double nodes = search.visitedNodes;
    int nps = (nodes / duration.count()) * 1000;
    std::cout << nps << " nodes per second, took " << duration.count() << "ms at depth " << depth << ". "
              << search.collisions << " collisions, " << nodes << " nodes." << std::endl;
}



/*
108695 nodes per second, took 6455ms.
106586 nodes per second, took 5524ms.
75209 nodes per second, took 2521ms.
51528 nodes per second, took 4545ms.
76163 nodes per second, took 5747ms.

810945 nodes per second, took 5038ms at depth 7. 486 collisions, 4085545 nodes.
216125 nodes per second, took 1080ms at depth 6. 173 collisions, 233415 nodes.
587673 nodes per second, took 13894ms at depth 10. 45450 collisions, 8165136 nodes.
184711 nodes per second, took 1245ms at depth 7. 2318 collisions, 229966 nodes.
160925 nodes per second, took 648ms at depth 6. 1311 collisions, 104280 nodes.
619576 nodes per second, took 8010ms at depth 7. 9230 collisions, 4962807 nodes.
 */
TEST(BenchmarkSuite, SearchNPSBenchmark) {
    Board b;
    Search s = Search(&b);

    std::cout.setf(std::ios::fixed);
    s.resetTable();
    ASSERT_EQ(b.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), 0);
    benchmarkSearchNPS(s, 7);

    s.resetTable();
    ASSERT_EQ(b.setFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "), 0);
    benchmarkSearchNPS(s, 6);

    s.resetTable();
    ASSERT_EQ(b.setFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"), 0);
    benchmarkSearchNPS(s, 10);

    s.resetTable();
    ASSERT_EQ(b.setFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"), 0);
    benchmarkSearchNPS(s, 7);

    s.resetTable();
    ASSERT_EQ(b.setFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"), 0);
    benchmarkSearchNPS(s, 6);

    s.resetTable();
    ASSERT_EQ(b.setFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"), 0);
    benchmarkSearchNPS(s, 7);
}
#endif