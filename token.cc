#include "token.h"

Token::Token() : type_(TokenType::kEof) {}

Token::Token(TokenType type, const std::string& value)
    : type_(type), value_(value) {}

TokenType Token::Type() const { return type_; }

void Token::SetError(const std::string& msg) {
  error_ = true;
  error_message_ = msg;
}

void Token::ClearError() {
  error_ = false;
  error_message_ = "";
}

bool Token::IsError() const { return error_; }

const std::string& Token::ErrorMessage() const { return error_message_; }

const std::string& Token::Value() const { return value_; }

std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << "{ type: ";
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
  os << ", value: '" << token.Value() << "'"
     << ", has_error: " << (token.IsError() ? "true" : "false")
     << ", error_message: '" << token.ErrorMessage() << "' }";

  return os;
}
