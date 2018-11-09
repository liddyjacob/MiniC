#include "expr_rules.hpp"
#include "expr.hpp"
#include <iostream>
#include <cassert>

int main(){

  // This seems like the right syntax.
  Type* boolT = new BoolT();
  Type* intT = new IntT();

  Type* intT1 = new IntT();
  Value intV1(7);
  Expr* intexpr1 = new IntE(intT, intV1);

  Type* intT2 = new IntT();
  Value intV2(7);
  Expr* intexpr2 = new IntE(intT, intV2);

  Value trueval(true);
  Value falseval(false);

  Expr* boolexpr1 = new BoolE(boolT, trueval);
  Expr* boolexpr2 = new BoolE(boolT, trueval);
  Expr* boolexpr3 = new BoolE(boolT, falseval);
  
  // I dont understand why I manually enter the type here.
  Expr* leqexpr = new BinaryE(Expr::le, boolT, intexpr1, intexpr2);
  /// This is equivalent to the following code:
  /// 7 <= 7
  
  Expr* eqexpr1 = new BinaryE(Expr::eq, boolT, boolexpr1, boolexpr2);
  Expr* eqexpr2 = new BinaryE(Expr::eq, boolT, boolexpr1, boolexpr3);
  Expr* addexpr = new BinaryE(Expr::add, intT, intexpr1, intexpr2);

  Expr* not_well_formed = new BinaryE(Expr::eq, boolT, boolexpr1, addexpr);

  assert(broken_rules(boolexpr1).is_empty() );
  assert(broken_rules(eqexpr1).is_empty()   );
  assert(broken_rules(addexpr).is_empty()   );
  assert(!broken_rules(not_well_formed).is_empty()     );

  return 0;
}
