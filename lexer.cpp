#include "lexer.hpp"
#include "keywords.hpp"
#include <iostream>
#include <sstream>

bool is_digit(char c) { return std::isdigit(c); }
bool is_nondigit(char c){
    return ((std::isalpha(c)) || (c == '_'));
}

Token
Lexer::lex_next()
{
  while (!is_eof()){
    switch (peek()){
      case ' ':
      case '\t':
        first++;
        continue;

			case '\n':
	      line_number++;  
				first++;
        continue;

      case '*':
        return match(Token::star, 1);
      case '/':
        return match(Token::slash, 1);
      case '+':
        return match(Token::plus, 1);
      case '%':
        return match(Token::modulus, 1);
      case '{':
        return match(Token::lbrace, 1);
      case '}':
        return match(Token::rbrace , 1);
      case '(':
        return match(Token::lparen, 1);
      case ')':
        return match(Token::rparen, 1);
      case ';':
        return match(Token::semicolon, 1);
      case ':': 
        return match(Token::colon, 1);
      case '-':
        if (peek(1) == '>'){
          return match(Token::arrow, 2);
        }
        return match(Token::minus, 1);
      case '=':
				if (peek(1) == '='){
					return match(Token::eq_eq, 2);
				}
				return match(Token::eq, 1);
			case '<':
				if (peek(1) == '='){
					return match(Token::leq, 2);
				}
				return match(Token::lt, 1);
			case '>':
				if (peek(1) == '>'){
					return match(Token::geq, 2);
				}
        return match(Token::gt, 1);

			case '!':
				if (peek(1) == '=')
					return match(Token::bang_eq, 2);

				first++;
				std::cerr << "Line " << line_number << ": " << "Expected '=' after '!'\n";
				continue;

      default: 
        if (is_nondigit(*first))
          return match_word();
        if (is_digit(*first))
          return match_number();

        std::cerr << "Line " << line_number << ": " << "Invalid char\n";
        first++;
        continue;
    }
  }

  return Token(Token::eof, "EOF");
}


Token 
Lexer::match_word(){

  char const* iter = first;
  while (!is_eof(iter) && (is_nondigit(*iter) || is_digit(*iter)))
    ++iter;

  std::string name(first, iter);
  Token::Kind k;
  
  auto lookup = keyword_map.find(name);
  
  if (lookup == keyword_map.end()){
    k = Token::identifier;
  } else {
    k = lookup->second;
  }

  first = iter;
  return Token(k, name);
}


Token 
Lexer::match_number(){
  
  char const* iter = first + 1;
  while (!is_eof(iter) && is_digit(*iter)){
    ++iter;
  }

  std::string name(first, iter);

  first = iter;

  return Token(Token::integer_literal, name);
}  
  
bool 
Lexer::is_eof() const {return first == limit;}

bool 
Lexer::is_eof(const char* ptr) const { return limit == ptr; }

  Token 
Lexer::match(Token::Kind k, int n)
{
  std::string name(first, first + n);
  Token tok = Token(k, name);

  first += n;

  return tok;
}

char Lexer::peek(int n) const
{
  if (limit - first <= n)
    return 0;
  return *(first + n);
}
