
struct Expr{
  virtual Type* check() const = 0;
  virtual void print(std::ostream& os) const = 0;
}

// Does this include int?
struct NullaryE : Expr{
};

// Or this?
enum UnOp{ addinv, mulinv, negate, lint, lbool,  
struct UnaryE : Expr{
};



enum BinOp{ add, sub, mul, div, rem, lt, le, gt, ge}; 
struct BinaryE : Expr{



private:
  Expr* left;
  BinOp op;
  Expr* right;
};


struct BoolE : Expr{
  Type* check() const override{
  }

private:
  Int(


  int val;
}

struct IntE : Expr{
  Type* check() const override{
  }
}

struct OrderE : Expr{
  Type* check() const override{
  }
}

struct LogicE : Expr{
  Type* check() const override{
  }
}


