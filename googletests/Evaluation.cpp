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
}
