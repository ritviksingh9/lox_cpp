#include "interpreter/interpreter.hpp"
#include "interpreter/interpreterEnv.hpp"
#include "error/staticErrorHandler.hpp"

namespace interpreterEnv {
	std::map<std::string, LoxGeneric> environment;
	std::shared_ptr<EnvNode> currentEnv;
	bool successState = true;


	LoxGeneric retrieveVar(const Token& tok) {
		// this function returns value from a specific variable
		std::shared_ptr<EnvNode> curr;
		// searching for variable by going through parent pointer tree
		for(curr = currentEnv; 
		    curr != nullptr && curr -> environment.count(tok.lexeme) == 0;
		    curr = curr->parentEnv);
		// variable not found
		if(curr == nullptr) {
			successState = false;
			staticError::reportSyntaxError(tok);
			return LoxGeneric();
		}
		return curr->environment[tok.lexeme];
	}
	void assignVar(const Token& tok, LoxGeneric value) {
		// this function assigns the value of a variable to a given value
		std::shared_ptr<EnvNode> curr;
		// searching for variable by going through parent pointer tree
		for(curr = currentEnv; 
		    curr != nullptr && curr -> environment.count(tok.lexeme) == 0;
		    curr = curr->parentEnv);
		// variable not found
		if(curr == nullptr) {
			successState = false;
			staticError::reportSyntaxError(tok);
			return;
		}	
		curr -> environment[tok.lexeme] = value;
	}

	void addVar(std::shared_ptr<VarStmt> varStatement) {
		// adds a variable to the current scope
		currentEnv -> environment[varStatement -> name.lexeme] =
		varStatement -> declaration();
	}
}

void Interpreter::addVar(std::shared_ptr<VarStmt> varStatement) {
	interpreterEnv::addVar(varStatement);
}
LoxGeneric Interpreter::retrieveVar(const Token& tok) {
	return interpreterEnv::retrieveVar(tok);
}
Interpreter::Interpreter() : successState_(true) {
	interpreterEnv::successState = true;
	interpreterEnv::currentEnv = std::shared_ptr<EnvNode>(new EnvNode());
}
void Interpreter::interpret(const std::vector<std::shared_ptr<Stmt>>& statements) {
	for(auto stmt: statements) {
		if(stmt -> type == StmtType::VAR) {
			std::shared_ptr<VarStmt> varStmt = std::dynamic_pointer_cast<VarStmt>(stmt);
			addVar(varStmt);
		}
		else if(stmt -> type == StmtType::BLOCK) {
			interpreterEnv::currentEnv = std::shared_ptr<EnvNode>
						 (new EnvNode(interpreterEnv::currentEnv));
			stmt -> evaluate();
			interpreterEnv::currentEnv = interpreterEnv::currentEnv 
						     -> parentEnv;
		}
		else
			stmt -> evaluate();	
	}
}

bool Interpreter::getSuccess() {return interpreterEnv::successState;}
