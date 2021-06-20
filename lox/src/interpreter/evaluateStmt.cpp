#include <iostream>

#include "types/ast/stmt.hpp"

void ExpressionStmt::evaluate() const {expression -> evaluate();}
void PrintStmt::evaluate() const {
	LoxGeneric result = expression -> evaluate();
	std::cout << result.toString() << std::endl;
}

