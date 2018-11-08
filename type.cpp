
#include "type.hpp"
#include <iostream>

using std::ostream;

void print(Printer& os, Type* t)
{
  Type::Kind k = t->kind;
  if (k == Type::boolT) os << "bool";
  if (k == Type::intT)  os << "int";
  if (k == Type::refT)  {
    os << "ref ";
    print(os, static_cast<RefT*>(t)->reftype);
  }
  if (k == Type::funT)  {
    os << "fun("; 
    for (Type* sub_k : static_cast<FunT*>(t)->vectorT){
      print(os, sub_k);
      os << ", ";
    }
    os << ") -> ";
    print(os, static_cast<FunT*>(t)->returnT);
  }
}

bool equal(Type* a, Type* b){
  return (a->kind == b->kind);
}
