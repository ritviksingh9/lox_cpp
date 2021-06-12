#include "types/token.hpp"

Token::Token(TokenType type, const std::string& lexeme, int line) : type(type),
								    lexeme(lexeme),
								    line(line) {};

double Token::getNumLiteral() {return std::stod(lexeme);}
std::string Token::getStringLiteral() {return lexeme.substr(1, lexeme.length()-2);}
