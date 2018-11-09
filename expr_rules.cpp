#include "expr_rules.hpp"

#include <cstddef>
#include <stdlib.h> // abort
#include <iostream> // cerr/cout

using std::cout;
using std::cerr;

// This function checks if an expression is well formed,
// but does not check if the children are well formed.
bool is_well_formed(Expr* e){

  Rules rules = expr_rules.at(e->kind);
  
  bool found_pass = true;

  for (RST rst_rule : rules.RST_rules){
    if (pass_rst(e, rst_rule)){
      found_pass = true;
      break;
    } else {
      found_pass = false;
    }
  }
  if (! found_pass ) {return false;}

  for (RET ret_rule : rules.RET_rules){
    if (!pass_ret(e, ret_rule)){
      return false;
    }
  }

  for (RNV rnv_rule : rules.RNV_rules){
    if (!pass_rnv(e, rnv_rule)){
      return false;
    }
  }

  return true;  
}
  

bool pass_rst(Expr* e, RST rst_rule){

    for (int arg_i : rst_rule.arg_vect){
      if (! (*e)[arg_i]) {
        cerr << "CRITICAL ERROR: RULE REQUIRES MORE ARGUMENTS\n";
        abort();
      }

      if ((*e)[arg_i]->t->kind != rst_rule.kind){
        return false;
      }
  }

  return true;
}

bool pass_ret(Expr* e, RET ret_rule){

  for (int i = 0; i < ret_rule.arg_vect.size(); ++i){
      
      int j = (i + 1) % (ret_rule.arg_vect.size() - 1); 
      
      int arg_i = ret_rule.arg_vect[i];
      int arg_j = ret_rule.arg_vect[j];
      
      if ( (!(*e)[arg_i]) || (!(*e)[arg_j]) ){  
        cerr << "CRITICAL ERROR: RULE REQUIRES MORE ARGUMENTS\n";
        abort();
      }
      
      if ((*e)[arg_i]->t->kind != (*e)[arg_j]->t->kind){
        return false;
      }
  
  }
  return true;

}

bool pass_rnv(Expr* e, RNV rnv_rule){

  cerr << "pass_rnv not impelented, continuing anyway...\n";
  return true;

}


const Rules RET_0_1 = Rules{{ },{RET({0, 1})},{}}; 
const Rules INT_0_1 = Rules{ {RST({0, 1}, Type::intT)}, { }, { } }; 
const Rules BOOL_0_1 = Rules{ {RST({0, 1}, Type::boolT)}, { }, { } };  

const
std::unordered_map<Expr::Kind, Rules, EnumHash> expr_rules 
  {

    // ST: specific type
    // ET: Equivalent types
    // NV: Not value
    //                      RST  RET  RNV
    {Expr::UNDEFINED, Rules({ }, { }, { })},
    {Expr::boolL,     Rules({ }, { }, { })},
    {Expr::intL,      Rules({ }, { }, { })},
    {Expr::floatL,    Rules({ }, { }, { })},
    {Expr::idL,       Rules({ }, { }, { })}, 
    
    {Expr::addinv,    Rules({ }, { }, { })},
    {Expr::mulinv,    Rules({ }, { }, { })},
    {Expr::negate,    Rules({RST(0, Type::boolT)}, { }, { })},
    {Expr::assign,    RET_0_1}, // argument 0,1 
                                                     // must be same type
    // Must be equal types: floats or ints: TODO fix after floats implemented
    {Expr::add,       INT_0_1},
    {Expr::sub,/*---*/INT_0_1},
    {Expr::mul,       INT_0_1},
    {Expr::quo,/*---*/INT_0_1}, // FIXME Requires nonzero den.
    {Expr::rem,       INT_0_1}, // ints only!

    {Expr::andE,      BOOL_0_1},
    {Expr::orE,       BOOL_0_1},

    {Expr::lt,        INT_0_1},
    {Expr::le,        INT_0_1},
    {Expr::gt,        INT_0_1},
    {Expr::ge,        INT_0_1},

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
    cerr << "is_well formed in expr_rules.cpp not implemented\n"
         << "\tContinuing anyway...\n";
    return true;
  }
}*/
