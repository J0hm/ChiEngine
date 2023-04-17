#include "gtest/gtest.h"
#include "Search.h"
#include "Algorithms.h"

TEST(SearchTestSuite, BasicSearchTest) {
    Board b;
    Search s = Search(&b);

    ASSERT_EQ(b.setFEN("r3k2r/p1ppqpb1/Bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPB1PPP/R3K2R b KQkq - 0 1"), 0);
    s.fixedSearch(3);
}
