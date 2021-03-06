#include <iostream>
#include <fstream>
#include <sstream>

#include "lox/lox.hpp"
#include "scanner/scanner.hpp"
#include "parser/parser.hpp"
#include "interpreter/interpreter.hpp"

void lox::runPrompt() { 
	/*
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
	*/
	std::string str2 = "var i = 0; for(;\ni < 5; \ni = i+1\n) { print i*2;}";
	run(str2);
}

void lox::runFile(const std::string& sourceFile) {
	// quick and dirty fix because target will be in build folder
	std::ifstream fileStream("../lox/"+sourceFile);
	std::stringstream buffer;
	buffer << fileStream.rdbuf();
	std::string sourceCode = buffer.str();
	run(sourceCode);
}

void lox::run(const std::string& sourceCode) {
	bool successState = true;
	// scanning
	// the scanning process takes in a string corresponding to source code
	// and outputs a std::vector of tokens corresponding to lexical analysis
	Scanner sc(sourceCode);
	std::vector<Token> tokens = sc.scanTokens();
	successState = successState && sc.getSuccess();
	// parsing
	// the parsing process takes in a std::vector of tokens 
	// and outputs a std::vector of Stmts corresponding to a statement syntax tree
	Parser parser(tokens);
	std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
	successState = successState && parser.getSuccess();
	// interpreting
	// takes in a std::vector of Stmts and executes the statements through a tree-walk
	// algorithm
	Interpreter interpreter;
	interpreter.interpret(statements);
	successState = successState && interpreter.getSuccess();
	std::cout << "Success State of program: " << successState << std::endl;
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
//	std::string str2 = "var a=3; var b=4; var c = 9;\n {var a = 5;\n b=10; \n print a; print b; print c;} print a; print b;";
//	std::string str2 = "var a = 2; var b = 1; \nif(a > b) {\nprint \"if\";} \nelse { print \"else\";}";
//	std::string str2 = "var i = 0; \n while(i < 5) { print i*2; i = i+1; }"
/*
	std::string str2 = "var i = 0; for(;\ni < 5; \ni = i+1\n) { print i*2;}";
	bool successState = true;
	// scanning
	// the scanning process takes in a string corresponding to source code
	// and outputs a std::vector of tokens corresponding to lexical analysis
	Scanner sc(str2);
	std::vector<Token> tokens = sc.scanTokens();
	successState = successState && sc.getSuccess();
	// parsing
	// the parsing process takes in a std::vector of tokens 
	// and outputs a std::vector of Stmts corresponding to a statement syntax tree
	Parser parser(tokens);
	std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
	successState = successState && parser.getSuccess();
	// interpreting
	// takes in a std::vector of Stmts and executes the statements through a tree-walk
	// algorithm
	Interpreter interpreter;
	interpreter.interpret(statements);
	successState = successState && interpreter.getSuccess();
	std::cout << "Success State of program: " << successState << std::endl;
*/

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
