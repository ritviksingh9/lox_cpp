#include "interpreter/interpreter.hpp"
#include "interpreter/interpreterEnv.hpp"
#include "error/staticErrorHandler.hpp"

namespace interpreterEnv {
	std::map<std::string, LoxGeneric> environment;
	std::shared_ptr<EnvNode> currentEnv;
	bool successState = true;


	LoxGeneric retrieveVar(const Token& tok) {
		std::shared_ptr<EnvNode> curr;
		for(curr = currentEnv; 
		    curr != nullptr && curr -> environment.count(tok.lexeme) == 0;
		    curr = curr->parentEnv);
		if(curr == nullptr) {
			successState = false;
			staticError::reportSyntaxError(tok);
			return LoxGeneric();
		}
		return curr->environment[tok.lexeme];
	}
	void assignVar(const Token& tok, LoxGeneric value) {
		std::shared_ptr<EnvNode> curr;
		for(curr = currentEnv; 
		    curr != nullptr && curr -> environment.count(tok.lexeme) == 0;
		    curr = curr->parentEnv);
		if(curr == nullptr) {
			successState = false;
			staticError::reportSyntaxError(tok);
			return;
		}	
		curr -> environment[tok.lexeme] = value;
	}

	void addVar(std::shared_ptr<VarStmt> varStatement) {
		interpreterEnv::currentEnv -> environment[varStatement -> name.lexeme] =
		varStatement -> declaration();
	}
}

void Interpreter::addVar(std::shared_ptr<VarStmt> varStatement) {
	interpreterEnv::currentEnv -> environment[varStatement -> name.lexeme] =
	varStatement -> declaration();
}

LoxGeneric Interpreter::retrieveVar(const Token& tok) {
	std::shared_ptr<EnvNode> curr;
	for(curr = interpreterEnv::currentEnv; 
	    curr != nullptr && curr -> environment.count(tok.lexeme) == 0;
	    curr = curr->parentEnv);
	if(curr == nullptr) {
		successState_ = false;
		staticError::reportSyntaxError(tok);
		return LoxGeneric();
	}
	return interpreterEnv::environment[tok.lexeme];
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
