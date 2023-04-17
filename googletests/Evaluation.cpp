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

    ASSERT_EQ(b.setFEN("rnbqkbnr/pp1ppppp/2p5/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"), 0);
    ASSERT_EQ(evaluator.evaluate(), 60);

    ASSERT_EQ(b.setFEN("2b5/4Bpbp/7r/p1Np4/2p2P1P/5P1p/1k1P4/1B3R1K w - - 0 13"), 0);
    ASSERT_EQ(evaluator.evaluate(), 20);
}
