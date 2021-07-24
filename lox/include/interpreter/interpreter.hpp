#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "types/ast/stmt.hpp"

class Interpreter {
private:
	bool successState_;

	// aliases for functions in interpreterEnv
	LoxGeneric retrieveVar(const Token& tok);
	void addVar(std::shared_ptr<VarStmt> varStatement);
public:
	Interpreter();
	void interpret(const std::vector<std::shared_ptr<Stmt>>& statements);
	bool getSuccess();
};

#endif
