#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "types/ast/stmt.hpp"
/*
namespace interpreterEnv {
	extern std::map<std::string, LoxGeneric> environment;
}*/
class Interpreter {
private:
	bool successState_;

	LoxGeneric retrieveVar(const Token& tok);
	void addVar(std::shared_ptr<VarStmt> varStatement);
public:
	Interpreter();
	void interpret(const std::vector<std::shared_ptr<Stmt>>& statements);
	bool getSuccess();
};

#endif
