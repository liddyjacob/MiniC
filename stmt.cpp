#include "stmt.hpp"
#include "decl.hpp"

void print(Printer& p, Decl* d);

void print(Printer& p, Stmt* s){

  if (s->kind == Stmt::blockS) { 
    p << "{";
    p.indent += 1;
     
    for (Stmt* sub : static_cast<KaryS*>(s)->stmtvector){
      p.NextLine();
      print(p, sub);
    }
    p.indent -= 1;
    p.NextLine();
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
      //p << "Expression Statement:";
      p.indent+=1;
      print(p, static_cast<ExprS*>(s)->expr);
      p.indent-=1;
      p << ";";
    }

    if (s->kind == Stmt::declS) { 
      
      Decl* d = static_cast<DeclS*>(s)->decl;
      
      print(p, d);
      p << ";";
    }
    return;
  }

  if (s->kind <= Stmt::unEND){
    if (s->kind == Stmt::whileS){
      p << "while ";
      print(p, static_cast<WhileS*>(s)->cond);
      p << " ";
      print(p, static_cast<WhileS*>(s)->stmt);
    }

    return;
  }

  if (s->kind <= Stmt::binEND){
    if (s->kind == Stmt::ifS){
      IfS* ifs = static_cast<IfS*>(s);
      p << "if ";
      print(p, ifs->cond);
      p << " ";
      print(p, ifs->stmt1); 
      p << " else ";
      print(p, ifs->stmt2);

    }
    return;
  }

  if (s->kind == Stmt::blockS){
    BlockS* bks = static_cast<BlockS*>(s);

    p << "{";
    for ( auto s : bks->stmtvector ){
      print(p, s);
      p.NextLine();
    }
    p << "}";

  }
      
  p << "Statement Printer;";
}
