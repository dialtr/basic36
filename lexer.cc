#include "lexer.h"

#include <memory>

#include "stream_interface.h"
#include "token.h"

Lexer::Lexer(std::shared_ptr<StreamInterface> stream) : stream_(stream) {}

bool Lexer::Eof() const { return stream_->Eof(); }

Token Lexer::Next() { return Token(); }
