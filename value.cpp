#include "value.hpp"

Printer& operator<<(Printer& p, const Value& v){
  if (v.kind == Value::intV)  { p << v.ival; }
  if (v.kind == Value::boolV) { p << v.bval; }
  if (v.kind == Value::floatV){ p << v.fval; }
}
