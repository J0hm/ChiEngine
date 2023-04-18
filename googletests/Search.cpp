#include "gtest/gtest.h"
#include "Search.h"
#include "Algorithms.h"

TEST(SearchTestSuite, BasicSearchTest) {
    Board b;
    Search s = Search(&b);

    ASSERT_EQ(b.setFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "), 0);
    s.fixedSearch(5);
    Move best = s.getBestMove();
    std::cout << best << std::endl;
}
