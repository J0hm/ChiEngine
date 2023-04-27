#include "gtest/gtest.h"
#include "Search.h"
#include "Algorithms.h"

TEST(SearchTestSuite, BasicSearchTest) {
    Board b;
    Search s = Search(&b);

    //ASSERT_EQ(b.setFEN("r1b4r/1pp2kpp/p1nqnp2/3p4/B2P4/P1Q2N2/1PPB1PPP/R3R1K1 b - - 2 15 "), 0);
    ASSERT_EQ(b.setFEN("8/1p6/p7/P6p/1kp2K1P/8/8/8 b - - 0 1"), 0);
    std::cout << s.negaMaxRoot(10) << std::endl;
    Move m = s.getBestMove();
    std::cout << m << std::endl;
    std::cout << s.visitedNodes << std::endl;

//    ASSERT_EQ(b.setFEN("rn3rk1/pppbqpp1/3p1n2/1N5p/1QB1P3/5P2/PPP3PP/R1B1K2R b KQ - 1 12"), 0);
//    std::cout << s.negaMaxRoot(5) << std::endl;
//    Move m = s.getBestMove();
//    std::cout << m << std::endl;
//    std::cout << s.visitedNodes << std::endl;
}
