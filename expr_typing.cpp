#include "expr_rules.hpp"
#include "expr_conv.hpp"

// Make an expression well typed.
// Returns false if the expression cannot be made well
// typed.
bool make_well_typed(Expr* e){

  // Make sure all children are well typed
  for (Expr* child : e->children){
    if (!make_well_typed(child)) {return false;}
  }

  // Are any rules broken?
  Rules rules_broken = broken_rules(e);
  if (rules_broken.is_empty()) return true;
  
  // ELSE 
  convert(e->children, rules_broken);
  
  // did this fix the problem? only need to run once
  Rules converted_broken = broken_rules(e);
  if (converted_broken.is_empty()) return true;

  // ELSE 
  
  return false;
}
