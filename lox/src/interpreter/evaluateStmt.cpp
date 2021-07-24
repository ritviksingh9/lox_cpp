#include <iostream>

#include "types/ast/stmt.hpp"
#include "interpreter/interpreterEnv.hpp"

void ExpressionStmt::evaluate() const {expression -> evaluate();}
void PrintStmt::evaluate() const {
	LoxGeneric result = expression -> evaluate();
	// print the evaluated expression
	std::cout << result.toString() << std::endl;
}
void BlockStmt::evaluate() const {
	// create a new scope in the parent pointer tree
	interpreterEnv::currentEnv = std::shared_ptr<EnvNode>(new EnvNode(interpreterEnv::currentEnv));
	for(auto stmt: statements) {
		// add variable to innermost scope
		if(stmt -> type == StmtType::VAR) {
			interpreterEnv::addVar(std::dynamic_pointer_cast<VarStmt>(stmt));
		}
		// evaluate all other statements as normal
		else {
			stmt -> evaluate();
		}
	}
	// at the end of this scope, delete environment and go back to the parent scope
	interpreterEnv::currentEnv = interpreterEnv::currentEnv -> parentEnv;
}
void IfStmt::evaluate() const {
	bool conditionBranch = condition->evaluate().getTruthValue();
	// check for if statement
	if(conditionBranch)
		thenStmt -> evaluate();
	// check for else statement
	else if(elseStmt != nullptr)
		elseStmt -> evaluate();
}
