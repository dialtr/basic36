#ifndef FILE_STREAM_H_
#define FILE_STREAM_H_

#include <fstream>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "stream_interface.h"

class FileStream : public StreamInterface {
 public:
  static absl::StatusOr<StreamInterface*> Open(const std::string& path);

  ~FileStream() = default;

  FileStream(const FileStream&) = delete;
  FileStream& operator=(const FileStream&) = delete;
  FileStream(FileStream&&) = delete;
  FileStream& operator=(FileStream&&) = delete;

  // StreamInterface
  bool Eof() const override;
  char Next() override;
  char Peek() override;

 private:
  FileStream(std::ifstream&& file);
  std::ifstream file_;
};

#endif  // FILE_STREAM_H_
