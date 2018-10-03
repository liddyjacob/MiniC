#pragma once
#include <string>
#include "type.hpp"

using std::string;

struct Expr{
  virtual Type* check() = 0;
  virtual void print(std::ostream& os) const = 0;
};

// Does this include int literals?
struct NullaryE : Expr{
};

// Or this?
enum UnOp{ addinv, mulinv, negate, lint, lbool};

struct UnaryE : Expr{
};


enum BinOp{add, sub, mul, quo, rem, lt, le, gt, ge, eq, neq}; 

struct BinaryE : Expr{
  BinaryE(Expr* l, BinOp p, Expr* r)
    : left(l), op(p), right(r)
  { }

  Type* check() override; 

private:
  Expr* left;
  BinOp op;
  Expr* right;
};

struct IdentifierE : Expr{
  IdentifierE(string s, RefT loc)
    : name(s), ref(loc)
  { }

  Type* check() override{
    return ref.what_ref_type();
  }

private:
  string name;
  RefT ref;
};

struct BoolE : Expr{
};

struct IntE : Expr{
  Type* check() override{
  }
};

struct OrderE : Expr{
  Type* check() override{
  }
};

struct LogicE : Expr{
  Type* check() override{
  }
};


