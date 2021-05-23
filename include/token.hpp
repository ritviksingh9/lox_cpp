#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {
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

/*
class Token {
public:
	const TokenType type;
	const std::string lexeme;
	const int line;
	
	Token(TokenType type, const std::string& lexeme, int line) : type(type), lexeme(lexeme), line(line) {}
	
	//Destructor
	~Token() = default;
};*/

class TokenBase{
public:
	const TokenType type;
	const std::string lexeme;
	const int line;

	TokenBase(TokenType type, const std::string&lexeme, int line) : type(type),
									lexeme(lexeme),
									line(line) {}
	virtual ~TokenBase()=default;
};

template <class T>
class TokenImpl: public TokenBase {
public:
	T literal;
	TokenImpl(TokenType type, const std::string& lexeme, int line, T literal) : 
	TokenBase(type, lexeme, line), literal(literal) {}
};

/*
//NOTE: All these classes are just various definitions of the Token base class
//A template was not used because there are only three different types for the literal
//and it makes it easier to use in std::vector
class TokenNum: public Token {
public:
	const double literal;
	TokenNum(TokenType type, const std::string& lexeme, double literal, int line) : Token(type, lexeme, line), literal(literal) {}
};
class TokenStr: public Token {
public:
	const std::string& literal;
	TokenStr(TokenType type, const std::string& lexeme, const std::string& literal, int line) : Token(type, lexeme, line), literal(literal) {}
};
class TokenNull: public Token {
public:
	TokenNull(TokenType type, const std::string& lexeme, int line) : Token(type, lexeme, line) {}
};*/

#endif
