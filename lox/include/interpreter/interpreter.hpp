#include "types/expression/expr.hpp"

class Interpreter {
public:
	Interpreter();
	void interpret(std::shared_ptr<Expr> expr);
};
