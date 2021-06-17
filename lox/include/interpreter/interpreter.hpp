#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "types/ast/stmt.hpp"


class Interpreter {
private:
	bool successState_;
public:
//	Interpreter();
	void interpret(const std::vector<std::shared_ptr<Stmt>>& statements);
	bool getSuccess();
};

#endif
