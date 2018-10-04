#pragma once
// This is borrowed from Sutton's Approach.
// TODO Make this more fancy.


class Value
{
public:
  explicit Value(int n);
  int get_int();
  double get_float();

private: 
  int val;
};

inline 
Value::Value(int n)
  : val(n)
{ }

inline 
int Value::get_int()
{
  return val;
}

inline
double Value::get_float()
{
  return static_cast<double>(val);
}
