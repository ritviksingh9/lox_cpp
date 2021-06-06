#include <iostream>
#include "expr.hpp"

int main() {
	void* nullType = 0;
	TokenImpl <void*> tok1(TokenType::MINUS, "-", 1, nullType);
	TokenImpl <void*>tok2(TokenType::STAR, "*", 1, nullType);
	
	Literal<double> lit1(45.67);
	Literal<double> lit2(123);

	Grouping group(&lit1);
	Unary<void*> unary(tok1, &lit2);

	Binary<void*> binary(&unary, tok2, &group);
	std::cout << binary.getString() << std::endl;
}
