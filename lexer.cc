#include "lexer.h"

#include <cctype>
#include <memory>
#include <string>

#include "stream_interface.h"
#include "token.h"

Lexer::Lexer(std::shared_ptr<StreamInterface> stream) : stream_(stream) {}

bool Lexer::Eof() const { return stream_->Eof(); }

Token Lexer::Next() {
  SkipWhitespace();
  if (stream_->Eof()) {
    return Token();
  }

  // Save coordinate of the start of the next token.
  // const int start_line = stream_->Line();
  // const int start_column = stream_->Column();

  const char c = stream_->Peek();
  if (std::isdigit(c)) {
    return ConsumeNumber();
  } else {
    // For now, all others are kOther
    std::string val;
    val += stream_->Next();
    return {TokenType::kOther, val};
  }

  // TODO(staff): This avoids warnings; remove later when they are used.
  //(void)start_line;
  //(void)start_column;
  // return Token();
}

void Lexer::SkipWhitespace() {
  while (!stream_->Eof()) {
    const char c = stream_->Peek();
    if (!std::isspace(c)) {
      break;
    }
    stream_->Next();
  }
}

Token Lexer::ConsumeNumber() {
  const int column = stream_->Column();

  enum State {
    kReadWhole,
    kReadDecimal,
    kReadExponentSign,
    kReadExponent,
    kError,
    kDone
  };

  State state = kReadWhole;
  std::string value;
  std::string msg;
  bool has_decimal = false;
  int decimal_digits = 0;
  bool has_exponent = false;
  int exponent_digits = 0;

  for (;;) {
    if ((state == kDone) || (state == kError)) {
      break;
    }

    const char peek = stream_->Peek();

    switch (state) {
      case kReadWhole:
        if (std::isdigit(peek)) {
          value += stream_->Next();
        } else if (peek == '.') {
          value += stream_->Next();
          has_decimal = true;
          state = kReadDecimal;
        } else if ((peek == 'e') || (peek == 'E')) {
          value += stream_->Next();
          has_exponent = true;
          state = kReadExponentSign;
        } else {
          state = kDone;
        }

      case kReadDecimal:
        if (std::isdigit(peek)) {
          value += stream_->Next();
          ++decimal_digits;
        } else if ((peek == 'e') || (peek == 'E')) {
          if (decimal_digits > 0) {
            value += stream_->Next();
            has_exponent = true;
            state = kReadExponentSign;
          } else {
            msg = "malformed number: decimal portion expected before 'E'";
            state = kError;
          }
        } else {
          if (decimal_digits > 0) {
            state = kDone;
          } else {
            msg = "malformed number: no digits found after decimal point";
            state = kError;
          }
        }

      case kReadExponentSign:
        if ((peek == '+') || (peek == '-')) {
          value += stream_->Next();
          state = kReadExponent;
        } else if (std::isdigit(peek)) {
          state = kReadExponent;
        } else {
          msg = "malformed number: exponent portion expected after 'E'";
          state = kError;
        }

      case kReadExponent:
        if (std::isdigit(peek)) {
          value += stream_->Next();
          ++exponent_digits;
        } else {
          if (exponent_digits > 0) {
            state = kDone;
          } else {
            msg = "malformed number: expected exponent digits after 'E'";
            state = kError;
          }
        }

      default:
        // Do nothing.
        break;
    }
  }

  TokenType token_type = TokenType::kOther;
  if ((column == 1) && (has_decimal == false) && (has_exponent == false)) {
    token_type = TokenType::kLineNumber;
  } else {
    token_type = TokenType::kNumber;
  }

  Token token(token_type, value);

  if (state == kError) {
    token.SetError(msg);
  }

  return token;
}
