#include "gtest/gtest.h"
#include "Eval.h"
#include "Algorithms.h"

TEST(EvalTestSuite, BasicTestEval) {
    Board b;
    Eval evaluator = Eval(&b);

    ASSERT_EQ(b.setFEN("4k3/1Q4P1/8/2b5/5n2/8/8/4K3 w - - 0 1"), 0);
    ASSERT_EQ(evaluator.evaluate(), 375);

    ASSERT_EQ(b.setFEN("4k3/1Q4P1/8/2b5/5n2/8/2r5/4K3 w - - 0 1"), 0);
    ASSERT_EQ(evaluator.evaluate(), -135);

    ASSERT_EQ(b.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 0);
    ASSERT_EQ(evaluator.evaluate(), 0);
    ASSERT_EQ(b.setFEN("rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 1"), 0);
    ASSERT_EQ(evaluator.evaluate(), 20);

    ASSERT_EQ(b.setFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"), 0);
    ASSERT_EQ(evaluator.evaluate(), 105);
}
