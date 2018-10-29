#include <string>
using std::string;

struct Name{
  Name(const char* c_str)
    : str(c_str)
  { }

  string str;
};
