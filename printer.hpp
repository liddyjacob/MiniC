#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include "type.hpp"
#include "expr.hpp"
#include "stmt.hpp"

using std::ostream;
using std::string;
using std::cerr;

struct Type;
struct Expr;
struct Stmt;
struct Printer;
void print(Printer& p,Type* t);
void print(Printer& p, Expr* t);
void print(Printer& p, Stmt* s);

// This is the printer. 
// There are some rules for the printer.
// 1. Do not print newlines, use NextLine()
// 2. NextLine() will always handle the current number of tabs, 
//    so adjust tabs before using Nextline().
// 3. To remove tabs for the next print, set tabs to 0, then reset after.
// 4. You can use the << operator with ints, const char*'s, strings
//    bools, and floats.

struct Printer{
  Printer(ostream& os)
    : os(os), indent(0)
  { }

  void printTabs(){
    if (indent == 0) { return; } 
    for (int i = 0; i < 2 * indent; ++i){
      os << " ";
    }
  }

  void NextLine(){
    os << "\n";
    printTabs();
  }
  
  Printer operator<<(int out){ 
    os << out;
    return *this;
  }

  Printer operator<<(const char* out){
    string searchable(out);
    *this << searchable;
    return *this;
  }

  Printer operator<<(string out){
    for (char& c : out){
      if (c == '\n') { NextLine(); }
      else os << c;
    } 
    return *this;
  }

  Printer operator<<(bool out){
    if (out == true) { os << "TRUE"; }
    else {os << "FALSE"; }
    return *this;
  }

  Printer operator<<(float out){
    os << out; 
    return *this;
  }

  Printer operator<<(Type* t){
    print(*this, t);
    return *this;
  }

  Printer operator<<(Expr* e){
    print(*this, e);
    return *this;
  }

  Printer operator<<(Stmt* s){
    print(*this, s);
    return *this;
  }

  Printer operator<<(Value& v){
    if (v.kind == Value::intV)  { os << v.ival; }
    if (v.kind == Value::boolV) { os << v.bval; }
    if (v.kind == Value::floatV){ os << v.fval; }
    return *this;
  }


    
  ostream& os;
  int indent;
};
