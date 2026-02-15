#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>

enum class TokenType {
  kEof,
  kLineNumber,
  kNumber,
  kOther,
};

class Token {
 public:
  Token() : type_(TokenType::kEof) {}
  Token(TokenType type, const std::string& value)
      : type_(type), value_(value) {}
  TokenType Type() const { return type_; }

  void SetError(const std::string& msg) {
    error_ = true;
    error_message_ = msg;
  }

  void ClearError() {
    error_ = false;
    error_message_ = "";
  }

  bool IsError() const { return error_; }

  const std::string& ErrorMessage() const { return error_message_; }

  const std::string& Value() const { return value_; }

 private:
  TokenType type_;
  std::string value_;
  bool error_;
  std::string error_message_;
};

std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << "{ ";
  switch (token.Type()) {
    case TokenType::kEof:
      os << "kEof";
      break;
    case TokenType::kLineNumber:
      os << "kLineNumber";
      break;
    case TokenType::kNumber:
      os << "kNumber";
      break;
    case TokenType::kOther:
      os << "kOther";
      break;
  }
  os << ", '" << token.Value() << "' }";
  return os;
}

#endif  // TOKEN_H_
