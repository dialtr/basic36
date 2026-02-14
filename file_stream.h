#ifndef FILE_STREAM_H_
#define FILE_STREAM_H_

#include <fstream>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "stream_interface.h"

class FileStream : public StreamInterface {
 public:
  static absl::StatusOr<FileStream*> Open(const std::string& path);

  ~FileStream() = default;

  FileStream(const FileStream&) = delete;
  FileStream& operator=(const FileStream&) = delete;
  FileStream(FileStream&&) = delete;
  FileStream& operator=(FileStream&&) = delete;

  // StreamInterface
  // Return the line of the next character to be read from the stream.
  int Line() const override;

  // Return the column of the next character to be read from the stream.
  int Column() const override;

  // Return 'true' if the end of stream has been reached.
  bool Eof() const override;

  // Return the next character from the stream, or \0 if Eof has been
  // reached. Advances the stream pointer.
  char Next() override;

  // Peek the next character from the stream, or \0 of Eof has been
  // reached. Does not advance the stream pointer.
  char Peek() override;

 private:
  FileStream(std::ifstream&& file);
  std::ifstream file_;
  int line_ = 1;
  int column_ = 1;
};

#endif  // FILE_STREAM_H_
