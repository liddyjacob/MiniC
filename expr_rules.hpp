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
  
  vector<RST> RST_rules;
  vector<RET> RET_rules;
  vector<RNV> RNV_rules;
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
    cerr << "In not_valid\n";
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

const
std::unordered_map<Expr::Kind, Rules, EnumHash> expr_rules 
  {
    
    {Expr::UNDEFINED, Rules({ }, { }, { })},
    {Expr::boolL, Rules({ }, { }, { })},
    {Expr::intL, Rules({ }, { }, { })},
    {Expr::floatL, Rules({ }, { }, { })},
    {Expr::idL, Rules({ }, { }, { })},
    {Expr::addinv, Rules({ }, { }, { })},
    {Expr::mulinv, Rules({ }, { }, { })},
    {Expr::negate, Rules({ }, { }, { })},
    {Expr::assign, Rules({ }, { }, { })},
    {Expr::add, Rules({ }, { }, { })},
    {Expr::sub, Rules({ }, { }, { })},
    {Expr::mul, Rules({ }, { }, { })},
    {Expr::quo, Rules({ }, { }, { })},
    {Expr::rem, Rules({ }, { }, { })},
    {Expr::andE, Rules({ }, { }, { })},
    {Expr::orE, Rules({ }, { }, { })},
    {Expr::lt, Rules({ }, { }, { })},
    {Expr::le, Rules({ }, { }, { })},
    {Expr::gt, Rules({ }, { }, { })},
    {Expr::ge, Rules({ }, { }, { })},
    {Expr::eq, Rules({ }, { }, { })},
    {Expr::neq, Rules({ }, { }, { })},
    {Expr::fn_call, Rules({ }, { }, { })},
  };

//struct 

