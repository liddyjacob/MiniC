#include "parser.hpp"
#include "expr.hpp"
#include "expr_rules.hpp"
#include "expr_conv.hpp"
#include <cstdlib>
#include <string> // std::stoi

Expr* 
Parser::parse_expr(ExprType et){

  Expr* e = nullptr;


  /*
   * Assign >> Add Assign'
   * 
   * Assign' -> '=' assign | NULL
   */
  if (et == ExprType::assignET){

    // add 
    Expr* left = parse_expr(ExprType::additiveET);

    if (match(Token::eq)){
      Expr* right = parse_expr(ExprType::assignET);
      e = new BinaryE(Expr::assign, left->t, left, right);
    } else {
      e = left;
    }

  }  

  if (et == ExprType::additiveET){
    
    // A -> M A'
    Expr* left = parse_expr(ExprType::multiplicativeET);

    // A' -> '-' A' | '+' A' | M | NULL
    Token t1, t2, t3;
    // This is messy, and could be fixed with an action class.
    if ((
          (t1 = match(Token::plus)) 
       || (t2 = match(Token::minus)) )
       || (t3 = match(Token::or_kw)) ){
    
    do{
      Expr::Kind k;
      if (t1) k = Expr::add;
      if (t2) k = Expr::sub;
      if (t3) k = Expr::orE;
      std::cerr << "Add || sub\n";
      
      // Enforce typing rules:
      Expr* right = parse_expr(ExprType::additiveET);
      Type* temp = new Type(Type::UNDEFINED);
      e = new BinaryE(k, temp, left, right);

      // Check what rules e broke.
      Rules broken = broken_rules(e);
      
      // If e broke any rules, create a new e;
      if (!broken.is_empty()){
        std::vector<Expr*> converted = e->children;
        convert(converted, broken);
        delete e;
        e = new BinaryE(k, temp, converted[0], converted[1]);
      }
      
      e->t = left->t; 
      delete temp;
      // Recurse:
      left = e;
    } while ((
          (t1 = match(Token::plus)) 
       || (t2 = match(Token::minus)) )
       || (t3 = match(Token::or_kw)) );
 
    } else {
      e = left;
    }
  }

  if (et == ExprType::multiplicativeET){

    // M -> PF M'
    Expr* left = parse_expr(ExprType::prefixET);

    // M' -> `*` PF | `/` PF | `%` PF |NULL
    Token t1, t2, t3, t4, t5;
    if   (((( (t1 = match(Token::star)) 
          ||  (t2 = match(Token::slash))   )
          ||  (t3 = match(Token::and_kw))  )
          ||  (t4 = match(Token::modulus)) ) 
          ||  (t5 = match(Token::leq))     )
    {
    do{

      Expr::Kind k;
      if (t1) k = Expr::mul; 
      if (t2) k = Expr::quo;
      if (t3) k = Expr::andE;
      if (t4) k = Expr::rem;
      if (t5) k = Expr::le; 

      std::cerr << "Mul || div || mod\n";

      // Enforce typing rules:
      Expr* right = parse_expr(ExprType::multiplicativeET);
      Type* temp = new Type(Type::UNDEFINED);
      e = new BinaryE(k, temp, left, right);

      // Check what rules e broke.
      Rules broken = broken_rules(e);
      
      // If e broke any rules, create a new e;
      if (!broken.is_empty()){
        std::vector<Expr*> converted = e->children;
        convert(converted, broken);
        delete e;
        e = new BinaryE(k, temp, converted[0], converted[1]);
      } 
      
      e->t = left->t; 
      delete temp;
     
      // Recurse
      left = e;
    }while   (((( (t1 = match(Token::star)) 
          || (t2 = match(Token::slash))    )
          || (t3 = match(Token::or_kw))    )
          || (t4 = match(Token::modulus)) )
          || (t5 = match(Token::leq)) );
    } else {
      e = left;
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
    Token t1, t2;
    if ((t1 = match(Token::minus)) || (t2 = match(Token::slash)) ){
      Expr::Kind k;
      if (t1) k = Expr::addinv;
      if (t2) k = Expr::mulinv;
      std::cerr << "negative || recip\n";

      Expr* right = parse_expr(ExprType::prefixET);
      e = new UnaryE(k, right->t, right);

    } else {
      e = parse_expr(ExprType::postfixET);
    }
  } 

  /* 
   * postfix >> primary '(' arguments ')'
   * postfix >> primary
   */
  if (et == ExprType::postfixET){
    e = parse_expr(ExprType::primaryET);
        
    if (match(Token::lparen)){
      //TODO THIS IS BROKEN s
      expect(Token::rparen);
      std::cerr << "WARNING: Postfix `()` not impl. yet\n";
    }
  } 

  if (et == ExprType::primaryET){
    
    if (Token t = match(Token::integer_literal)){
      std::cerr << "integer literal: < " << t << " >\n";
      Value v(std::stoi(t.lexeme));
      e = new IntE(&intT, v);
    }

    if (Token t = match(Token::identifier)){
      std::string sym = t.lexeme;
      
      // Found an entry!
      if (Decl* d = scopeStack.lookup(sym)){

        Type* t = nullptr; 
        if (d->kind == Decl::objectD) 
          { t = static_cast<ObjectD*>(d)->type; }
        if (d->kind == Decl::referenceD) 
          { t = static_cast<ReferenceD*>(d)->reftype; }
        if (d->kind == Decl::functionD) 
          { t = new FunT(static_cast<FunctionD*>(d)->get_return_types(),
                         static_cast<FunctionD*>(d)->returntype);}
        e = new IDE(t, d);
      } else {
        std::cerr << sym << " was not declared in this scope!\n";
        abort();
      }
      std::cerr << "Identifier: < " << t << " >\n";
    }

    if (Token t = match(Token::lparen)){
      
      std::cerr << "Left paren identifier\n";
    }
  }

  return e;
}
  


