#include "expr.hpp"

Type* BinaryE::check(){
    if (this->op >= lt){
      return new BoolT();
    }
    std::cerr << "Non-boolean binary expr\n";
}

Type* UnaryE::check(){
  if (op  == mulinv || op == addinv){
    // What happens when the expression is invalid?
    return expr->check();
  }
  if (op == negate) {
    //if (equal(expr->check(), new BoolT())){
    //  std::cerr << "Cannot negate a non-boolean expression!\n";
    //  abort();
    //}
    return new BoolT();
  }

}
