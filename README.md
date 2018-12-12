# MiniC

A compiler for a class project. 

### Recent updated:
* Global scope does not exist. To make a file, ALWAYS START WITH A BLOCK STATEMENT.

* A Lexer and Parser now exist! 
  * To test the lexer:
``` 
./lexertest tests/<filename>.mc
```
  * To test the parser:
``` 
./parser tests/<filename>.mc
```
*Note: The lexer was not complete before its due date. but is now in working condition.*

* Expression type checking is done in *expr\_typing.cpp*, with 
supplimentary files *expr\_rules.hpp* and *expr\_conv.hpp*

* Conversions are applied in *expr\_conv.hpp*

### Updates to come:

* Code generation


