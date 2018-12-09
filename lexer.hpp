#pragma once
#include "token.hpp"
#include <unordered_map>

class Lexer{

public:
  Lexer(char const* first, char const* limit)
    : first(first), limit(limit), line_number(0)
  { }

  Lexer(std::string const& str)
    : Lexer(str.data(), str.data() + str.size())
  { }

  Lexer(const Lexer& lhs)
    : Lexer(lhs.first, lhs.limit)
  { }

  Token lex_next();

  char peek(int n = 0) const;

  int line_number;

  Token match(Token::Kind, int);
  Token match_word();
  Token match_number();
  //std::unordered_map<std::string, Token::Kind> keywords;
  

private:

  bool is_eof() const;
  bool is_eof(const char* ptr) const;

  char const* first;
  char const* limit;
};

