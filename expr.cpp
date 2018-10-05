#include "expr.hpp"

// Print an expression!
void print(Printer& p, Expr* e){
  
  p.printTabs();
  p << "Expr: ";

  if (e->kind <= Expr::nullEND){
    if ((e->kind == Expr::intL || e->kind == Expr::boolL) || 
        (e->kind == Expr::floatL))
    {
      p << static_cast<LiteralE*>(e)->val;
    }
    if (e->kind == Expr::idL){
      p << "IDLITERAL\n";
    }
    return;
  }

  if (e->kind <= Expr::unEND){
    // TODO Print out details for unary expresisons.
    
  
    p << "unary: \n";
    p.indent += 1;
    print(p, static_cast<UnaryE*>(e)->expr);
    return;
  }


  if (e->kind <= Expr::binEND){
    // TODO Print out details for unary expresisons.
    
  
    p << "binary: \n";
    p.indent += 1;
    print(p, static_cast<BinaryE*>(e)->expr1);
    p << "\n";
    print(p, static_cast<BinaryE*>(e)->expr2);
    return;
  }

}

