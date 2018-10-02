#include <iostream>
#include "type.hpp"

int main(){
  std::cout << "Hello, \n";

  BoolT* tptr = new BoolT();
  RefT* rptr = new RefT(tptr);
  print(std::cout, tptr);
  print(std::cout, rptr);
  std::cout << " was the result of print\n";

  return 1;
}
