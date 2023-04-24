#include "gtest/gtest.h"
#include "TTable.h"

TEST(TranspositionTestSuite, BasicTTableTests) {
    TTable table = TTable(4);

    ASSERT_FALSE(table.hasKey(0));

    Transposition t = {true, 15, HASH_EXACT, 6, 20, Move()};
    table.setEntry(15, t);

    ASSERT_TRUE(table.hasKey(15));
    ASSERT_TRUE(table.hasKey(31));
    ASSERT_FALSE(table.getEntry(31).hash == 31);
    ASSERT_EQ(table.getEntry(31).hash, 15);
}