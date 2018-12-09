#pragma once
#include "token.hpp"
#include "expr.hpp"
#include "decl.hpp"
#include "type.hpp"
#include "lexer.hpp"

// The parser conducts proofs that 
// a string follows the grammer of 
// the language.
class Parser{
private:

  // These enumerate the recursively defined languages 
  // for expressions , statements, and declarations.
  enum class ExprType{
    assignET,
    additiveET,
    multiplicativeET,
    prefixET,
    postfixET,
    primaryET,
  };

  enum class StmtType{
    emptyST,
    blockST,
    ifST,
    whileST,
    breakST,
    continueST,
    returnST,
    declST,
    exprST,
  };

  enum class DeclType{
    objectDT,
    functionDT,
    programDT,
  };

  
public:
  // Lex first, then parse
  Parser(Lexer lex);

  void parse();

  bool verbose;
  
  Expr* parse_expr(ExprType et = ExprType::assignET);
  Stmt* parse_stmt(StmtType st = StmtType::exprST);
  Decl* parse_decl(DeclType dt = DeclType::programDT);
  Token match(Token::Kind k);

  //Type* parse_type(
private:
  

  Token expect(Token::Kind);
  Lexer lexer;
  std::vector<Token> tokens;
  int index;
};
