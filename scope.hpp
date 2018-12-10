#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cstdlib> // abort
#include "decl.hpp"


// A sligt variant of the teachers implementations.
struct Scope : std::unordered_map<std::string, Decl*>
{
  Decl* lookup(std::string sym) const
  {
    auto iter = find(sym);
    if (iter == end())
      return nullptr;
    return iter->second;
  }

  void declare(Decl* d)
  {
    if (lookup(d->name->str)){
      std::cerr << d->name->str << "Already declared in scope!\n";
      abort();
    }
    emplace(d->name->str, d);
  }
};

struct ScopeStack : std::vector<Scope>
{
  Decl* lookup(std::string sym)
  {
    for (const Scope& s : *this){
      if (Decl* d = s.lookup(sym)){
        return d;
      }
    }
    return nullptr;
  }
};
