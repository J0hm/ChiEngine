#include "gtest/gtest.h"
#include "Search.h"
#include "Algorithms.h"

TEST(SearchTestSuite, BasicSearchTest) {
    Board b;
    Search s = Search(&b);

    ASSERT_EQ(b.setFEN("r6r/p1k2Pb1/1n1p1np1/8/4P3/1p2Q2N/P1P2PPP/5K2 b - - 0 10"), 0);
    s.fixedSearch(5);
    Move best = s.getBestMove();
    std::cout << best << std::endl;
}
