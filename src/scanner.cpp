#include "scanner.hpp"

std::map<std::string, TokenType> Scanner::initMap() {
	std::map<std::string, TokenType> m;

	m["and"] = TokenType::AND;
	m["class"] = TokenType::CLASS;
	m["else"] = TokenType::ELSE;
	m["false"] = TokenType::FALSE;
	m["for"] = TokenType::FOR;
	m["fun"] = TokenType::FUN;
	m["if"] = TokenType::IF;
	m["nil"] = TokenType::NIL;
	m["or"] = TokenType::OR;
	m["print"] = TokenType::PRINT;
	m["return"] = TokenType::RETURN;
	m["super"] = TokenType::SUPER;
	m["this"] = TokenType::THIS;
	m["true"] = TokenType::TRUE;
	m["var"] = TokenType::VAR;
	m["while"] = TokenType::WHILE;
	
	return m;
}

Scanner::Scanner(const std::string& source) : source(source) {}

const std::map<std::string, TokenType> Scanner::keywords = Scanner::initMap();

char Scanner::advance() {
	return 'a';
} 
