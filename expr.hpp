#pragma once
#include <string>
#include "type.hpp"
#include "value.hpp"



// This is a D A N G E R O U S approach as
// we are not using very many const and
// private variables. In order to quickly
// complete this project, we use this hack.
// To make up for this, we will add some
// COOL and D A N G E R O U S features.
//
// I would eventualy like to implement an
// unusual data type (eventually). Some
// sort of group theory thing would be
// cool.

using std::string;
struct Expr{
  // Kind of expression.
  enum Kind
  {
    boolL,
    intL,
    idL, // End of nullary kinds


    addinv,
    mulinv,
    negate, // End of Unary kinds

    add,
    sub,
    mul,
    quo,
    rem,
    lt, 
    le, 
    gt, 
    ge, 
    eq, 
    neq, // End of Binary Kinds
  };

  // Will be helpful for subcases. i.e, if e.k <= Expr::nulEND
  // then we know e is a nullary expression.
  enum KindArity{
    nulEND = idL,
    unEND = negate,
    binEND = neq,
  };

  Expr(Kind k, Type* t);

  //virtual Type* check() = 0;
  //virtual void print(std::ostream& os) const = 0;

  Kind kind;
  Type* t;
};

inline
Expr::Expr(Kind k, Type* t)
  : kind(k), t(t)
{ }

// Currently does nothing: but worth 
// making use of
struct NullaryE : Expr{
};

struct UnaryE : Expr{
  UnaryE(Kind k, Type* t, Expr* e)
    : Expr(k,t), expr(e)
  { }

  //Type* check() override;
  Expr* expr;
};

struct BinaryE : Expr{
  BinaryE(Kind k, Type* t, Expr* e1, Expr* e2)
    : Expr(k,t), e1(e1), e2(e2)
  { }

  //Type* check() override;
  Expr* e1;
  Expr* e2;
};

struct LiteralE : Expr{
  LiteralE(Kind k, Type* t, Value& val)
    : Expr(k, t), val(val)
  { }

  Value val;
};

struct BoolE : LiteralE{
  BoolE(Type* t, Value& val)
    : LiteralE(boolL, t, val)
  { }

  //Type* check() override{ return t; }
  int get_value() { return val.get_int(); }
};

struct IntE : LiteralE{
  IntE(Type* t, Value& val)
    : LiteralE(intL, t, val)
  { }

  //Type* check() override{ return t; }
  int get_value() { return val.get_int(); }
};

void print(Expr* e);



// NO IDENTIFYERS YET!
/*
struct IdentifierE : Expr{
  IdentifierE(string s, RefT loc)
    : Expr( name(s), ref(loc)
  { }

  Type* check() override{
    return ref.what_ref_type();
  }

  string name;
  RefT ref;
};*/
