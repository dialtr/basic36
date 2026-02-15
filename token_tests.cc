#include <cmath>
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

TEST(TokenTest, AsInteger_Failure_Invalid) {
  Token token(TokenType::kNumber, "abc");
  auto result = token.AsInteger();
  ASSERT_FALSE(result.ok()) << result.status();
  EXPECT_THAT(result.status().code(), absl::StatusCode::kInvalidArgument);
}

TEST(TokenTest, AsInteger_Failure_Range) {
  Token token(TokenType::kNumber, "9999999999999999999");
  auto result = token.AsInteger();
  ASSERT_FALSE(result.ok()) << result.status();
  EXPECT_THAT(result.status().code(), absl::StatusCode::kOutOfRange);
}

TEST(TokenTest, AsDouble_Success) {
  Token token(TokenType::kNumber, "717.0");
  auto result = token.AsInteger();
  ASSERT_TRUE(result.ok()) << result.status();
  const double expected = 717.0f;
  const double diff = abs(expected - result.value());
  const double kEpsilon = 0.00000001f;
  EXPECT_TRUE(diff < kEpsilon);
}

TEST(TokenTest, AsDouble_Failure_Invalid) {
  Token token(TokenType::kNumber, "abc");
  auto result = token.AsInteger();
  ASSERT_FALSE(result.ok()) << result.status();
  EXPECT_THAT(result.status().code(), absl::StatusCode::kInvalidArgument);
}

TEST(TokenTest, AsDoubler_Failure_Range) {
  Token token(TokenType::kNumber, "1.8e309");
  auto result = token.AsDouble();
  ASSERT_FALSE(result.ok()) << result.status();
  EXPECT_THAT(result.status().code(), absl::StatusCode::kOutOfRange);
}
