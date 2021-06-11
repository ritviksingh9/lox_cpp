#ifndef PARSER_H
#define PARSER_H

#include "expr.hpp"

class Parser {
private:
	long unsigned int current_;
	std::vector<Token> tokens_;
	
	//utilities
	Token advance();
	bool isAtEnd();
	bool check(TokenType type);
	bool match(std::vector<TokenType> types);
	
	//grammar rules
	std::shared_ptr<Expr> primary();
	std::shared_ptr<Expr> unary();
	std::shared_ptr<Expr> factor();
	std::shared_ptr<Expr> term();
	std::shared_ptr<Expr> comparison();
	std::shared_ptr<Expr> equality();
	std::shared_ptr<Expr> expression();

	//error handling
//	TokenImpl consume(TokenType type, const std::string& message);
	void synchronize();

public:
	Parser(const std::vector<Token>& sourceTokens);
	std::shared_ptr<Expr> parse();
};

#endif
