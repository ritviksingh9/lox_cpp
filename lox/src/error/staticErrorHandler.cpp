#include <iostream>

#include "error/staticErrorHandler.hpp"

namespace staticError {

void reportScannerError(int line, const std::string& message) { 
//	throw std::runtime_error("Line: "+std::to_string(line)+" "+message);
	std::cerr << "Error while scanning: line " << line << " " << message <<  std::endl;
}
void reportParserError(const Token& tok, const std::string& message) {
	if(tok.type == TokenType::ENDOFFILE) {
		std::cerr << "Error while parsing: line " << tok.line << " at end " 
			  << message << std::endl;
	}
	else {
		std::cerr << "Error while parsing: line " << tok.line << " at '"
			  << tok.lexeme << "' " << message << std::endl;
	}
}
void reportSyntaxError(const Token& tok) {
	std::cerr << "Syntax error while parsing: line " << tok.line << " " <<	"'" 
		  << tok.lexeme << "'" << "not defined. " << std::endl;
}
}
