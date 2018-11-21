#include "lexer.hpp"

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




  {
    Lexer l(input);
  }

}
