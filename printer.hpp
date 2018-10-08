#pragma once

#include <iostream>
#include <string>
#include <ostream>

using std::ostream;
using std::string;

// This is the printer. 
// There are some rules for the printer.
// 1. Do not print newlines, use NextLine()
// 2. NextLine() will always handle the current number of tabs, 
//    so adjust tabs before using Nextline().
// 3. To remove tabs for the next print, set tabs to 0, then reset after.

struct Printer{
  Printer(ostream& os)
    : os(os), indent(0)
  { }

  void printTabs(){
    if (indent == 0) { return; } 
    for (int i = 0; i <2 * indent; ++i){
      os << " ";
    }
    
    //os << "|-->";
  }

  void NextLine(){
    os << "\n";
    printTabs();
  }
  
  void operator<<(int out){ 
    os << out; 
  }

  void operator<<(const char* out){
    string searchable(out);
    *this << searchable;
  }

  void operator<<(string out){
    for (char& c : out){
      if (c == '\n') { NextLine(); }
      else os << c;
    } 
  }

  void operator<<(bool out){
    if (out == true) { os << "TRUE"; }
    else {os << "FALSE"; }
  }

  void operator<<(float out){
    os << out; 
  }


  ostream& os;
  int indent;
};
