#include <string>
using std::string;

struct Name{
  Name(const char* c_str)
    : str(c_str)
  { }

  Name(string str)
    : str(str)
  { }

  string str;
};
