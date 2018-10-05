#pragma once
#include "expr.hpp"

// TODO: Add some safty checks for if the Kind is valid?

struct Stmt
{
  enum Kind
  {
    breakS,
    continueS,
    declS,
    returnS,
    exprS, // End of nullary statements

    whileS, // End of unary statements

    ifS, // Binary State,emt

    blockS, // K-ary Statement
  };

  enum KindArity{
    nulEND = exprS,
    unEND = whileS,
    binEND = ifS,
    karyEND = blockS,
  };

  Stmt(Kind k)
    : kind(k)
  { }

  Kind kind;
};

struct ContinueS : Stmt{
  ContinueS()
    : Stmt(continueS)
  { }
};

// RETURN expr
struct ReturnS : Stmt{
  ReturnS(Expr* e)
    : Stmt(returnS), expr(e)
  { }

  Expr* expr;
};

struct ExprS : Stmt{
  ExprS(Expr* e)
    : Stmt(exprS), expr(e)
  { }

  Expr* expr;
};

// 
struct DeclS : Stmt{
  DeclS(Expr* e)
    : Stmt(declS), expr(e)
  { }

  Expr* expr;
};

struct UnaryS : Stmt{
  UnaryS(Kind k, Stmt* s)
    : Stmt(k), stmt(s)
  { }
  
  Stmt* stmt;
};

// WHILE [cond] stmt
struct WhileS : UnaryS{
  WhileS(Expr* e, Stmt* s)
    : UnaryS(whileS, s), cond(e)
  { }

  Expr* cond;
};


struct BinaryS : Stmt{
  BinaryS(Kind k, Stmt* s1, Stmt* s2)
    : Stmt(k), stmt1(s1), stmt2(s2)
  { }

  Stmt* stmt1;
  Stmt* stmt2;
};


//IF [cond] stmt1 ELSE stmt2
struct IfS : BinaryS{
  IfS(Expr* c, Stmt* s1, Stmt* s2)
    : BinaryS(ifS, s1, s2), cond(c)
  { }

  Expr* cond;
};

void Print(Stmt* s);
