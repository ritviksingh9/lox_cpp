#include "interpreter/interpreter.hpp"

void Interpreter::interpret(const std::vector<std::shared_ptr<Stmt>>& statements) {
	for(auto stmt: statements) {
		stmt -> evaluate();	
	}
}

bool Interpreter::getSuccess() {return successState_;}
