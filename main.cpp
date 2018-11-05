#include <iostream>
#include "type.hpp"
#include "value.hpp"
#include "expr.hpp"
#include "printer.hpp"

int main(){
  std::cout << "Hello, \n";

  Printer p(std::cout);

  Type* tptr = new BoolT();
  Type* rptr = new RefT(tptr);
  Type* iptr = new IntT;
  print(p, tptr);
  print(p, rptr);


  //Printer p(std::cout);
  Value v(7);
  Expr* test = new IntE(iptr,v);
  std::cout << " was the result of print\n";
  print(p, test);
  
  return 1;
}
