#include "expr.hpp"
std::string parenthesize(const std::string& str,
			 	const std::vector<std::shared_ptr<Expr>>& expressions) {
	std::string strRep = "(";
	strRep.append(str);
	for(auto x: expressions) {
		strRep.append(" ");
		strRep.append(x -> getString());
	}
	strRep.append(")");

	return strRep;
}

std::string Binary::getString() const {
	std::vector<std::shared_ptr<Expr>> expressions = {left, right};
	return parenthesize(op.lexeme, expressions);
}
std::string Grouping::getString() const {
	std::vector<std::shared_ptr<Expr>> expressions = {expression};
	return parenthesize("group", expressions);
}
std::string Unary::getString() const {
	std::vector<std::shared_ptr<Expr>> expressions = {right};
	return parenthesize(op.lexeme, expressions);
}
