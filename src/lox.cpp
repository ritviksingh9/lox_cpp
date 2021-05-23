#include <iostream>
#include <string>

#include "lox.hpp"
//#include "scanner.hpp"
#include "token.hpp"

void lox::runPrompt() { 
	std::string line;

	for(;;) {
		std::cout << "> ";
		std::getline(std::cin, line);
		if(line.compare("exit();") == 0) break;
		lox::run(line);
	}
//	Scanner sc("awasd");
//	sc.scanTokens();
//	TokenStr tok(TokenType::LEFT_PAREN, "hello!", "hello!", 3);
//	std::cout << "\n" << tok.lexeme << "\n";
	TokenImpl <std::string> tok2(TokenType::LEFT_PAREN, "hello!", 3, "hello!");
	std::cout << "\n" << tok2.lexeme << "\n";
}

void lox::runFile(char* path) {
	std::cout << "runFile " << path << std::endl;
}

void lox::run(const std::string& source) {
	
}

int main(int argc, char* argv[]) {
	if(argc == 1) {
		lox::runPrompt();	
	}
	else if(argc == 2) {
		lox::runFile(argv[1]);
	}
	else {
		std::cerr << "Usage: lox [script]\n";
	}

	return 0;
}
