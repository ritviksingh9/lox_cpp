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

template <class T>
class Token {
public:
	const TokenType type;
	const  std::string lexeme;
	const T literal;	
	const  int line;
	
	Token(TokenType type, std::string lexeme, T literal, int line) : type(type), lexeme(lexeme), literal(literal), line(line) {}
	//currently the toString method hasn't been implemented... need to figure out clean way of printing out enums
};
