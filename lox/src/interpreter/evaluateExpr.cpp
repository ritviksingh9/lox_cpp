#include "types/ast/expr.hpp"
#include "interpreter/interpreterEnv.hpp"
#include <iostream>

LoxGeneric Binary::evaluate() const {
	// only initially evaluate left one to allow for short-circuiting of logical operators
	LoxGeneric leftExpr = left -> evaluate();
	// logical opererators
	if(op.type == TokenType::AND) {
		// short-circuit AND operator
		if(!leftExpr.getTruthValue()) {return leftExpr;}
		return right -> evaluate();
	}
	else if(op.type == TokenType::OR) {
		// short-circuit OR operator
		if(leftExpr.getTruthValue()) {return leftExpr;}
		return right -> evaluate();
	}
	// evaluate right expression for the rest of the binary operators
	LoxGeneric rightExpr = right -> evaluate();
	// deal with other binary operators
	switch(op.type) {
		// arithmetic Operators 
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
		// comparison Operators
		case TokenType::EQUAL_EQUAL:
			return LoxGeneric(left == right);
			break;
		case TokenType::BANG_EQUAL:
			return LoxGeneric(left != right);
			break;
		case TokenType::GREATER_EQUAL:
			return LoxGeneric(left >= right);
			break;
		case TokenType::LESS_EQUAL:
			return LoxGeneric(left <= right);
			break;
		case TokenType::GREATER:
			return LoxGeneric(left > right);
			break;
		case TokenType::LESS:
			std::cout << left << " " << right << std::endl;
			return LoxGeneric(left < right);
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
