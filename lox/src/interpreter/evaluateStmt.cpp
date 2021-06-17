#include <iostream>

#include "types/ast/stmt.hpp"

void Expression::evaluate() const {expression -> evaluate();}
void Print::evaluate() const {
	LoxGeneric result = expression -> evaluate();
	std::cout << result.toString() << std::endl;
}


