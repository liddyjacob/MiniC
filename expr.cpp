#include "expr.hpp"

// Print an expression!
void print(Printer& p, Expr* e){
  
  if (e->kind <= Expr::nullEND){
    if ((e->kind == Expr::intL || e->kind == Expr::boolL) || 
        (e->kind == Expr::floatL))
    {
      Value v =  static_cast<LiteralE*>(e)->val;
      p << v;
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
        p << "-(";
        break;
      case Expr::mulinv:
        p << "/(";
        break;
      case Expr::negate:
        p << "!(";
        break;
    } 
    print(p, static_cast<UnaryE*>(e)->expr);
    p << ")";
    return;
  }


  if (e->kind <= Expr::binEND){
    // TODO Print out details for unary expresisons.
    
    p << "(";
    int indent = p.indent;
    p.indent = 0;

    print(p, static_cast<BinaryE*>(e)->expr1);
    
    switch (e->kind){
      case Expr::add:
        p << " + ";
        break;
      case Expr::sub:
        p << " - ";
        break;
      case Expr::mul:
        p << " * ";
        break;
      case Expr::quo:
        p << " / ";
        break;
      case Expr::rem:
        p << " % ";
        break;
      case Expr::lt:
        p << " < ";
        break;
      case Expr::le:
        p << " <= ";
        break;
      case Expr::gt:
        p << " > ";
        break;
      case Expr::ge:
        p << " >= ";
        break;
      case Expr::eq:
        p << " == ";
        break;
      case Expr::neq:
        p << " != ";
        break;
    }
    print(p, static_cast<BinaryE*>(e)->expr2);
    p << ")";
    p.indent = indent;
    return;
  }

}

