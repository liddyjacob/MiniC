
#include "type.hpp"
#include <iostream>

using std::ostream;


void print(ostream& os, Type* t)
{

  std::cout << "Print test\n";

  struct V : Visitor
  {

    V(ostream& os) : os(os) { }

    void visit(BoolT* t) override {
      os << "bool";
    }
    void visit(IntT* t) override { 
      os << "int";
    }
    
  ostream& os;
  };

  V vis(os);
  t->accept(vis);
}


