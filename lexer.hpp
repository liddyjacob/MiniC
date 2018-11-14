#pragma once
#include <token.hpp>

class Lexer{
public:
  Lexer(char const* first, char const* limit);

  Token parse_next();

  int line_number;

  std::unordered_map<std::string, Token::name keywords>;
private:

  bool is_eof(char const* ptr) const { return ptr == limit; }

  char consume() { first++; return first; }

  Token match(Token:


  char const* first;
  char const* limit;
}
