#include "expr_conv.hpp"
// Int, float, bool
const
std::unordered_set<Type::Kind> group_types({Type::boolT, Type::intT});

// Int, float
const
std::unordered_set<Type::Kind> ring_types({Type::intT, Type::floatT});


// extern const
// std::unordered_set<Type::Kind> ;
bool is_convertable(std::vector<Expr*> e_vect){
}

bool convert(std::vector<Expr*> e_vect){

}
