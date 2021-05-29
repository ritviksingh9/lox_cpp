#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <map>
#include <memory>

#include "token.hpp"

class Scanner {
private:	
	long unsigned int start_; //points to the first character in the lexeme being parsed
	long unsigned int current_; //points at the character currently being considered
	int line_; //tracks what source line current is on 
	std::string source_;
	//std::vector<Token*> tokens;
	std::vector<std::shared_ptr<TokenBase>> tokens_;
	static const std::map<std::string, TokenType> keywords_;

	void scanToken();
	void identifier();
	void number();
	void string();
	bool match(char expected);
	char peek();
	char peekNext();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	bool isDigit(char c);
	bool isAtEnd();
	char advance();
	void addToken(TokenType type);
	template<typename T>
	void addToken(TokenType type, T literal) {
		std::string lexeme = source_.substr(start_, current_-start_);
		TokenImpl <T>* tok = new TokenImpl <T> (type, lexeme, line_, literal);
		tokens_.push_back(std::shared_ptr<TokenBase>(tok));
	}

	static std::map<std::string, TokenType> initMap();

public:
	Scanner(const std::string& source);
	std::vector<std::shared_ptr<TokenBase>> scanTokens();
};

#endif
