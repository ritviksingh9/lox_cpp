#include "types/ast/stmt.hpp"

LoxGeneric VarStmt::declaration() const {
	if(initializer == nullptr)
		return LoxGeneric();
	return initializer -> evaluate();
}
