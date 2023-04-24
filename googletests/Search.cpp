#include "gtest/gtest.h"
#include "Search.h"
#include "Algorithms.h"

TEST(SearchTestSuite, BasicSearchTest) {
    Board b;
    Search s = Search(&b);

    ASSERT_EQ(b.setFEN("rn3rk1/pppbqpp1/3p1n2/1N5p/1QB1P3/5P2/PPP3PP/R1B1K2R b KQ - 1 12"), 0);
    std::cout << s.negaMaxRoot(5) << std::endl;
    Move m = s.getBestMove();
    std::cout << m << std::endl;
    std::cout << s.visitedNodes << std::endl;
}
