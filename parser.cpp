#include "parser.hpp"
#include <cstdlib>

Parser::Parser(Lexer l)
  : lexer(l), index(0), scopestack()
{ 
  while (Token t = lexer.lex_next())
    tokens.push_back(t);
  
  // Global scope:
  scopestack.push_back(Scope());
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

Token 
Parser::expect(std::initializer_list<Token::Kind> list){


  Token& curr = tokens[index];
  for (auto kind : list){
    if (curr.kind == kind){
      index++;
      return curr;
    }
  }

  std::cerr << "Syntax error on token < " << curr << " >\n";
  std::cerr << "\t--Expected one of: ";
  for (auto kind : list){
    std::cerr << kind << "; ";
  }
  std::cerr << '\n';
  abort();


}
