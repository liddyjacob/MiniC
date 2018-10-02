#include <iostream>
#include "type.hpp"

int main(){
  std::cout << "Hello, \n";

  BoolT* tptr = new BoolT();
  print(std::cout, tptr);
  std::cout << " was the result of print\n";

  return 1;
}
