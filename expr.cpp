#include "expr.hpp"
#include "value.hpp"
#include <iostream>

// Print an expression!
void print(Printer& p, Expr* e){
  
  if (e->kind == Expr::UNDEFINED) {p << "<Undefined type!>"; }
  if (e->kind <= Expr::nullEND){
    if ((e->kind == Expr::intL || e->kind == Expr::boolL) || 
        (e->kind == Expr::floatL))
    {
      Value v =  static_cast<LiteralE*>(e)->val;
      p << v;
    
    }
    if (e->kind == Expr::idL){
      p << static_cast<IDE*>(e)->decl->name->str;
    }
    return;
  }

  if (e->kind <= Expr::unEND){
    // TODO Print out details for unary expresisons.
    switch (e->kind){
      case Expr::imp_conv:
        p << "_imp_conv<" << e->t  << ">" << "(";
        break;
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

    print(p, static_cast<UnaryE*>(e)->expr());
    p << ")";
    return;
  }


  if (e->kind <= Expr::binEND){
    // TODO Print out details for unary expresisons.
    
    p << "(";
    int indent = p.indent;
    p.indent = 0;

    print(p, static_cast<BinaryE*>(e)->expr1());
    
    switch (e->kind){
      case Expr::assign:
        p << " = ";
        break;
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
      case Expr::andE:
        p << " and ";
        break;
      case Expr::orE:
        p << " or ";
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
    print(p, static_cast<BinaryE*>(e)->expr2());
    p << ")";
    p.indent = indent;
    return;
  }
  if (e->kind == Expr::fn_call){
    Fn_callE* fn = static_cast<Fn_callE*>(e);
    p << fn->fn_IDE()->decl->name->str;
    p << "(";
    for (int i = 1; i < fn->children.size(); ++i)
    {
      print(p, fn->children[i]);
      if (i + 1 != fn->children.size()){
        p << ", ";
      }
    }
    p << ")";
    return ;
  }
  
}

// Print into an sexpr
void print_sexpr(Printer& p, Expr* e){
  
  if (e->kind <= Expr::nullEND){
    if ((e->kind == Expr::intL || e->kind == Expr::boolL) || 
        (e->kind == Expr::floatL))
    {
      Value v =  static_cast<LiteralE*>(e)->val;
      p << v;
    }
    if (e->kind == Expr::idL){
      p << static_cast<IDE*>(e)->decl->name->str;
    }
    return;
  }

  if (e->kind <= Expr::unEND){
    // TODO Print out details for unary expresisons.
    p << "(";
    switch (e->kind){
      case Expr::addinv:
        p << "-";
        break;
      case Expr::mulinv:
        p << "/";
        break;
      case Expr::negate:
        p << "!";
        break;
    } 
    p << " ";
    print_sexpr(p, static_cast<UnaryE*>(e)->expr());
    p << ")";
    return;
  }


  if (e->kind <= Expr::binEND){
    // TODO Print out details for unary expresisons.
    
    p << "(";


    
    switch (e->kind){
      case Expr::assign:
        p << "=";
        break;
      case Expr::add:
        p << "+";
        break;
      case Expr::sub:
        p << "-";
        break;
      case Expr::mul:
        p << "*";
        break;
      case Expr::quo:
        p << "/";
        break;
      case Expr::rem:
        p << "%";
        break;
      case Expr::andE:
        p << "and";
        break;
      case Expr::orE:
        p << "or";
        break;
      case Expr::lt:
        p << "<";
        break;
      case Expr::le:
        p << "<=";
        break;
      case Expr::gt:
        p << ">";
        break;
      case Expr::ge:
        p << ">=";
        break;
      case Expr::eq:
        p << "==";
        break;
      case Expr::neq:
        p << "!=";
        break;
    }

    p << " ";
    print_sexpr(p, static_cast<BinaryE*>(e)->expr1());
    p << " ";
    print_sexpr(p, static_cast<BinaryE*>(e)->expr2());
    p << ")";
    return;
  }

}

Fn_callE::Fn_callE(IDE* fn, std::vector<Expr*> args)
    : KaryE(fn_call, static_cast<FunctionD*>(fn->decl)->returntype,
            std::vector<Expr*>())
  {

    children.push_back(fn);

    for (Expr* arg : args){
      children.push_back(arg);
    }
  }

