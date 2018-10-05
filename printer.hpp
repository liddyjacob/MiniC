#pragma once

#include <iostream>
#include <string>
#include <ostream>

using std::ostream;
using std::string;

struct Printer{
  Printer(ostream& os)
    : os(os), indent(0)
  { }

  void printTabs(){
    if (indent == 0) { return; } 
    for (int i = 0; i < 2 * indent - 1; ++i){
      os << " ";
    }
    
    os << "|-->";
  }
  
  void operator<<(int out){
    os << out; 
  }

  void operator<<(const char* out){
    os << out;
  }

  void operator<<(string out){
    os << out; 
  }

  void operator<<(bool out){
    os << out; 
  }

  void operator<<(float out){
    os << out; 
  }


  ostream& os;
  int indent;
};
