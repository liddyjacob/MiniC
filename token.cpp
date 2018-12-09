#include "token.hpp"
std::ostream& operator<<(std::ostream& os, Token const& tok)
{
  os << "Type: " << tok.kind << " Lex: " << tok.lexeme;
}
