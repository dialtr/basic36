#include <iostream>
#include <sstream>

#include "absl/status/status.h"
#include "absl/status/status_matchers.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "file_stream.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

std::string MakeTestFilePath(const char* relpath) {
  static const char* src_dir = std::getenv("TEST_SRCDIR");
  static const char* workspace = std::getenv("TEST_WORKSPACE");
  std::string fullpath = absl::StrCat(src_dir, "/", workspace, "/", relpath);
  std::cout << fullpath << std::endl;
  return fullpath;
}

TEST(FileStreamTest, OpenNonexistentFile) {
  absl::StatusOr<FileStream*> result = FileStream::Open(".xyzzy");
  EXPECT_THAT(result.status(),
              absl_testing::StatusIs(absl::StatusCode::kNotFound));
}

TEST(FileStreamTest, OpenEmptyFile) {
  auto result =
      FileStream::Open(MakeTestFilePath("test_data/empty.txt").c_str());
  ASSERT_TRUE(result.ok()) << result.status();
  FileStream* stream = result.value();
  EXPECT_THAT(stream->Eof(), true);
  delete stream;
}

TEST(FileStreamTest, LineAndColumn) {
  auto result =
      FileStream::Open(MakeTestFilePath("test_data/line_column.txt").c_str());
  ASSERT_TRUE(result.ok()) << result.status();
  FileStream* stream = result.value();

  // Consume 'a', and expect it on 1,1
  EXPECT_THAT(stream->Line(), 1);
  EXPECT_THAT(stream->Column(), 1);
  char c = stream->Next();  // Consume 'a'
  EXPECT_THAT(c, 'a');

  // Expect the next char position to be 1,2
  EXPECT_THAT(stream->Line(), 1);
  EXPECT_THAT(stream->Column(), 2);
  c = stream->Next();  // Consume '\n';
  EXPECT_THAT(c, '\n');

  // Expect that reading \n updated the line, col appropriately.
  EXPECT_THAT(stream->Line(), 2);
  EXPECT_THAT(stream->Column(), 1);

  // Read the space
  c = stream->Next();
  EXPECT_THAT(c, ' ');

  // Expect 'B' on 2,2
  EXPECT_THAT(stream->Line(), 2);
  EXPECT_THAT(stream->Column(), 2);
  c = stream->Next();
  EXPECT_THAT(c, 'b');

  delete stream;
}

// TEST(FileStreamTest, AssertTrueExample) { EXPECT_TRUE(true); }

// TEST(FileStreamTest, EqualityExample) { ASSERT_EQ(1 + 1, 2); }
