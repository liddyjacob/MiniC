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
      /*
      if (d->kind == Decl::objectD){
        
        ObjectD* obj = static_cast<ObjectD*>(d);
        
        p << "var ";
        p << obj->name->str << " : ";
        
        print(p, obj->type);
        p << " = ";
        print(p, obj->init);
        p << ";";

      }
      std::cout << "DECL\n";

      if (d->kind == Decl::referenceD){
        ReferenceD* ref = static_cast<ReferenceD*>(d);
        p << "ref ";
        p << ref->name->str << " : ";
        print(p, ref->reftype);
        p << " = ";
        print(p, ref->init);
        p << ";";
      }

      if (d->kind == Decl::functionD){
        
        FunctionD* fun = static_cast<FunctionD*>(d);
        p << "fun ";
        p << fun->name->str << "(";
        
        print(p, fun->params[0]);
        for (int i = 1; i < fun->params.size(); ++i){ 
          p << ", ";
          Decl* param = fun->params[i];
          print(p, param);
        }
        p << " -> ";
        print(p, fun->returntype);
        p << "\n";
        p.indent++;
        print(p, fun->body);
        p.indent--;
      }
      */

    }
    return;
  }

  if (s->kind <= Stmt::unEND){
    if (s->kind == Stmt::whileS){
      p << "WHILE ";
      print(p, static_cast<WhileS*>(s)->cond);
      p << " ";
      print(p, static_cast<WhileS*>(s)->stmt);
    }

    return;
  }

  if (s->kind <= Stmt::binEND){
    if (s->kind == Stmt::ifS){
      IfS* ifs = static_cast<IfS*>(s);
      p << "IF ";
      print(p, ifs->cond);
      p << " ";
      print(p, ifs->stmt1);
      p.NextLine();
      p << "ELSE ";
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
