#include "scanner.hpp"

Scanner::Scanner(const std::string& source) : source(source) {
	keywords["and"] = TokenType::AND;
	keywords["class"] = TokenType::CLASS;
	keywords["else"] = TokenType::ELSE;
	keywords["false"] = TokenType::FALSE;
	keywords["for"] = TokenType::FOR;
	keywords["fun"] = TokenType::FUN;
	keywords["if"] = TokenType::IF;
	keywords["nil"] = TokenType::NIL;
	keywords["or"] = TokenType::OR;
	keywords["print"] = TokenType::PRINT;
	keywords["return"] = TokenType::RETURN;
	keywords["super"] = TokenType::SUPER;
	keywords["this"] = TokenType::THIS;
	keywords["true"] = TokenType::TRUE;
	keywords["var"] = TokenType::VAR;
	keywords["while"] = TokenType::WHILE;
}

char Scanner::advance() {
	return 'a';
} 
