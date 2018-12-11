#pragma once
#include <string>
#include <vector>

#include "printer.hpp"
#include "stmt.hpp"
#include "name.hpp"
#include "type.hpp"
#include "expr.hpp"


struct Type;
struct Stmt;
struct Expr;

struct Decl{

  enum Kind
  {
    objectD, // var x: t = e
    referenceD, // ref x: t = e 
    functionD, // fun x(d1, d2, ..., ) -> t s 
  };

  Decl(Name* n, Kind k)
    : name(n), kind(k)
  { }

  Name* name;
  Kind kind;
};
// An object looks like this:
// [Type] [Name] = [(optional) Expr]  
struct ObjectD : Decl{

  ObjectD(Name* n, Type* t, Expr* e)
    : Decl(n, objectD), type(t), init(e)
  { }

  Type* type;
  Expr* init;
};

// A reference looks like this:
// [Name] [Type] [ReferenceDecl];
struct ReferenceD : Decl{
  ReferenceD(Name* n, Type* t, Expr* e)
    : Decl(n, referenceD), reftype(t), init(e)
  { }

  Type* reftype;
  Expr* init;
};

// A function looks like:
// [Name][Parameters] -> Output_Type Body
struct FunctionD : Decl{
  FunctionD(Name* n, std::initializer_list<Decl*> parms, Type* t, Stmt* s)
    : Decl(n, functionD), returntype(t), params(parms), body(s)
  { }
  FunctionD(Name* n, std::vector<Decl*> parms, Type* t, Stmt* s)
    : Decl(n, functionD), returntype(t), params(parms), body(s)
  { }

  std::vector<Type*> get_return_types();

  Type* returntype;
  std::vector<Decl*> params;
  Stmt* body;
};


void print(Printer& p, Decl* d);
