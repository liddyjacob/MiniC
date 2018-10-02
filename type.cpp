
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


