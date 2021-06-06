#include "expr.hpp"


std::string Grouping::getString() const {
	std::vector<Expr*> expressions = {expression};
	return parenthesize("group", expressions);
}

