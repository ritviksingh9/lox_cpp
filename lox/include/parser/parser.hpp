#ifndef PARSER_H
#define PARSER_H

#include "types/ast/expr.hpp"
#include "types/ast/stmt.hpp"

class Parser {
private:
	long unsigned int current_;
	std::vector<Token> tokens_;
	bool successState_;
	bool catchError_;

	//utilities
	Token advance();
	bool isAtEnd();
	bool check(TokenType type);
	bool match(const std::vector<TokenType>& types);

	//statement utilities
	std::shared_ptr<Stmt> statement();
	std::shared_ptr<Stmt> printStatement();
	std::shared_ptr<Stmt> expressionStatement();
	std::shared_ptr<Stmt> varDeclaration();
	
	//grammar rules
	std::shared_ptr<Expr> primary();
	std::shared_ptr<Expr> unary();
	std::shared_ptr<Expr> factor();
	std::shared_ptr<Expr> term();
	std::shared_ptr<Expr> comparison();
	std::shared_ptr<Expr> equality();
	std::shared_ptr<Expr> assignment();
	std::shared_ptr<Expr> expression();

	//error handling
	Token consume(TokenType type, const std::string& errorMessage);
	void synchronize();

public:
	Parser(const std::vector<Token>& sourceTokens);
	std::vector<std::shared_ptr<Stmt>> parse();
	bool getSuccess();
};

#endif
