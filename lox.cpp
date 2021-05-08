#include <iostream>

#include "lox.hpp"

void lox::runPrompt() { 
	std::string line;

	for(;;) {
		std::cout << "> ";
		std::getline(std::cin, line);
		if(line.compare("exit();") == 0) break;
		lox::run(line);
	}
}

void lox::runFile(char* path) {
	std::cout << "runFile " << path << std::endl;
}

void lox::run(const std::string& source) {
	std::cout <<"Your input: " << source;
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
