#pragma once
#include <iostream>

class Type;
class BoolT;
class IntT;
class RefT;


class Visitor
{
public:
  virtual void visit(Type* t) { }
  virtual void visit(BoolT* t) { return visit((Type*)t); }
  virtual void visit(IntT* t) { return visit((Type*)t); }
  virtual void visit(RefT* t) { return visit((Type*)t); }
};


struct Type
{
  virtual void accept(Visitor& v) = 0;
};

struct BoolT : public Type{
  void accept(Visitor& v) override{
    return v.visit(this);
  }
};


struct IntT : public Type{
  void accept(Visitor& v) override{
    return v.visit(this);
  }
};

void print(std::ostream& os, Type* t);
