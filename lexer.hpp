#pragma once
#include "token.hpp"
#include <unordered_map>

class Lexer{

public:
  Lexer(char const* first, char const* limit)
    : first(first), limit(limit)
  { }

  Lexer(std::string const& str)
    : Lexer(str.data(), str.data() + str.size())
  { }

  Token parse_next();

  int line_number;
  
  Token match(Token::Kind);

  std::unordered_map<std::string, Token::Kind> keywords;

private:

  bool is_eof(char const* ptr) const { return ptr == limit; }
  //char* consume() { first++; return first; }

  char const* first;
  char const* limit;
};

