#pragma once
#include <string>

struct Token;

bool is_keyword(Token);
bool is_logic(Token);

struct Token
{
  
  
  enum Kind{
    bool_kw,
    int_kw,
    float_kw,
    ref_kw,
    fun_kw,
    var_kw,

    if_kw,
    else_kw,
    while_kw,
    
    return_kw,
    continue_kw,
    break_kw,

    and_kw, 
    or_kw,
    not_kw, // End of keywords

    star,
    slash,
    plus,
    minus,
    
    modulus,

    eq,
    eq_eq,
    bang_eq,
    lt,
    leq,
    gt,
    geq, // End of operators

    lbrace,
    rbrace = lbrace + 1, // Useful for generalizing braces and parens.
    
    lparen,
    rparen = lparen + 1, // End of `ENCAPSULATION`

    eof,
    semicolon, // End of `ENDERS`
    

    // Other:
    colon, 
    arrow,
  };

  //static const Kind 
  Token(Kind k, std::string lexeme)
    : kind(k), lexeme(lexeme)
  { }


  explicit operator bool() const { return kind != eof; }
  
  Kind kind;
  std::string lexeme; 
};




