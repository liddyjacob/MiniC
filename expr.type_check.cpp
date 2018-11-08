#include <expr.hpp>
#include <expr.cpp>

// Type check a single expression
/*  e : The expression to be checked
 *  bad_path: The expressions leading to the error
 *  bad_path: should be  
 * 
 *
 */ 
void checker(Expr* e, vector<Expr*>& return_path);

vector<Expr*> type_check(Expr* e){

  vector<Expr*>& return_path;
  checker(e, return_path);

  return return_path;
}

Type* checker(Expr* e, vector<Expr*>& return_path){

  if (e->kind <= Expr::nullEND){
    return e->type;
  }
  
  // Unary expressions must have the same type as  but are 
  // 
  if (e->kind <= Expr::unEND){
    
    
    return e-> 
  }

  return 
}
