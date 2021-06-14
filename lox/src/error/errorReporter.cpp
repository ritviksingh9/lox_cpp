#include <iostream>

#include "error/errorReporter.hpp"

void reportScannerError(int line, std::string message) { 
//	throw std::runtime_error("Line: "+std::to_string(line)+" "+message);
	std::cerr << "Error while scanning: line " << line << " " << message <<  std::endl;
}
void reportParserError(Token tok, std::string message) {
	if(tok.type == TokenType::ENDOFFILE) {
		std::cerr << "Error while parsing: line " << tok.line << " at end " 
			  << message << std::endl;
	}
	else {
		std::cerr << "Error while parsing: line " << tok.line << " at '"
			  << tok.lexeme << "' " << message << std::endl;
	}
}
