#include "file_stream.h"

#include "absl/status/status.h"

absl::StatusOr<FileStream*> FileStream::Open(const std::string& path) {
  std::ifstream file(path.c_str());
  if (!file.is_open()) {
    return absl::NotFoundError("path not found");
  }
  FileStream* stream = new FileStream(std::move(file));
  // Must Peek() once to set EOF bit iff the file is empty.
  stream->Peek();
  return stream;
}

FileStream::FileStream(std::ifstream&& file) : file_(std::move(file)) {}

bool FileStream::IsOpen() const { return file_.is_open(); }

bool FileStream::Eof() const { return file_.eof(); }

char FileStream::Next() {
  char c = 0;
  if (file_.get(c)) {
    return c;
  }
  return 0;
}

char FileStream::Peek() {
  int next = file_.peek();
  if (next == std::char_traits<char>::eof()) {
    return 0;
  }
  return static_cast<char>(next);
}
