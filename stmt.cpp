#include "stmt.hpp"

void print(Printer& p, Stmt* s){

  if (s->kind == Stmt::blockS) { 
    p << "{\n";
    p.indent += 1;
     
    for (Stmt* sub : static_cast<KaryS*>(s)->stmtvector){
      p.printTabs();
      print(p, sub);
      p << "\n";
    }
    p.indent -= 1;
    p << "}";

  return;
  }
  
  /// Printing nullary statements.
  if (s->kind <= Stmt::nulEND){ 
    if (s->kind == Stmt::breakS) { p << "break;"; }
    if (s->kind == Stmt::continueS) { p << "continue;"; }
    if (s->kind == Stmt::returnS) { 
      p << "return "; 
      print(p, static_cast<ReturnS*>(s)->expr);
      p << ";";
    }
    if (s->kind == Stmt::exprS) { 
      p << "Expression Statement:\n";
      p.indent+=1;
      print(p, static_cast<ExprS*>(s)->expr);
      p.indent-=1;
      p << ";";
    }
    if (s->kind == Stmt::declS) { 
      p << "DECLARE (TODO: MAKE PRETTY, ADD DETAILS) "; 
      print(p, static_cast<ReturnS*>(s)->expr);
      p << ";";
    }
    return;
  }

  p << "Statement Printer";
}
