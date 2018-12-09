#pragma once
#include <string>
#include <cstddef>
#include <vector>

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


    imp_conv,
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

  Expr(Kind k, Type* t, std::initializer_list<Expr*> list);
  //virtual Type* check() = 0;
  //virtual void print(std::ostream& os) const = 0;

  std::vector<Expr*> children;
  Kind kind;
  Type* t;
};

inline
Expr::Expr(Kind k, Type* t, std::initializer_list<Expr*> list)
  : kind(k), t(t), children(list)
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
    : Expr(k,t, {e})//, children({e})
  { }
  
  //Type* check() override;
  Expr*& expr(){return children[0];};
};

struct BinaryE : Expr{
  BinaryE(Kind k, Type* t, Expr* e1, Expr* e2)
    : Expr(k,t,{e1, e2})
  { }

  //Type* check() override;
  
  Expr*& expr1(){return children[0];};
  Expr*& expr2(){return children[1];}
};

// Not sure how do deal with funtions yet.
struct KaryE : Expr{

  KaryE(Kind k, Type* t, std::initializer_list<Expr*> list)
    : Expr(k, t, list)
  { }

};

struct Fn_callE : KaryE{
  Fn_callE(Type* t, std::initializer_list<Expr*> list)
    : KaryE(fn_call, t, list)
  { }


  Expr*& fn_IDE(){return children[0];}
};

// Literals are nullary
struct LiteralE : Expr{
  LiteralE(Kind k, Type* t, Value& val)
    : Expr(k, t, {}), val(val)
  { }


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

struct ImplicitConvE : UnaryE{
  ImplicitConvE(Type* t, Expr* e)
    : UnaryE(imp_conv, t, e)
  { }

};


//IDentifyer Expression
struct IDE : Expr
{
  // Construct d:
  IDE(Type* t, Decl* d)
    : Expr(idL, t, {}), decl(d)
  { }

  Decl* decl;
};

void print(Printer& p, Expr* e);
void print_sexpr(Printer& p, Expr* e);

