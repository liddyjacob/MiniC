#pragma once

class Value
{
public:
  explicit Value(int n);
  explicit Value(bool b);
  explicit Value(float f);
  int get_int() const;
  double get_float() const;
  bool get_bool() const;

private:
  //Current Lazy implementation does not use discriminated union (but should)
  int ival;
  float fval;
  bool bval;
};

inline 
Value::Value(int n)
  : ival(n)
{ }

inline 
Value::Value(bool b)
  : bval(b)
{ }

inline 
Value::Value(float f)
  : fval(f)
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


