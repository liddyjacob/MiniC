#pragma once

class Type;
class Bool_type;
class Int_type;
class Ref_type;



struct Type
{
  virtual void accept(Visitor& v) = 0;
};

struct BoolT : public Type{
  void accept(Visitor& v) override{
    return v.visit(this);
  }
}

struct IntT : public Type{
  void accept(Visitor& v) override{
    return v.visit(this);
  }
}
