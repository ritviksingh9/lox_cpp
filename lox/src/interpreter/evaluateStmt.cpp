#include <iostream>

#include "types/ast/stmt.hpp"
#include "interpreter/interpreterEnv.hpp"

void ExpressionStmt::evaluate() const {expression -> evaluate();}
void PrintStmt::evaluate() const {
	LoxGeneric result = expression -> evaluate();
	std::cout << result.toString() << std::endl;
}
void Block::evaluate() const {
	interpreterEnv::currentEnv = std::shared_ptr<EnvNode>(new EnvNode(interpreterEnv::currentEnv));
	for(auto stmt: statements) {
		if(stmt -> type == StmtType::VAR) {
			interpreterEnv::addVar(std::dynamic_pointer_cast<VarStmt>(stmt));
		}
		else {
			stmt -> evaluate();
		}
	}
	interpreterEnv::currentEnv = interpreterEnv::currentEnv -> parentEnv;
}
