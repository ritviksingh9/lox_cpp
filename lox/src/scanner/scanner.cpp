#include <cctype>

#include "scanner/scanner.hpp"
#include "error/errorReporter.hpp"

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

Scanner::Scanner(const std::string& source) : source_(source) {
	start_ = 0;
	current_ = 0;
	line_ = 1;
}

const std::map<std::string, TokenType> Scanner::keywords_ = Scanner::initMap();

std::vector<Token> Scanner::scanTokens(bool& successState) {

	while(!isAtEnd()) {
		start_ = current_;
		scanToken(successState);
	}
	tokens_.emplace_back(TokenType::ENDOFFILE, "", line_);
	return tokens_;
}
bool Scanner::isAtEnd() {return current_ >= source_.length();}

void Scanner::scanToken(bool& successState) {
	char c = advance();
	switch(c) {
		case '(': addToken(TokenType::LEFT_PAREN); break;
		case ')': addToken(TokenType::RIGHT_PAREN); break;
		case '{': addToken(TokenType::LEFT_BRACE); break;
		case '}': addToken(TokenType::RIGHT_BRACE); break;
		case ',': addToken(TokenType::COMMA); break;
		case '.': addToken(TokenType::DOT); break;
		case '-': addToken(TokenType::MINUS); break;
		case '+': addToken(TokenType::PLUS); break;
		case ';': addToken(TokenType::SEMICOLON); break;
		case '*': addToken(TokenType::STAR); break; 
		
		case '!': addToken(match('=') ? TokenType::BANG_EQUAL : 
						TokenType::BANG); break;
		case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : 
						TokenType::EQUAL); break;
		case '<': addToken(match('=') ? TokenType::LESS_EQUAL : 
						TokenType::BANG); break;
		case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : 
						TokenType::BANG); break;
		case '/':
			if(match('/')) //ignore comments
				while(!isAtEnd() && peek() != '\n')  advance();
			else addToken(TokenType::SLASH);	
	
		case ' ': break;
		case '\r': break;
		case '\t': break;
		case '\n': line_++; break;
		
		case '"': successState = successState && string(); break;

		default:
			if(isdigit(c)) 
				number();
			else if(isalpha(c))
				identifier();
			else {
				successState = false;
				reportError(line_, "Unexpected character.");
			}
	}
}
char Scanner::advance() {return source_.at(current_++);} 
void Scanner::addToken(TokenType type) {
	std::string lexeme = source_.substr(start_, current_-start_);
	tokens_.emplace_back(type, lexeme, line_);
}
bool Scanner::match(char expected) {
	if(isAtEnd()) return false;
	else if(source_[current_] != expected) return false;

	current_++;
	return true;
}
char Scanner::peek() {return source_.at(current_);}
char Scanner::peekNext() {
	if(current_+1 >= source_.length()) return '\0';
	return source_[current_+1];
}
bool Scanner::string() {
	while(!isAtEnd() && peek() != '"') {
		if(peek() == '\n') 
			line_++;
		advance();
	}
	
	if(isAtEnd()) {
		reportError(line_, "Unterminated string.");
		return false; //was not successful
	}

	advance();
	//only consider the values inside the quotation marks
	addToken(TokenType::STRING);
	return true; //return success
}
void Scanner::number() {
	for(; !isAtEnd() && isdigit(source_[current_]); advance());

	if(!isAtEnd() && source_[current_] == '.' && isdigit(peekNext())) {
		advance();
		
		for(; !isAtEnd() && isdigit(source_[current_]); advance());
	}
	addToken(TokenType::NUMBER);
}
void Scanner::identifier() {
	for(;!isAtEnd() && isAlphaNumeric(peek()); advance());
	
	TokenType type = TokenType::IDENTIFIER;
	auto iterator = keywords_.find(source_.substr(start_, current_-start_));
	if(iterator != keywords_.end())
		type = iterator -> second;
	
	addToken(type);
}
bool Scanner::isAlphaNumeric(char c) {
	return isAlpha(c) || isdigit(c);
}
bool Scanner::isAlpha(char c) {
	return isalpha(c) || c == '_';
}
