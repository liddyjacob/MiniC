#pragma once
#include <iostream>
#include <vector>
#include "printer.hpp"

using std::vector;
class Type;
class BoolT;// Booleans
class IntT;//  Integers
class RefT;//  References
class FunT;//  Functions

class Printer;

struct Type
{
  enum Kind{
    UNDEFINED,
    boolT,
    intT,
    floatT,
    funT,
    refT,
  };

  Type(Kind k)
    : kind(k)
  { }

  Kind kind;
};

struct BoolT : Type{
  BoolT()
    : Type(boolT)
  { }
};

struct IntT : Type{
  IntT()
    : Type(intT)
  { }
};

struct FloatT : Type{
  FloatT()
    : Type(floatT)
  { }
};

struct FunT : Type{
  FunT(vector<Type*> in_t, Type* ret_t)
    : Type(funT), vectorT(in_t), returnT(ret_t)
  { }

  vector<Type*> vectorT;
  Type* returnT;
};

struct RefT : Type{
  RefT(Type* t)
    : Type(refT), reftype(t)
  { }

  Type* reftype;
};


