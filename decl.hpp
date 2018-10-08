#include <string>
#include <vector>

#include "printer.hpp"
#include "stmt.hpp"

using Name = std::string;


struct Decl{

  enum Kind
  {
    objectD,
    referenceD,
    functionD,
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
  FunctionD(Name* n, Type* t, std::initializer_list<Decl*> parms,  Stmt* s)
    : Decl(n, functionD), returntype(t), parameters(parms), body(s)
  { }

  Type* returntype;
  std::vector<Decl*> parameters;
  Stmt* body;
};


void print(Printer& p, Decl* d);
