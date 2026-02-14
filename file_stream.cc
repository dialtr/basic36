#include "file_stream.h"

#include <memory>

#include "absl/status/status.h"

absl::StatusOr<std::shared_ptr<FileStream>> FileStream::Open(
    const std::string& path) {
  std::ifstream file(path.c_str());
  if (!file.is_open()) {
    return absl::NotFoundError("path not found");
  }
  auto stream =
      std::make_shared<FileStream>(FileStream::Passkey{}, std::move(file));
  // Must Peek() once to set EOF bit iff the file is empty.
  stream->Peek();
  return stream;
}

FileStream::FileStream(Passkey, std::ifstream&& file)
    : file_(std::move(file)) {}

int FileStream::Line() const { return line_; }

int FileStream::Column() const { return column_; }

bool FileStream::Eof() const { return file_.eof(); }

char FileStream::Next() {
  char c = 0;
  if (!file_.get(c)) {
    return 0;
  }
  switch (c) {
    case '\r':
      column_ = 1;
      break;
    case '\n':
      // For UNIX, we'll assume that newline also resets the "carriage".
      // TODO(staff): Maybe offer an option for handling newline literally.
      ++line_;
      column_ = 1;
      break;
    default:
      // Any other character advances one column.
      ++column_;
      break;
  }
  return c;
}

char FileStream::Peek() {
  int next = file_.peek();
  if (next == std::char_traits<char>::eof()) {
    return 0;
  }
  return static_cast<char>(next);
}
