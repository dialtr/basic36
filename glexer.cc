#include <cctype>
#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
  LINE_NUMBER,
  KEYWORD,
  IDENTIFIER,
  NUMBER,
  STRING,
  OPERATOR,
  EOF_TOKEN,
  UNKNOWN
};

struct Token {
  TokenType type;
  std::string value;
};

class Lexer {
 public:
  // Assuming Stream is passed by reference
  Lexer(Stream& input) : stream_(input) {}

  Token GetNextToken() {
    SkipWhitespace();

    char current = stream_.Peek();

    if (current == '\0') return {TokenType::EOF_TOKEN, ""};

    // 1. Handle Numbers (Line numbers or numeric literals)
    if (std::isdigit(current)) {
      return ConsumeNumber();
    }

    // 2. Handle Identifiers and Keywords (A, A$, PRINT)
    if (std::isalpha(current)) {
      return ConsumeIdentifierOrKeyword();
    }

    // 3. Handle String Literals ("HELLO")
    if (current == '"') {
      return ConsumeString();
    }

    // 4. Handle Operators (=, <>, <=, >=, +, -, etc.)
    return ConsumeOperator();
  }

 private:
  Stream& stream_;

  void SkipWhitespace() {
    while (std::isspace(stream_.Peek())) {
      stream_.Next();
    }
  }

  Token ConsumeNumber() {
    std::string val;
    while (std::isdigit(stream_.Peek()) || stream_.Peek() == '.') {
      val += stream_.Next();
    }
    return {TokenType::NUMBER, val};
  }

  Token ConsumeIdentifierOrKeyword() {
    std::string val;
    while (std::isalnum(stream_.Peek())) {
      val += stream_.Next();
    }
    // System/36 Specific: String variables end with $
    if (stream_.Peek() == '$') {
      val += stream_.Next();
    }
    // In a real version, you'd check a map here to see if 'val' is a KEYWORD
    return {TokenType::IDENTIFIER, val};
  }

  Token ConsumeString() {
    stream_.Next();  // Consume opening quote
    std::string val;
    while (stream_.Peek() != '"' && stream_.Peek() != '\0') {
      val += stream_.Next();
    }
    stream_.Next();  // Consume closing quote
    return {TokenType::STRING, val};
  }

  Token ConsumeOperator() {
    std::string op;
    char first = stream_.Next();
    op += first;

    // Check for two-character operators: <>, <=, >=
    char second = stream_.Peek();
    if ((first == '<' && (second == '>' || second == '=')) ||
        (first == '>' && second == '=')) {
      op += stream_.Next();
    }

    return {TokenType::OPERATOR, op};
  }
};
