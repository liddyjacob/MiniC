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


class Rules;
Rules broken_rules(Expr* e);

using std::vector;
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

// This encompasses the set of rules an expression must follow
class Rules{
public:

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
  Rules operator+(Rules const left) const;

  bool is_empty(){
    return  RST_rules.size()
          + RET_rules.size()
          + RNV_rules.size()
          == 
            0;
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

bool pass_rst(vector<Expr*> e_vect, RST rst_rule);
bool pass_ret(vector<Expr*> e_vect, RET ret_rule);
bool pass_rnv(vector<Expr*> e_vect, RNV rnv_rule);

extern const
std::unordered_map<Expr::Kind, Rules, EnumHash> EXPR_RULES;
