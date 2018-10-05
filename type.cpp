
#include "type.hpp"
#include <iostream>

using std::ostream;


void print(ostream& os, Type* t)
{

  struct V : Visitor
  {

    V(ostream& os) : os(os) { }

    void visit(BoolT* t) override {
      os << "bool";
    }
    void visit(IntT* t) override { 
      os << "int";
    }
    void visit(RefT* t) override {
      os << "ref ";
      print(os, t->what_ref_type());
    } 
    
  ostream& os;
  };

  V vis(os);
  t->accept(vis);
}

bool equal(Type* a, Type* b);

bool equal(BoolT* a, Type* b){
  
  struct V : Visitor
  {
    V(BoolT* t)
      : a(t)
    { }

    void visit(Type* t) override{
      result = false;
    }

    void visit(BoolT* t) override{
      result = true;
    };
    
    BoolT* a;
    bool result;
  };

  V vis(a);
  b->accept(vis);
  return vis.result;
}

bool equal(RefT* a, Type* b){
  struct V : Visitor
  {
    V(RefT* t)
      : a(t)
    { }

    void visit(Type* t) override{
      result = false;
    }

    void visit(RefT* b) override{
      result = equal(a->what_ref_type(), b->what_ref_type());
    }
    
    RefT*  a;
    bool result;
  };

  V vis(a);
  b->accept(vis);
  return vis.result;
}

bool equal(IntT* a, Type* b){
  struct V : Visitor
  {
    V(IntT* t)
      : a(t)
    { }

    void visit(Type* t) override{
      result = false;
    }

    void visit(IntT* t) override{
      result = true;
    }
    
    IntT* a;
    bool result;
  };

  V vis(a);
  b->accept(vis);
  return vis.result;
}

bool 
equal(Type* a, Type* b)
{
  struct V : Visitor
  {
    V(Type* t)
      : b(t)
    { }

    void visit(BoolT* a) override{ 
      result = equal(a,b);
    }

    void visit(IntT* a) override{ 
      result = equal(a,b);
    }

    void visit(RefT* a) override{
      result = equal(a, b);
    }

    Type* b;
    bool result;
  };

  V vis(b);
  a->accept(vis);
  return vis.result;
}
