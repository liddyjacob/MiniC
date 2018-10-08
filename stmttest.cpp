#include <iostream>

#include "stmt.hpp"
#include "expr.hpp"
#include "type.hpp"

int main(){

  Printer p(std::cout);
  Type* b = new BoolT();
  Type* i = new IntT();

  // bool = true
  Value beqT(true);

  // int  = 3
  Value ieq3(3);
  
  Value ieq4(4);

  Stmt* s1 = new WhileS(new BoolE(b, beqT), new ContinueS());
  Stmt* s2 = new ContinueS();
  Stmt* s3 = new ExprS(new BinaryE(Expr::sub, 
                                   i,
                                   new IntE(i, ieq3), 
                                   new IntE(i, ieq4)
                                   )
                       );
  Stmt* s4 = new IfS(new BinaryE(Expr::le,
                                 b, 
                                 new IntE(i, ieq3),
                                 new IntE(i, ieq4)
                                ),
                     new ReturnS(new IntE(i, ieq3)),
                     new ContinueS()
                     );
  Stmt* s5 = new BlockS({s1, s2, s3, s4});

  print(p, s5);

  return 0;
}
