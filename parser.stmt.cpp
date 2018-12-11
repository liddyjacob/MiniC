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
      scopestack.push_back(Scope());
    
      std::vector<Stmt*> blks;
      
      while (tokens[index].kind != Token::rbrace) {
        Stmt* s = parse_stmt();
        // ^ Moves the index
        blks.push_back(s);
      }

      expect(Token::rbrace);
      scopestack.pop_back();
      return new BlockS(blks);
    }

    case StmtType::ifST:
    {
      expect(Token::lparen);
      Expr* cond = parse_expr();
      expect(Token::rparen);
      expect(Token::lbrace);
      Stmt* ts = parse_stmt(StmtType::blockST);
      expect(Token::else_kw);
      expect(Token::lbrace);
      Stmt* fs = parse_stmt(StmtType::blockST);
      return new IfS(cond, ts, fs);
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
      Decl* d = parse_local_decl();
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


// Parse a decl and deal with its scope.
Decl* 
Parser::parse_local_decl(){
  Token tvar, tref, tfun;
  if ((  (tvar = match(Token::var_kw))
     ||  (tref = match(Token::ref_kw)) )
     ||  (tfun = match(Token::fun_kw)) )
  {
    Decl* d = nullptr;
    Decl::Kind dk;
    Token id_tok = expect(Token::identifier);

    if (scopestack.back().lookup(id_tok.lexeme)){
      std::cerr << "Error: name " << id_tok.lexeme << " already declared in scope!\n";
      abort();
    }
    // Not much common ground for functiond's
    // fun <id>(`decl-list`) -> return_type Blk-stmt;
    if (tfun) 
    {   
      dk = Decl::functionD;
      // TODO this
      return nullptr;
    }

    // Not a function:
    // Common ground here.
    // (var | ref) <id> : <type> = expr;
    expect(Token::colon);
    Token type_tok = expect({Token::int_kw, Token::bool_kw});
    expect(Token::eq);

    Expr* e = parse_expr();
    Type* t = nullptr;
    
    // Find type
    if (type_tok.kind == Token::int_kw) t = &intT;
    if (type_tok.kind == Token::bool_kw) t = &boolT;

    Name* n = new Name(id_tok.lexeme);

    if (tvar){
      d = new ObjectD(n, t, e);
    }
    if (tref){
      d = new ReferenceD(n, t, e);
    }

    scopestack.back()[id_tok.lexeme] = d;
    return d;
  }

  std::cerr << "Declaration expected!\n";
  abort();


}
