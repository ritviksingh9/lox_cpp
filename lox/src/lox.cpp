#include <iostream>
#include <string>

#include "lox.hpp"
#include "scanner.hpp"
#include "expr.hpp"

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
	Token tok1(TokenType::MINUS, "-", 1);
	Token tok2(TokenType::STAR, "*", 1);
	
	Literal <double>* lit1 = new Literal <double> (45.67);
	Literal <double>* lit2 = new Literal <double> (123);

	Grouping* group = new Grouping(std::shared_ptr<Expr>(lit1));
	Unary* unary = new Unary (tok1, std::shared_ptr<Expr>(lit2));

	Binary binary(std::shared_ptr<Expr>(unary), tok2, std::shared_ptr<Expr>(group));
	std::cout << binary.getString() << std::endl;
	
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
