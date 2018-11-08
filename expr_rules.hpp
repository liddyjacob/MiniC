#pragma once
// This is the set of rules that help define
// the expression language.
//
// Fortunatly most rules are always in the form:
// Argument <argN> must be of type kind<t>
// OR
// Arguments <argN1> and <argN2> are of the
// same type
//
// There are some specific rules. For example.
// /a cannot be defined for a == 0. 
// 
// The rules are to be applied to check if conversion is needed.
// If, after conversion, the rules still fail, then the expression
// is ill formed.

#include "expr.hpp"
#include "type.hpp"
#include <initializer_list>
#include <array>
#include <vector>
#include <unordered_map>
#include <tuple>

using std::tuple;
using std::get;

struct Require_Specific_Type;
struct Require_Equiv_Type;
struct Require_Not_Value;

using RST = Require_Specific_Type;
using RET = Require_Equiv_Type;
using RNV = Require_Not_Value;

using vRST = vector<Require_Specific_Type>; 
using vRET = vector<Require_Equiv_Type>;
using vRNV = vector<Require_Not_Value>;

using iRST = std::initializer_list<Require_Specific_Type>; 
using iRET = std::initializer_list<Require_Equiv_Type>;
using iRNV = std::initializer_list<Require_Not_Value>;

struct Rules{
  Rules(iRST RST_rules, iRET RET_rules, iRNV RNV_rules)
    : RST_rules(RST_rules), RET_rules(RET_rules), RNV_rules(RNV_rules)
  { }

  Rules(vRST RST_rules, vRET RET_rules, vRNV RNV_rules)
    : RST_rules(RST_rules), RET_rules(RET_rules), RNV_rules(RNV_rules)
  { }
  
  vector<RST> RST_rules; // {R1 or R2 or R3...}
  //   AND
  vector<RET> RET_rules; // {R1 or R2 or R3...}
  //   AND
  vector<RNV> RNV_rules; // {R1 and R2 and R3...}

  Rules operator+(Rules left){
  
    vRST newRST = RST_rules;
    newRST.insert(newRST.end(),left.RST_rules.begin(), left.RST_rules.end());

    vRET newRET = RET_rules;
    newRET.insert(newRET.end(),left.RET_rules.begin(), left.RET_rules.end());

    vRNV newRNV = RNV_rules;
    newRNV.insert(newRNV.end(),left.RNV_rules.begin(), left.RNV_rules.end());

    return Rules(newRST, newRET, newRNV);
  }

};

struct Require_Specific_Type{
  
  Require_Specific_Type(int a, Type::Kind k)
    : argN(a), kind(k)
  { }

  int argN; // Argument number
  Type::Kind kind;
};

struct Require_Equiv_Type{

  Require_Equiv_Type(std::initializer_list<int> list)
    : arg_vect(list)
  { }
  
  vector<int> arg_vect;
};

struct Require_Not_Value{

  Require_Not_Value()
  {
    cerr << "In not_value: ERROR: not implemented\n";
  }

};

struct EnumHash
{
      template <typename T>
      std::size_t operator()(T t) const
      {
        return static_cast<std::size_t>(t);
      }
};


const RET_0_1 = Rules{{ },{RET({0, 1})},{}}; 
const INT_0_1 = Rules{ {RST(0, Type::intT), RST(1, Type::intT)}, { }, { } } 
const BOOL_0_1 = Rules{ {RST(0, Type::boolT), RST(1, Type::boolT)}, { }, { } } 

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
    {Expr::negate,    Rules({RST(0, Type::boolT)}, { }, { })}, // Argument
                                                     // one must be bool

    {Expr::assign,    RET_0_1}, // argument 0,1 
                                                     // must be same type
    // Must be equal types: floats or ints: TODO fix after floats implemented
    {Expr::add,       RET_0_1 + INT_0_1},


    {Expr::sub,/*---*/RET_0_1 + INT_0_1},
    {Expr::mul,       RET_0_1 + INT_0_1},
    {Expr::quo,/*---*/RET_0_1 + INT_0_1}, // FIXME Requires nonzero den.
    {Expr::rem,       RET_0_1 + INT_0_1}, // ints only!
    {Expr::andE,      RET_0_1 + BOOL_0_1},
    {Expr::orE,       RET_0_1 + BOOL_0_1},
    {Expr::lt,        RET_0_1 + INT_0_1},
    {Expr::le,        RET_0_1 + INT_0_1},
    {Expr::gt,        RET_0_1 + INT_0_1},
    {Expr::ge,        RET_0_1 + INT_0_1},
    {Expr::eq,        RET_0_1}, // any type
    {Expr::neq,       RET_0_1}, // any type
    {Expr::fn_call, Rules({ }, { }, { })}, // no rules!
  };

//struct 

