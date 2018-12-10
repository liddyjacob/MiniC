#include "lexer.hpp"
#include "parser.hpp"
#include "expr.hpp"
#include "printer.hpp"
#include <iterator>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::istreambuf_iterator;
using std::string;

int
main(int argc, char* argv[])
{
  ifstream ifs(argv[1]);
  istreambuf_iterator<char> first(ifs);
  istreambuf_iterator<char> limit;
  string input(first, limit);
  
  Lexer l(input);

  Parser p(l);

  Printer printer(std::cout);
  print(printer, p.parse_stmt()); 
  printer.NextLine();

}
