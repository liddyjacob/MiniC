#include "expr.hpp"

void print(Expr* e){
  std::cout << "Printed\n";
  
  switch (e->kind){
    case Expr::boolL:
    case Expr::intL:

    case Expr::idL:

    case Expr::addinv:

    case Expr::mulinv:

    case Expr::negate:

    case Expr::add:

    case Expr::sub:

    case Expr::mul:

    case Expr::quo:

    case Expr::rem:

    case Expr::lt:

    case Expr::le:

    case Expr::gt:

    case Expr::ge:

    case Expr::eq:

    case Expr::neq:

      break;
  }
}

