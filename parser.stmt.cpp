#include "parser.hpp"
#include "stmt.hpp"
Stmt* Parser::parse_stmt(){

  if (match(Token::if_kw))
    return parse_stmt(StmtType::ifST);

  if (match(Token::while_kw) )
      return parse_stmt(StmtType::whileST);
  
  if (match(Token::break_kw))
      return parse_stmt(StmtType::breakST);
  
  if (match(Token::continue_kw))
      return parse_stmt(StmtType::continueST);
  
  if (match(Token::return_kw))
      return parse_stmt(StmtType::returnST);
  
  if (match(Token::var_kw))
      return parse_stmt(StmtType::declST);
  
  if (match(Token::ref_kw))
      return parse_stmt(StmtType::declST);
  
  if (match(Token::fun_kw))
      return parse_stmt(StmtType::declST);
  
  if (match(Token::semicolon))
      return parse_stmt(StmtType::emptyST);

  if (match(Token::lbrace) )
      return parse_stmt(StmtType::blockST);
  
  return parse_stmt(StmtType::exprST);
}

Stmt* Parser::parse_stmt(StmtType st){

  switch (st){
    case StmtType::emptyST:
      return new EmptyS();

    case StmtType::blockST:
    {
      std::vector<Stmt*> blks;
      while (tokens[index].kind != Token::rbrace) {
        Stmt* s = parse_stmt();
        //FIXME: ERROR here?
        blks.push_back(s);
        ++index;
      }

      expect(Token::rbrace);
      return new BlockS(blks);
    }

    case StmtType::ifST:
    {
      expect(Token::lparen);
      Expr* cond = parse_expr();
      expect(Token::rparen);
      expect(Token::lbrace);
      Stmt* ts = parse_stmt(StmtType::blockST);
      //expect(Token::else_kw);
      //expect(Token::lbrace);
      //Stmt* fs = parse_stmt(StmtType::blockST);
      //return new IfS(cond, ts, fs);
    }
    case StmtType::whileST:
    {
      expect(Token::lparen);
      Expr* cond = parse_expr();
      expect(Token::rparen);
      expect(Token::lbrace);
      Stmt* body = parse_stmt(StmtType::blockST);
      return new WhileS(cond, body);
    }

    case StmtType::breakST:
      expect(Token::semicolon);
      return new BreakS();
    
    case StmtType::continueST:
      expect(Token::semicolon);
      return new BreakS();

    case StmtType::returnST:
    {
      Expr* rtn = parse_expr();
      expect(Token::semicolon);
      return new ReturnS(rtn);
    }
    case StmtType::declST:
    {
      index--;
      Decl* d = nullptr;//parse_local_declaration();
      return new DeclS(d);
    }

    case StmtType::exprST:
    {
      Expr* e = parse_expr();
      expect(Token::semicolon);
      return new ExprS(e); 
    }
    default:
      std::cerr << "Error parsing statement\n";
      return nullptr;
  }
}
