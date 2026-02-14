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
      FileStream::Open(MakeTestFilePath("test_data/empty_file.txt").c_str());
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_THAT(result.value()->IsOpen(), true);
  EXPECT_THAT(result.value()->Eof(), true);
}

// TEST(FileStreamTest, AssertTrueExample) { EXPECT_TRUE(true); }

// TEST(FileStreamTest, EqualityExample) { ASSERT_EQ(1 + 1, 2); }
