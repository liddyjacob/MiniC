#include "keyword.hpp"

const
std::unordered_map<std::string, Token::Name> keyword_map = 
{
  {"bool", bool_kw},
  {"int", int_kw},
  {"float", float_kw},
  {"ref", ref_kw},
  {"fun", fun_kw},
  {"var", var_kw},

  {"if", if_kw},
  {"else", else_kw},
  {"while", while_kw},
  
  {"return", return_kw},
  {"continue", continue_kw},
  {"break", break_kw},
  {"and", and_kw}, 
  {"or", or_kw},
  {"not", not_kw} // End of keywords
};
