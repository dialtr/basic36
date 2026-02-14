#include "test_utility.h"

#include <string>

#include "absl/strings/str_cat.h"

std::string MakeTestFilePath(const char* relpath) {
  static const char* src_dir = std::getenv("TEST_SRCDIR");
  static const char* workspace = std::getenv("TEST_WORKSPACE");
  std::string fullpath = absl::StrCat(src_dir, "/", workspace, "/", relpath);
  return fullpath;
}
