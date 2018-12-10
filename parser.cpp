#include "parser.hpp"
#include <cstdlib>

Parser::Parser(Lexer l)
  : lexer(l), index(0), scopeStack()
{ 
  while (Token t = lexer.lex_next())
    tokens.push_back(t);
}

Token 
Parser::match(Token::Kind kind){
  
  Token& curr = tokens[index];
 
  if (curr.kind == kind){
    index++;
    return curr; 
  }

  return Token(Token::eof, "NoMatch!");
}
Token
Parser::expect(Token::Kind kind)
{
  Token& curr = tokens[index];
  if (curr.kind == kind){
    index++;
    return curr;
  }

  std::cerr << "Syntax error on token < " << curr << " >\n";
  std::cerr << "\t--Expected kind: " << kind << '\n';
  abort();
}

