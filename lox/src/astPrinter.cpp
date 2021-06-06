#include <string>

#include "expr.hpp"

std::string Binary::getString() {
	std::vector<Expr*> expressions = {left, right};
	return parenthesize(op.lexeme, expressions);
}
std::string Grouping::getString() {
	std::vector<Expr*> expressions = {expression};
	return parenthesize("group", expressions)
}
std::string Literal::getString() {
	if(value == NULL) return "nil";
	return typeid(value) == typeid(int) ? to_string(value) : value;
}
std::string Unary::getString() {
	std::vector<Expr*> expressions = {right};
	return parenthesize(op.lexeme, expressions);
}

std::string parenthesize(const std::string& str,
			 const std::vector<Expr*>& expressions) {
	std::string str = "(".append(str);
	for(auto x: expressions) {
		str.append(" ");
		str.append(x -> getString());
	}
	str.append(")");

	return str;
}

int main() {
	TokenImpl tok1(TokenType::MINUS, "-", 1, NULL);
	TokenImpl tok2(TokenType::STAR, "*", 1, NULL);
	
	Literal<double> lit1(45.67);
	Literal<double> lit2(123);

	Grouping group(&lit2);
	Unary unary(tok1, lit2);

	Binary binary(&unary, tok2, &group);
	std::cout << binary.getString() << std::endl;
}
