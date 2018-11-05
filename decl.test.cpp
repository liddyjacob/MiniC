#include "decl.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "value.hpp"
#include "printer.hpp"

int main(){
  Name* x = new Name("x");
  Name* r = new Name("r");
  Name* f = new Name("factorial");
  Type* INT = new IntT();
  Type* INTREF = new RefT(INT);
  Type* BOOL = new BoolT();

  Value four(4);
  Value three(3);
  Value one(1);
  Value zero(0);

  Expr* zero_expr = new IntE(INT, zero);
  Expr* one_expr = new IntE(INT, one);

  Expr* i_expr = new BinaryE(Expr::add,
                             INT,
                             new IntE(INT, four),
                             new IntE(INT, three) );

  Decl* obj = new ObjectD(x, INT, i_expr);
  
  Expr* x_expr = new IDE(INTREF, obj);

  Decl* ref = new ReferenceD(r, INTREF, x_expr);

  //            fun       f  (x: int) -> int  
  //            {
  //              if x <= 0:
  //                return 1;
  //              else    
  //                return f(x-1);
  //
  //            }
  Decl* funct = new FunctionD(f, {obj}, INT,
    new BlockS{
      new IfS(new BinaryE(Expr::le,
                          BOOL,
                          x_expr,
                          zero_expr),
              new ReturnS(one_expr),
              new ReturnS(
                new BinaryE(Expr::sub,
                            INT,
                            x_expr,
                            one_expr
                )
              )
          )
    }
  );
  

  Printer p(std::cout);
  print(p, funct);

  return 0;

}


