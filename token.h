#ifndef TOKEN_H_
#define TOKEN_H_

enum class TokenType {
  kEof,
  kOther,
};

class Token {
 public:
  Token() : type_(TokenType::kEof) {}
  TokenType Type() const { return type_; }

 private:
  TokenType type_;
};

#endif  // TOKEN_H_
