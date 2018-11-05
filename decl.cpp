#include "decl.hpp"
#include "printer.hpp"

void print(Printer& p, Decl* d){
  
  // var x: t = e
  if (d->kind == Decl::objectD){
    ObjectD* d_o = static_cast<ObjectD*>(d);
    p << "var " << d_o->name->str << " : " 
      << d_o->type << " = " << d_o->init;// << '\n'; 
  } 

  // ref x: t = e 
  if (d->kind == Decl::referenceD){
    ReferenceD* d_r = static_cast<ReferenceD*>(d);
    p << "ref " << d_r->name->str << " : " 
      << d_r->reftype << " = " << d_r->init;// << '\n'; 
  }
    
  // fun x(d1, d2, ..., ) -> t s 
  if (d->kind == Decl::functionD){
    FunctionD* d_f = static_cast<FunctionD*>(d);
    p << "fun " << d_f->name->str << "(";

    for (int i = 0; i < d_f->params.size(); ++i){
      Decl* param = d_f->params[i];
      print(p, param);
      if (i != d_f->params.size() - 1){
        p << ", ";
      }
    }
    p << " )";
    p << " -> " << d_f->returntype; 
      
      // Body of function
      p.indent+=1;
      p.NextLine();
      p << d_f->body;
      p.indent-=1; 
      p.NextLine();
  } 
  
}
