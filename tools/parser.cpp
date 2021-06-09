#include "parser.hpp"

Parser::Parser(const std::vector<std::shared_ptr<TokenBase>>& sourceTokens) : 
							      tokens_(sourceTokens) {
	current_ = 0;
}

bool Parser::isAtEnd() {return current_ >= tokens_.size();}
bool Parser::check(TokenType type) {
	if(isAtEnd()) return false;
	return tokens_[current_] -> type == type;
}
std::shared_ptr<TokenBase> Parser::advance() {
	if(!isAtEnd())
		current_++;
	return tokens_[current_-1];
}
bool Parser::match(std::vector<TokenType> types) {
	for(auto x: types) {
		if(check(x))
			advance();
			return true; 
	}
	return false;
}

std::shared_ptr<Expr> Parser::primary() {
	if(check(TokenType::FALSE)) {
		advance();
		return std::shared_ptr<Expr>(new Literal <bool> (false));
	}
	else if(check(TokenType::TRUE)) {
		advance();
		return std::shared_ptr<Expr>(new Literal <bool> (true));
	}
	else if(check(TokenType::NIL)) {
		advance();
		return std::shared_ptr<Expr>(new Literal <void*> (NULL));
	}
	else if(check(TokenType::NUMBER)) {
		advance();
		return std::shared_ptr<Expr> 
		(new Literal <double> (tokens_[current_-1] -> literal));
	}
	else if(check(TokenType::STRING)) {
		advance();
		return std::shared_ptr<Expr>
		(new Literal <std::string> (tokens_[current_-1] -> literal));
	}
	else {
		std::shared_ptr<Expr> expr = expression();
		//TODO: ERROR MESSAGE HANDLING!!!
		//consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return std::shared_ptr<Expr>(new Grouping(expr));
	}
}
std::shared_ptr<Expr> Parser::unary() {
	std::vector <TokenType> keyTypes = {TokenType::BANG, TokenType MINUS};

	if(match(keyTypes)) {
		std::shared_ptr<TokenBase> op = tokens_[current_-1];
		std::shared_ptr<Expr> right = unary();
		if(op->type == TokenType::NUMBER) {
			TokenImpl<double> tok = getTok(op);
			return std::shared_ptr<Expr>(new Unary<double>(tok, right));
		}
		else if(op->type == TokenType::STRING) {
			TokenImpl<std::string> tok = getTok(op);
			return std::shared_ptr<Expr>(new Unary<std::string>(tok, right));
		}
		else {
			TokenImpl<void*> tok = getTok(op);
			return std::shared_ptr<Expr>(new Unary<void*>(tok, right));
		}
	}
	return primary();
}
std::shared_ptr<Expr> Parser::factor() {
	std::shared_ptr<Expr> expr = unary();
	std::vector <TokenType> keyTypes = {TokenType::SLASH, TokenType STAR};

	while(match(keyTypes)) {
		std::shared_ptr<TokenBase> op = tokens_[current_-1];
		std::shared_ptr<Expr> right = unary();
		if(op->type == TokenType::NUMBER) {
			TokenImpl<double> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<double>(expr, tok, right));
		}
		else if(op->type == TokenType::STRING) {
			TokenImpl<std::string> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<std::string>(expr, tok, right));
		}
		else {
			TokenImpl<void*> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<void*>(expr, tok, right));
		}
	}
	return expr;
}
std::shared_ptr<Expr> Parser::term() {
	std::shared_ptr<Expr> expr = factor();
	std::vector <TokenType> keyTypes = {TokenType::MINUS, TokenType PLUS};

	while(match(keyTypes)) {
		std::shared_ptr<TokenBase> op = tokens_[current_-1];
		std::shared_ptr<Expr> right = factor();
		if(op->type == TokenType::NUMBER) {
			TokenImpl<double> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<double>(expr, tok, right));
		}
		else if(op->type == TokenType::STRING) {
			TokenImpl<std::string> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<std::string>(expr, tok, right));
		}
		else {
			TokenImpl<void*> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<void*>(expr, tok, right));
		}
	}
	return expr;
}
std::shared_ptr<Expr> Parser::comparison() {
	std::shared_ptr<Expr> expr = term();
	std::vector <TokenType> keyTypes = {TokenType::GREATER, TokenType GREATER_EQUAL, TokenType::LESS, TokenType LESS_EQUAL};

	while(match(keyTypes)) {
		std::shared_ptr<TokenBase> op = tokens_[current_-1];
		std::shared_ptr<Expr> right = term();
		if(op->type == TokenType::NUMBER) {
			TokenImpl<double> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<double>(expr, tok, right));
		}
		else if(op->type == TokenType::STRING) {
			TokenImpl<std::string> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<std::string>(expr, tok, right));
		}
		else {
			TokenImpl<void*> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<void*>(expr, tok, right));
		}
	}
	return expr;
}
std::shared_ptr<Expr> Parser::equality() {
	std::shared_ptr<Expr> expr = comparison();
	std::vector <TokenType> keyTypes = {TokenType::EQUAL, TokenType BANG_EQUAL};

	while(match(keyTypes)) {
		std::shared_ptr<TokenBase> op = tokens_[current_-1];
		std::shared_ptr<Expr> right = comparison();
		if(op->type == TokenType::NUMBER) {
			TokenImpl<double> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<double>(expr, tok, right));
		}
		else if(op->type == TokenType::STRING) {
			TokenImpl<std::string> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<std::string>(expr, tok, right));
		}
		else {
			TokenImpl<void*> tok = getTok(op);
			return std::shared_ptr<Expr>(new Binary<void*>(expr, tok, right));
		}
	}
	return expr;
}
std::shared_ptr<Expr> Parser::expression() { return equality();}

void Parser::synchronize() {
	advance();
	for(; !isAtEnd(); advance()) {
		if(tokens_[current_-1] -> type == TokenType::SEMICOLON) return;

		switch(tokens_[current_] -> type) {
			case TokenType::CLASS:
			case TokenType::FUN:
			case TokenType::VAR:
			case TokenType::FOR:
			case TokenType::IF:
			case TokenType::WHILE:
			case TokenType::PRINT:
			case TokenType::RETURN:
				return;
		}
	}
}
