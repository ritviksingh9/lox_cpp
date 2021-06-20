#include "types/ast/expr.hpp"
#include "interpreter/interpreterEnv.hpp"

LoxGeneric Binary::evaluate() const {
	LoxGeneric leftExpr = left -> evaluate();
	LoxGeneric rightExpr = right -> evaluate();
	
	switch(op.type) {
		//Arithmetic Operators 
		case TokenType::PLUS:
			return leftExpr + rightExpr;
			break;
		case TokenType::MINUS:
			return leftExpr - rightExpr;
			break;
		case TokenType::STAR:
			return leftExpr * rightExpr;
			break;
		case TokenType::SLASH:
			return leftExpr / rightExpr;
			break;
		//Comparison Operators
		case TokenType::EQUAL_EQUAL:
			return left == right;
			break;
		case TokenType::BANG_EQUAL:
			return left != right;
			break;
		case TokenType::GREATER_EQUAL:
			return left >= right;
			break;
		case TokenType::LESS_EQUAL:
			return left <= right;
			break;
		case TokenType::GREATER:
			return left > right;
			break;
		case TokenType::LESS:
			return left < right;
			break;
	}	
	return LoxGeneric();
}
LoxGeneric Grouping::evaluate() const {return expression->evaluate();}
LoxGeneric Literal::evaluate() const {
	if(value.type == LiteralType::BOOL) return LoxGeneric(value.boolValue);
	else if(value.type == LiteralType::NUM) return LoxGeneric(value.numValue);
	else if(value.type == LiteralType::STRING) return LoxGeneric(value.strValue);
	return LoxGeneric();
}
LoxGeneric Unary::evaluate() const {
	LoxGeneric rightExpr =right -> evaluate();
	switch(op.type) {
		case TokenType::MINUS:
			return rightExpr*-1;
			break;
		case TokenType::BANG:
			return !rightExpr.getTruthValue();
			break;
	}
	return LoxGeneric();
}
LoxGeneric IdentifierExpr::evaluate() const {return interpreterEnv::retrieveVar(target);}
LoxGeneric AssignExpr::evaluate() const {
	LoxGeneric value = expression -> evaluate();
	interpreterEnv::assignVar(target, value);
	return value;
}
