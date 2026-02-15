#include <iostream>

#include "absl/status/status.h"
#include "absl/status/status_matchers.h"
#include "absl/status/statusor.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test_utility.h"
#include "token.h"

TEST(TokenTest, Eof) {
  Token token;
  EXPECT_THAT(token.Type(), TokenType::kEof);
}

TEST(TokenTest, AsInteger_Success) {
  Token token(TokenType::kNumber, "717");
  auto result = token.AsInteger();
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_THAT(result.value(), 717);
}

TEST(TokenTest, AsInteger_Failure) {
  Token token(TokenType::kNumber, "abc");
  auto result = token.AsInteger();
  std::cout << "result: " << result << std::endl;
  ASSERT_FALSE(result.ok()) << result.status();
  //	EXPECT_THAT(result.status(), absl::StatusCode::kOutOfRange);
}

// TEST(LexerTest, AssertTrueExample) { EXPECT_TRUE(true); }

// TEST(LexerTest, EqualityExample) { ASSERT_EQ(1 + 1, 2); }
