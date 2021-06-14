#include <iostream>

#include "lox/lox.hpp"
#include "scanner/scanner.hpp"
#include "parser/parser.hpp"

void lox::runPrompt() { 
	std::string line;

	for(;;) {
		std::cout << "> ";
		std::getline(std::cin, line);
		if(line.compare("exit();") == 0) break;
		lox::run(line);
	}
	Scanner sc("if(var == True) for \"awdawdwadawdawd\" 3.123 #######!QWE");
	auto tokens = sc.scanTokens();
	bool successState = sc.getSuccess();
	for(auto tok: tokens) {
		std::cout << "Token: " << tok.lexeme << std::endl;
	}
	std::cout << "SUCCESS: " << successState << std::endl;
}

void lox::runFile(char* path) {
	std::cout << "runFile " << path << std::endl;
}

void lox::run(const std::string& source) {
	
}

int main(int argc, char* argv[]) {
	std::string str = "-123 * 45.67";
	bool successState = true;
	Scanner sc(str);
	auto tokens = sc.scanTokens();
	bool succesState = sc.getSuccess();
	Parser parser(tokens);
	std::shared_ptr<Expr> expr = parser.parse();
	LoxGeneric eval = expr -> evaluate();
	std::cout << expr -> getString() << std::endl;
	std::cout << eval.numValue << std::endl;
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
