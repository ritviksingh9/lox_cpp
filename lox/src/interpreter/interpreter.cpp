#include "interpreter/interpreter.hpp"
#include "interpreter/interpreterEnv.hpp"
#include "error/staticErrorHandler.hpp"

namespace interpreterEnv {
	std::map<std::string, LoxGeneric> environment;
	bool successState = true;


	LoxGeneric retrieveVar(const Token& tok) {
		if(environment.count(tok.lexeme) == 0) {
			successState = false;
			staticError::reportSyntaxError(tok);
			return LoxGeneric();
		}
		return environment[tok.lexeme];
	}
	void assignVar(const Token& tok, LoxGeneric value) {
		if(environment.count(tok.lexeme) == 0) {
			successState = false;
			staticError::reportSyntaxError(tok);
			return;
		}	
		environment[tok.lexeme] = value;
	}
}

void Interpreter::addVar(std::shared_ptr<VarStmt> varStatement) {
	interpreterEnv::environment[varStatement->name.lexeme] = varStatement->declaration();
}

LoxGeneric Interpreter::retrieveVar(const Token& tok) {
	if(interpreterEnv::environment.count(tok.lexeme) == 0) {
		successState_ = false;
		staticError::reportSyntaxError(tok);
		return LoxGeneric();
	}
	return interpreterEnv::environment[tok.lexeme];
}
Interpreter::Interpreter() : successState_(true) {interpreterEnv::successState = true;}
void Interpreter::interpret(const std::vector<std::shared_ptr<Stmt>>& statements) {
	for(auto stmt: statements) {
		if(stmt -> type == StmtType::VAR) {
			std::shared_ptr<VarStmt> varStmt = std::dynamic_pointer_cast<VarStmt>(stmt);
			addVar(varStmt);
		}
		else
			stmt -> evaluate();	
	}
}

bool Interpreter::getSuccess() {return interpreterEnv::successState;}
