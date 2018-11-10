#pragma once

#include "type.hpp"
#include "expr.hpp"
#include "expr_rules.hpp"
#include <vector>
#include <unordered_set>

namespace std
{
  template<>
  struct hash<Type::Kind>{

    std::size_t operator()(const Type::Kind& k) const{
      return static_cast<std::size_t>(k);
    }

  };
}

// Int, float, bool
extern const
std::unordered_set<Type::Kind> group_types;

// Int, float
extern const
std::unordered_set<Type::Kind> ring_types;

// extern const
// std::unordered_set<Type::Kind> ;
bool is_convertable(std::vector<Expr*> e_vect);

// convert to a supertype
bool convert(std::vector<Expr*> e_vect);

