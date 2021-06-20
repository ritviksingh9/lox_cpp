#include <iostream>

#include "lox/lox.hpp"
#include "scanner/scanner.hpp"
#include "parser/parser.hpp"
#include "interpreter/interpreter.hpp"

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
	/*
	std::string str1 = "-123 * 45.67 / 0";
	bool successState = true;
	Scanner sc(str);
	auto tokens = sc.scanTokens();
	succesState = sc.getSuccess();
	Parser parser(tokens);
	std::shared_ptr<Expr> expr = parser.parse();
	LoxGeneric eval = expr -> evaluate();
	std::cout << expr -> getString() << std::endl;
	std::cout << eval.numValue << std::endl;
	*/	
//	std::string str2 = "print \"hello world\";  print 2*8;";
//	std::string str2 = "var x = 3; print x=4; var y = 4; y = x+y; print y;";
	std::string str2 = "var a=3; var b=4; var c = 9;\n {var a = 5;\n b=10; \n print a; print b; print c;} print a; print b;";
	bool successState = true;
	//scanning
	Scanner sc(str2);
	std::vector<Token> tokens = sc.scanTokens();
	successState = successState && sc.getSuccess();
	//parsing
	Parser parser(tokens);
	std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
	successState = successState && parser.getSuccess();
	//interpreting
	Interpreter interpreter;
	interpreter.interpret(statements);
	successState = successState && interpreter.getSuccess();
	std::cout << "Success State of program: " << successState << std::endl;


	/*
	if(argc == 1) {
		lox::runPrompt();	
	}
	else if(argc == 2) {
		lox::runFile(argv[1]);
	}
	else {
		std::cerr << "Usage: lox [script]\n";
	}*/

	return 0;
}
