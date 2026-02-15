#include "token.h"

#include <cerrno>
#include <cstdlib>

#include "absl/status/status.h"

Token::Token() : type_(TokenType::kEof) {}

Token::Token(TokenType type, const std::string& value)
    : type_(type), value_(value) {}

TokenType Token::Type() const { return type_; }

absl::StatusOr<double> Token::AsDouble() const {
  // The manual page for strtod says that errno is not modified if the
  // conversion is successful. However we'd like to be able to determine
  // conclusively from the call to strtod() that a problem was encountered
  // by the function (as opposed to the possible outcome that a prior
  // function set errno to something other than success.)
  const int saved_errno = errno;
  errno = 0;
  char* start = const_cast<char*>(value_.c_str());
  char* end = start + value_.size();
  const double result = strtod(start, &end);
  if (errno == ERANGE) {
    return absl::OutOfRangeError("string number was out of range");
  } else if (end == start) {
    return absl::InvalidArgumentError("failed to parse number");
  }
  errno = saved_errno;
  return result;
}

absl::StatusOr<long> Token::AsInteger() const {
  const int saved_errno = errno;
  errno = 0;
  char* start = const_cast<char*>(value_.c_str());
  char* end = start + value_.size();
  const long result = strtol(start, &end, 10);
  if (errno == ERANGE) {
    return absl::OutOfRangeError("string number was out of range");
  } else if (end == start) {
    return absl::InvalidArgumentError("failed to parse number");
  }
  errno = saved_errno;
  return result;
}

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
