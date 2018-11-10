#include "expr_conv.hpp"
#include <algorithm>// find

// Int, float, bool
const
std::unordered_set<Type::Kind> SUBGROUP_TYPES 
  = {Type::boolT, Type::intT, Type::floatT};

// Again, order matters with subgroup
// Technically, we would need a 
// graph to support a poset structure 
// of subgroups, but the subgroups 
// we have happen to form a total order.
const
std::vector<Type::Kind> SUBGROUP_ORDER 
  = {Type::boolT, Type::intT, Type::floatT};

// Int, float
const
std::unordered_set<Type::Kind> SUBRING_TYPES
  = {Type::intT, Type::floatT};

const
std::vector<Type::Kind> SUBRING_ORDER 
  = {Type::intT, Type::floatT};



// extern const
// std::unordered_set<Type::Kind> ;

bool is_convertable(std::vector<Expr*> e_vect){
  
  bool all_are_subgroups = true;
  bool all_are_subrings  = true;
  
  for (Expr* e : e_vect){
    
    Type::Kind e_kind = e->t->kind;     
    
    if (SUBGROUP_TYPES.find(e_kind) == SUBGROUP_TYPES.end()){
      all_are_subgroups == false;
    }
    
    if (SUBRING_TYPES.find(e_kind) == SUBRING_TYPES.end()){
      all_are_subrings == false;
    }
  }

  // TODO make this more versitile.
  return (all_are_subgroups || all_are_subrings); 
}

Type::Kind max_kind(Type::Kind t1, Type::Kind t2){
  auto s1 = find(SUBRING_ORDER.begin(), SUBRING_ORDER.end(),t1);
  auto s2 = find(SUBRING_ORDER.begin(), SUBRING_ORDER.end(),t2);
  auto end = SUBRING_ORDER.end();

  if ((s1 != end ) && (s2 != end)){
    return (s1 > s2) ? t1 : t2;
  }
  

  s1 = find(SUBGROUP_ORDER.begin(), SUBGROUP_ORDER.end(),t1);
  s2 = find(SUBGROUP_ORDER.begin(), SUBGROUP_ORDER.end(),t2);
  end = SUBGROUP_ORDER.end();

  if ((s1 != end ) && (s2 != end)){
    return (s1 > s2) ? t1 : t2;
  }

  return Type::UNDEFINED;
}

// boolT < intT < floatT
// funT -> fn_call -> return type
// int -> refT? expr

// TODO deal with function calls.
Type::Kind find_LCM(std::vector<Expr*> e_vect){
  
  Type::Kind max = Type::boolT;

  for (Expr* e : e_vect){
    Type::Kind e_kind = e->t->kind;
    max = max_kind(e_kind, max);
  }

  return max;
}

bool convert(std::vector<Expr*> e_vect){

  if (!is_convertable(e_vect)){ return false; }
  
}
