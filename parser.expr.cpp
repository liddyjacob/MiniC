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
   *  Boolean expressions have priority
   *
   *
   */
  if (et == ExprType::compareET){

    // M -> PF M'
    Expr* left = parse_expr(ExprType::assignET);

    //
    // I did not expect this to get so big,
    // I know this is a terrible scheme.
    // Any better ideas are welcome.
    //
    // This also does not fit in multiplication, and will lead to some
    // strange behaviors. !TODO TODO TODO AFRICA TODO TODO TODO!
    //                    |====================================|
    //                   
    //                     * Find a beter scheme for matching!
    //
    //
    // At least I formatted the if statement nicely.
    Token t1, t2, t3, t4, t5, t6;
    if ((((((
              (t1 = match(Token::leq))     )
          ||  (t2 = match(Token::geq))     )
          ||  (t3 = match(Token::eq_eq))   )
          ||  (t4 = match(Token::lt))      )
          ||  (t5 = match(Token::gt))      )
          ||  (t6 = match(Token::bang_eq)) )
    {
    do{

      Expr::Kind k;
      if (t1) k = Expr::le; 
      if (t2) k = Expr::ge;
      if (t3) k = Expr::eq;
      if (t4) k = Expr::lt;
      if (t5) k = Expr::gt; 
      if (t6) k = Expr::neq;

      // Enforce typing rules:
      Expr* right = parse_expr(ExprType::compareET);
      Type* temp = new Type(Type::UNDEFINED);
      e = new BinaryE(k, temp, left, right);


      std::cerr << "L,R = " << left << ", " << right << '\n';
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
    }while ((((((
              (t1 = match(Token::leq))     )
          ||  (t2 = match(Token::geq))     )
          ||  (t3 = match(Token::eq_eq))   )
          ||  (t4 = match(Token::lt))      )
          ||  (t5 = match(Token::gt))      )
          ||  (t6 = match(Token::bang_eq)) );
    } else {
      e = left;
    }
  }

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
    Token t1, t2, t3, t4;
    if   ((( 
              (t1 = match(Token::star)) 
          ||  (t2 = match(Token::slash))   )
          ||  (t3 = match(Token::and_kw))  )
          ||  (t4 = match(Token::modulus)) ) 
    {
    do{

      Expr::Kind k;
      if (t1) k = Expr::mul; 
      if (t2) k = Expr::quo;
      if (t3) k = Expr::andE;
      if (t4) k = Expr::rem;

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
    } while   ((( 
              (t1 = match(Token::star)) 
          ||  (t2 = match(Token::slash))   )
          ||  (t3 = match(Token::and_kw))  )
          ||  (t4 = match(Token::modulus)) ) ;
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

      Value v(std::stoi(t.lexeme));
      e = new IntE(&intT, v);
    
    } else if (Token t = match(Token::true_kw)){
      
      Value v(true);
      e = new BoolE(&boolT, v);
    
    } else if (Token t = match(Token::false_kw)){
      
      Value v(false);
      e = new BoolE(&boolT, v);
    
    } else if (Token t = match(Token::identifier)){
    
      std::string sym = t.lexeme;
      
      // Found an entry!
      if (Decl* d = scopestack.lookup(sym)){

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
    }

    if (Token t = match(Token::lparen)){
      
    }
  }

  return e;
}
  


