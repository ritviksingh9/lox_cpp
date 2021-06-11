#include <iostream>

#include "lox.hpp"
#include "scanner.hpp"
#include "parser.hpp"

void lox::runPrompt() { 
	std::string line;

	for(;;) {
		std::cout << "> ";
		std::getline(std::cin, line);
		if(line.compare("exit();") == 0) break;
		lox::run(line);
	}
	Scanner sc("if(var == True) for \"awdawdwadawdawd\" 3.123");
	auto tokens = sc.scanTokens();
	for(auto tok: tokens) {
		std::cout << "Token: " << tok.lexeme << std::endl;
	}
}

void lox::runFile(char* path) {
	std::cout << "runFile " << path << std::endl;
}

void lox::run(const std::string& source) {
	
}

int main(int argc, char* argv[]) {
	std::string str = "-123 * 45.67";

	Scanner sc(str);
	auto tokens = sc.scanTokens();
	Parser parser(tokens);
	std::shared_ptr<Expr> expr = parser.parse();
	std::cout << expr -> getString() << std::endl;

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
