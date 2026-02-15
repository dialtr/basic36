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
  // Construct empty; type will be kEof.
  Token();

  // Construct with type and value.
  Token(TokenType type, const std::string& value);

  // Return the type.
  TokenType Type() const;

  // Sets an error on the token.
  void SetError(const std::string& msg);

  // Clears error on the token;
  void ClearError();

  // Returns 'true' if the the token has an error.
  bool IsError() const;

  // Returns the error message, if present, or empty string if not.
  const std::string& ErrorMessage() const;

  // Returns the string value of the token.
  const std::string& Value() const;

 private:
  TokenType type_;
  std::string value_;
  bool error_ = false;
  std::string error_message_ = "";
};

// Canonical stream insertion operator.
std::ostream& operator<<(std::ostream& os, const Token& token);

#endif  // TOKEN_H_
