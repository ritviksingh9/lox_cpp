#include <cctype>

#include "scanner/scanner.hpp"
#include "error/staticErrorHandler.hpp"

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
	successState = true;
}

const std::map<std::string, TokenType> Scanner::keywords_ = Scanner::initMap();

std::vector<Token> Scanner::scanTokens() {
	// scans the string passed into the class and outputs a vector of tokens
	while(!isAtEnd()) {
		start_ = current_;
		scanToken();
	}
	tokens_.emplace_back(TokenType::ENDOFFILE, "", line_);
	return tokens_;
}
bool Scanner::isAtEnd() {return current_ >= source_.length();}

void Scanner::scanToken() {
	// processes the upcoming token differently depending on its type
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
		// binary operators
		case '!': addToken(match('=') ? TokenType::BANG_EQUAL : 
						TokenType::BANG); break;
		case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : 
						TokenType::EQUAL); break;
		case '<': addToken(match('=') ? TokenType::LESS_EQUAL : 
						TokenType::LESS); break;
		case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : 
						TokenType::GREATER); break;
		// ignore comments
		case '/':
			if(match('/')) 
				while(!isAtEnd() && peek() != '\n')  advance();
			else addToken(TokenType::SLASH);	
		// whitespace
		case ' ': break;
		case '\r': break;
		case '\t': break;
		case '\n': line_++; break;
		// string literals
		case '"': string(); break;
		default:
			// checks if it's a number
			if(isdigit(c)) 
				number();
			// checks if it's an identifier
			else if(isalpha(c))
				identifier();
			else {
				successState = false;
				staticError::reportScannerError(line_, "Unexpected character.");
			}
	}
}
char Scanner::advance() {return source_.at(current_++);} 
void Scanner::addToken(TokenType type) {
	// add token of a particular type to the internal buffer
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
void Scanner::string() {
	// cycle through all the output
	while(!isAtEnd() && peek() != '"') {
		if(peek() == '\n') 
			line_++;
		advance();
	}
	// check for unterminated string
	if(isAtEnd()) {
		successState = false;
		staticError::reportScannerError(line_, "Unterminated string.");
	}
	advance();
	// only consider the values inside the quotation marks
	addToken(TokenType::STRING);
}
void Scanner::number() {
	// checks if the upcoming substring is a number and then
	// adds it to the internal buffer
	for(; !isAtEnd() && isdigit(source_[current_]); advance());

	if(!isAtEnd() && source_[current_] == '.' && isdigit(peekNext())) {
		advance();
		
		for(; !isAtEnd() && isdigit(source_[current_]); advance());
	}
	addToken(TokenType::NUMBER);
}
void Scanner::identifier() {
	// checks if the upcoming substring corresponds to an identifier and then
	// adds it to the internal buffer
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

bool Scanner::getSuccess() {return successState;}
