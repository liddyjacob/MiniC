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


bool is_well_formed(Expr* e);

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
  
  Rules()
    : RST_rules(), RET_rules(), RNV_rules()
  { }


  vector<RST> RST_rules; // {R1 or R2 or R3...}
  //   AND
  vector<RET> RET_rules; // {R1 or R2 or R3...}
  //   AND
  vector<RNV> RNV_rules; // {R1 and R2 and R3...}

  // Adding rules is just combining the sets
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


// Requires listed arguments to be of a specific type.
struct Require_Specific_Type{
  
  Require_Specific_Type(int a, Type::Kind k)
    : arg_vect({a}), kind(k)
  { }

  Require_Specific_Type(std::initializer_list<int> list, Type::Kind k)
    : arg_vect(list), kind(k)
  { }

  vector<int> arg_vect; // Argument number
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

bool pass_rst(Expr* e, RST rst_rule);
bool pass_ret(Expr* e, RET ret_rule);
bool pass_rnv(Expr* e, RNV rnv_rule);

extern const
std::unordered_map<Expr::Kind, Rules, EnumHash> expr_rules;
