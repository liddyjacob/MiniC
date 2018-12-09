#include "parser.hpp"
#include "expr.hpp"
#include <cstdlib>

Expr* 
Parser::parse_expr(ExprType et){

  Expr* e = nullptr;

  if (et == ExprType::assignET){

    e = parse_expr(ExprType::additiveET);

    if (match(Token::eq))
      return parse_expr(ExprType::assignET);
  }  

  if (et == ExprType::additiveET){
    
    // A -> M A'
    e = parse_expr(ExprType::multiplicativeET);

    // A' -> '-' M | '+' M | NULL
    while (match(Token::plus) || match(Token::minus)){
      std::cerr << "Add || Sub\n";
      parse_expr(ExprType::multiplicativeET);
    }  

  }  

  if (et == ExprType::multiplicativeET){

    // M -> PF M'
    e = parse_expr(ExprType::prefixET);

    // M' -> `*` PF | `/` PF | `%` PF |NULL
    while ((match(Token::star) || match(Token::slash)) || match(Token::modulus)){
      std::cerr << "Star || Slash || Modulus\n";
      parse_expr(ExprType::prefixET);
    }
  } 

  /*
   * Prefix >> '-' prefix [Negatives]
   *        >> '/' prefix [Reciporicals]
   *        >> postfix
   *
   */
  if (et == ExprType::prefixET){
    
    //=====  TODO: FIXME down below this line FIXME :TODO =====
    if (match(Token::integer_literal)){
      std::cerr << "Integer literal!";
      abort();
    }
      //if (match(Token::minus)) {  
    //}
    std::cerr << "WARNING: Prefix not impl. yet\n";
    //return e;
  } 

  if (et == ExprType::postfixET){
    std::cerr << "WARNING: Postfix not impl. yet\n";
    //return e;
  } 


  return e;
}
  


