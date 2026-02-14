#include "file_stream.h"
#include "gtest/gtest.h"
#include "lexer.h"
#include "test_utility.h"

TEST(LexerTest, Eof) {
  auto result =
      FileStream::Open(MakeTestFilePath("test_data/empty.txt").c_str());
  ASSERT_TRUE(result.ok()) << result.status();
  Lexer lexer(result.value());
  ASSERT_TRUE(lexer.Eof());
}

// TEST(LexerTest, AssertTrueExample) { EXPECT_TRUE(true); }

// TEST(LexerTest, EqualityExample) { ASSERT_EQ(1 + 1, 2); }
