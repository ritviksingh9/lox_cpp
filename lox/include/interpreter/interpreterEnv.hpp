#ifndef INTERPRETER_ENV_H
#define INTERPRETER_ENV_H

#include <map>
#include "types/loxGeneric.hpp"
#include "types/ast/stmt.hpp"

struct EnvNode {
	std::shared_ptr<EnvNode> parentEnv;
	std::map<std::string, LoxGeneric> environment;		

	EnvNode() : parentEnv(nullptr) {};
	EnvNode(std::shared_ptr<EnvNode> parentEnv) : parentEnv(parentEnv) {};
};

namespace interpreterEnv {
	extern std::shared_ptr<EnvNode> currentEnv; 
	extern std::map<std::string, LoxGeneric> environment;
	extern bool successState;

	extern LoxGeneric retrieveVar(const Token& tok);
	extern void assignVar(const Token& tok, LoxGeneric value);
	extern void addVar(std::shared_ptr<VarStmt> varStatement);
}

#endif
