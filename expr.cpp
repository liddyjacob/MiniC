#include "expr.hpp"

BoolT::Type* check() const override{
    if (op >= lt){
      return new BoolT();
    }
    std::cerr << "Non-boolean binary expr\n";
  }
