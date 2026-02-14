#ifndef LEXER_H_
#define LEXER_H_

#include <memory>

#include "stream_interface.h"
#include "token.h"

class Lexer {
 public:
  explicit Lexer(std::shared_ptr<StreamInterface> stream);

  // No copy / assign
  Lexer(const Lexer&) = delete;
  Lexer& operator=(const Lexer&) = delete;
  Lexer(Lexer&&) = delete;
  Lexer& operator=(Lexer&&) = delete;

  // Returns true if the underlying stream is at eof.
  bool Eof() const;

  // Return the next token.
  Token Next();

 private:
  std::shared_ptr<StreamInterface> stream_;
};

#endif  // LEXER_H_
