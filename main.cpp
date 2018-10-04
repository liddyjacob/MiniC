#include <iostream>
#include "type.hpp"
#include "expr.hpp"
#include "value.hpp"

int main(){
  std::cout << "Hello, \n";

  Type* tptr = new BoolT();
  Type* rptr = new RefT(tptr);
  Type* iptr = new IntT;
  print(std::cout, tptr);
  print(std::cout, rptr);

  Value v(7);
  Expr* test = new IntE(iptr,v);
  std::cout << " was the result of print\n";
  print(test);
  
  return 1;
}
