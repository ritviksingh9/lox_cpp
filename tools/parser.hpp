#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "token.hpp"
#include "expr.hpp"

class Parser {
private:
	long unsigned int current_;
	std::vector<std::shared_ptr<TokenBase>> tokens_;
	
	//utilities
	std::shared_ptr<TokenBase> advance();
	bool isAtEnd();
	bool check(TokenType type);
	bool match(std::vector<TokenType> types);
	template <class T>
	TokenImpl<T> getTok(std::shared_ptr<TokenBase> base) {
		if(base -> type == TokenType::NUMBER) {
			TokenImpl <double> tok(base->type, base->lexeme, base->line, 
					       std::dynamic_pointer_cast<TokenImpl 
					       <double>>(base)->literal);
			return tok;
		}
		if(base -> type == TokenType::STRING) {
			TokenImpl <std::string> tok(base->type, base->lexeme, base->line, 
					       std::dynamic_pointer_cast<TokenImpl 
					       <std::string>>(base)->literal);
			return tok;
		}
		else  {
			TokenImpl <void*> tok(base->type, base->lexeme, base->line, 
					       std::dynamic_pointer_cast<TokenImpl 
					       <void*>>(base)->literal);
			return tok;
		}

	}
	
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
	Parser(const std::vector<std::shared_ptr<TokenBase>>& sourceTokens);
};

#endif
