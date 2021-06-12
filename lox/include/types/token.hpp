#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
	//single character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	//one or two character tokens
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

	//literals
	IDENTIFIER, STRING, NUMBER,

	//keywords
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	ENDOFFILE
};

class Token {
public:
	const TokenType type;
	const std::string lexeme;
	const int line;

	Token(TokenType type, const std::string& lexeme, int line);

	double getNumLiteral();
	std::string getStringLiteral();
	
};

#endif
