#include "expr_rules.hpp"

#include <cstddef>
#include <stdlib.h> // abort
#include <iostream> // cerr/cout

using std::cout;
using std::cerr;
using std::vector;

// This function checks if an expression is well formed,
// but does not check if the children are well formed.
// 
// Returns the broken rules!
Rules broken_rules(Expr* e){

  Rules rules = EXPR_RULES.at(e->kind);
  Rules broken_rules;

  bool found_pass = true;
  for (RST rst_rule : rules.RST_rules){
    if (pass_rst(e->children(), rst_rule)){
      found_pass = true;
      break;
    } else {
      broken_rules = broken_rules + Rules({rst_rule},{ },{ });
      found_pass = false;
    }
  }

  // Just need to pass one of these rules.
  if (found_pass != true){ broken_rules.RST_rules.clear(); }

  for (RET ret_rule : rules.RET_rules){
    if (!pass_ret(e->children(), ret_rule)){
      broken_rules = broken_rules + Rules({ },{ret_rule},{ });
    }
  }

  for (RNV rnv_rule : rules.RNV_rules){
    if (!pass_rnv(e->children(), rnv_rule)){
      broken_rules = broken_rules + Rules({ },{ },{rnv_rule});
    }
  }

  return broken_rules;  
}
  

bool pass_rst(vector<Expr*> e_vect, RST rst_rule){

    for (int arg_i : rst_rule.arg_vect){
      if ( arg_i > e_vect.size()) {
        cerr << "CRITICAL ERROR: RULE REQUIRES MORE ARGUMENTS\n";
        abort();
      }

      if (e_vect[arg_i]->t->kind != rst_rule.kind){
        return false;
      }
  }

  return true;
}

bool pass_ret(vector<Expr*> e_vect, RET ret_rule){

  for (int i = 0; i < ret_rule.arg_vect.size(); ++i){
      
      int j = (i + 1) % (ret_rule.arg_vect.size() - 1); 
      
      int arg_i = ret_rule.arg_vect[i];
      int arg_j = ret_rule.arg_vect[j];
      int size = e_vect.size(); 

      if ( (arg_i >= size) || (arg_j >= size) ){  
        cerr << "CRITICAL ERROR: RULE REQUIRES MORE ARGUMENTS\n";
        abort();
      }
      
      if (e_vect[arg_i]->t->kind != e_vect[arg_j]->t->kind){
        return false;
      }
  
  }
  return true;

}

bool pass_rnv(vector<Expr*> e, RNV rnv_rule){

  cerr << "pass_rnv not impelented, continuing anyway...\n";
  return true;

}


Rules 
Rules::operator+(Rules const left) const{

  vRST newRST = RST_rules;
  newRST.insert(newRST.end(),left.RST_rules.begin(), left.RST_rules.end());

  vRET newRET = RET_rules;
  newRET.insert(newRET.end(),left.RET_rules.begin(), left.RET_rules.end());

  vRNV newRNV = RNV_rules;
  newRNV.insert(newRNV.end(),left.RNV_rules.begin(), left.RNV_rules.end());

  return Rules(newRST, newRET, newRNV);
}



const Rules INT_0 = Rules{ {RST({0}, Type::intT)}, { }, { } }; 
const Rules FLOAT_0 = Rules{ {RST({0}, Type::floatT)}, { }, { } };
const Rules INT_0_1 = Rules{ {RST({0, 1}, Type::intT)}, { }, { } }; 
const Rules BOOL_0_1 = Rules{ {RST({0, 1}, Type::boolT)}, { }, { } };  
const Rules FLOAT_0_1 = Rules{ {RST({0, 1}, Type::floatT)}, { }, { } };

const Rules RET_0_1 = Rules{{ },{RET({0, 1})},{}}; 

// Require nonzero value
// const Rules NONZERO = Rules{ { }, { }, {RNV(Value_type(Value_type::zero))}};

const Rules NO_RULES = Rules({ }, { }, { });

const
std::unordered_map<Expr::Kind, Rules, EnumHash> EXPR_RULES 
  {

    // ST: specific type
    // ET: Equivalent types
    // NV: Not value
    //                      
    {Expr::UNDEFINED, NO_RULES},
    {Expr::boolL,     NO_RULES},
    {Expr::intL,      NO_RULES},
    {Expr::floatL,    NO_RULES},
    {Expr::idL,       NO_RULES}, 
    
    {Expr::addinv,    INT_0 + FLOAT_0}, // TODO
    {Expr::mulinv,    INT_0 + FLOAT_0},
    {Expr::negate,    Rules({RST(0, Type::boolT)}, { }, { })},
    {Expr::assign,    RET_0_1}, //FIXME check if left is `assignable`
    
    {Expr::add,       INT_0_1 + FLOAT_0_1},
    {Expr::sub,/*---*/INT_0_1 + FLOAT_0_1},
    {Expr::mul,       INT_0_1 + FLOAT_0_1},
    {Expr::quo,/*---*/INT_0_1 + FLOAT_0_1}, // FIXME Requires nonzero den.
    {Expr::rem,       INT_0_1}, // ints only!

    {Expr::andE,      BOOL_0_1},
    {Expr::orE,       BOOL_0_1},

    {Expr::lt,        INT_0_1 + FLOAT_0_1},
    {Expr::le,        INT_0_1 + FLOAT_0_1},
    {Expr::gt,        INT_0_1 + FLOAT_0_1},
    {Expr::ge,        INT_0_1 + FLOAT_0_1},

    {Expr::eq,        RET_0_1}, // any type
    {Expr::neq,       RET_0_1}, // any type

    {Expr::fn_call, Rules({ }, { }, { })}, // no rules!
  };



/*
  if (e->Kind <= Expr::nullEND){


  }

  if (e->Kind <= Expr::unEND){


  }

  if (e->kind <= Expr::binEND){
    
  }

  if (e->kind <= Expr::kEND){
    cerr << "is_well formed in EXPR_RULES.cpp not implemented\n"
         << "\tContinuing anyway...\n";
    return true;
  }
}*/
