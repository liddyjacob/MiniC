#pragma once
#include <string>
#include <cstddef>

#include "value.hpp"
#include "type.hpp"
//#include "value.hpp"
#include "decl.hpp"
#include "printer.hpp"

//struct Value;
struct Decl;
// This is a minimalist expression implementation
// There are some missing safty features, but the
// implementation should be relativly easy to read
// and use
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
    UNDEFINED,
    boolL,
    intL,
    floatL,
    idL, // End of nullary kinds


    addinv,
    mulinv,
    negate, // End of Unary kinds


    assign,
    add,
    sub,
    mul,
    quo,
    rem,
    andE,
    orE,
    lt, 
    le, 
    gt, 
    ge, 
    eq, 
    neq, // End of Binary Kinds
  
    fn_call, // end of K-ary
  };

  // Will be helpful for subcases. i.e, if e.k <= Expr::nulEND
  // then we know e is a nullary expression.
  enum KindArity{
    BEGIN   = 0,
    nullEND = idL,
    unEND   = negate,
    binEND  = neq,
    kEND    = fn_call,
    END     = fn_call,
  };

  virtual Expr* operator[](int i){
      return nullptr;
  }

  virtual Expr* operator[](int i) const{
    return nullptr;
  }

  Expr(Kind k, Type* t);

  //virtual Type* check() = 0;
  //virtual void print(std::ostream& os) const = 0;

  Kind kind;
  Type* t;
};

inline
Expr::Expr(Kind k, Type* t)
  : kind(k), t(t)
{ 
  if ((BEGIN > kind) || (END < kind)){
    throw std::runtime_error ("Invalid Expression");
  }
}

// Currently does nothing: but worth 
// making use of
struct NullaryE : Expr{
};

struct UnaryE : Expr{
  UnaryE(Kind k, Type* t, Expr* e)
    : Expr(k,t), expr(e)
  { }
  
  Expr* operator[](int i) override{
    if (i == 0) return expr;
    return nullptr;
  }
  //Type* check() override;
  Expr* expr;
};

struct BinaryE : Expr{
  BinaryE(Kind k, Type* t, Expr* e1, Expr* e2)
    : Expr(k,t), expr1(e1), expr2(e2)
  { }

  Expr* operator[](int i) override{
    if (i == 0) return expr1;
    if (i == 1) return expr2;
    return nullptr;
  }
  //Type* check() override;
  Expr* expr1;
  Expr* expr2;
};

// Not sure how do deal with funtions yet.
struct KaryE : Expr{

  KaryE(Kind k, Type* t, std::initializer_list<Expr*> list)
    : Expr(k, t)
  { }

};

// Literals are nullary
struct LiteralE : Expr{
  LiteralE(Kind k, Type* t, Value& val);
  Value val;
};

struct BoolE : LiteralE{
  BoolE(Type* t, Value& val)
    : LiteralE(boolL, t, val)
  { }

};

struct IntE : LiteralE{
  IntE(Type* t, Value& val)
    : LiteralE(intL, t, val)
  { }

};


//IDentifyer Expression
struct IDE : Expr
{
  // Construct d:
  IDE(Type* t, Decl* d)
    : Expr(idL, t), decl(d)
  { }

  Decl* decl;
};

void print(Printer& p, Expr* e);
void print_sexpr(Printer& p, Expr* e);

