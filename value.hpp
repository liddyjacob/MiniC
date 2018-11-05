#pragma once
//#include "printer.hpp"

class Printer;

class Value
{
public:
  explicit Value(int n);
  explicit Value(bool b);
  explicit Value(float f);

  int get_int() const;
  double get_float() const;
  bool get_bool() const;
  
  enum Kind{
    intV,
    boolV,
    floatV,
  };

  Kind kind;

  int ival;
  float fval;
  bool bval;
};

inline 
Value::Value(int n)
  : ival(n), kind(intV)
{ }

inline 
Value::Value(bool b)
  : bval(b), kind(boolV)
{ }

inline 
Value::Value(float f)
  : fval(f), kind(floatV)
{ }
 
inline 
int Value::get_int() const
{
  return ival;
}

inline
double Value::get_float() const
{
  return fval;
}

inline
bool Value::get_bool() const
{
  return bval;
}


