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
    

    switch (e->kind){
      case Expr::addinv:
        p << "addinv(-e)";
        break;
      case Expr::mulinv:
        p << "mulinv(/e)";
        break;
      case Expr::negate:
        p << "negate(!e)";
        break;
    }
  
    p << "(unary):\n";
    p.indent += 1;
    print(p, static_cast<UnaryE*>(e)->expr);
    return;
  }


  if (e->kind <= Expr::binEND){
    // TODO Print out details for unary expresisons.
    

    switch (e->kind){
      case Expr::add:
        p << "Add (e1 + e2)";
        break;
      case Expr::sub:
        p << "Sub (e1 + e2)";
        break;
      case Expr::mul:
        p << "Mul (e1 * e2)";
        break;
      case Expr::quo:
        p << "Div (e1 / e2)";
        break;
      case Expr::rem:
        p << "Rem (e1 % 32)";
        break;
      case Expr::lt:
        p << "LT  (e1 < e2)";
        break;
      case Expr::le:
        p << "LE  (e1 <= e2)";
        break;
      case Expr::gt:
        p << "GT  (e1 > e2)";
        break;
      case Expr::ge:
        p << "GE  (e1 >= e2)";
        break;
      case Expr::eq:
        p << "EQ  (e1 == e2)";
        break;
      case Expr::neq:
        p << "NEQ (e1 != e2)";
        break;
    }
    p << "(binary): \n";   
    p.indent += 1;
    print(p, static_cast<BinaryE*>(e)->expr1);
    p << "\n";
    print(p, static_cast<BinaryE*>(e)->expr2);
    return;
  }

}

