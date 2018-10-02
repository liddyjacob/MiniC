
struct Expr{

  virtual Type* check() const = 0;
}

struct Bool_expr : Expr{
  Type* check() const override{
  }
}
