#include "gtest/gtest.h"
#include "lexer.h"  // Even if not used yet, good to verify the include works

// The TEST macro takes: (TestSuiteName, TestName)
TEST(LexerTest, AssertTrueExample) {
  // A simple assertion that always passes
  EXPECT_TRUE(true);
}

TEST(LexerTest, EqualityExample) {
  // Another common basic assertion
  ASSERT_EQ(1 + 1, 2);
}
