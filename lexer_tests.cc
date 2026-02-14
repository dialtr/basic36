#include "absl/status/status.h"
#include "absl/status/status_matchers.h"
#include "absl/status/statusor.h"
#include "file_stream.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lexer.h"
#include "test_utility.h"
#include "token.h"

TEST(LexerTest, Eof) {
  auto result =
      FileStream::Open(MakeTestFilePath("test_data/empty.txt").c_str());
  ASSERT_TRUE(result.ok()) << result.status();
  Lexer lexer(result.value());
  ASSERT_TRUE(lexer.Eof());
  Token token = lexer.Next();
  EXPECT_THAT(token.Type(), TokenType::kEof);
}

// TEST(LexerTest, AssertTrueExample) { EXPECT_TRUE(true); }

// TEST(LexerTest, EqualityExample) { ASSERT_EQ(1 + 1, 2); }
