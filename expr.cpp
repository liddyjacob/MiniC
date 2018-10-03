#include "expr.hpp"

Type* BinaryE::check(){
    if (this->op >= lt){
      return new BoolT();
    }
    std::cerr << "Non-boolean binary expr\n";
  }
