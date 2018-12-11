#include "keywords.hpp"

const
std::unordered_map<std::string, Token::Kind> keyword_map = 
{
  {"bool", Token::bool_kw},
  {"int", Token::int_kw},
  {"float", Token::float_kw},
  {"ref", Token::ref_kw},
  {"fun", Token::fun_kw},
  {"var", Token::var_kw},

  {"if", Token::if_kw},
  {"else", Token::else_kw},
  {"while", Token::while_kw},

  {"return", Token::return_kw},
  {"continue", Token::continue_kw},
  {"break", Token::break_kw},

  {"true", Token::true_kw},
  {"false", Token::false_kw},

  {"and", Token::and_kw}, 
  {"or", Token::or_kw},
  {"not", Token::not_kw} // End of keywords
  
};
