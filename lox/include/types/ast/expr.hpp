#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <memory>
#include "types/token.hpp"
#include "types/literalGeneric.hpp"
#include "types/loxGeneric.hpp"

enum class ExprType {BINARY, GROUPING, LITERAL, UNARY, IDENTIFIER, ASSIGN};

class Expr{
public:
	ExprType type;
	Expr(ExprType type) : type(type) {}
	virtual ~Expr() {}
	virtual std::string getString() const = 0;
	virtual LoxGeneric evaluate() const = 0;
};

class Binary: public Expr {
public:
	std::shared_ptr<Expr> left;
	Token op;
	std::shared_ptr<Expr> right;

	Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : Expr(ExprType::BINARY),
										    left(left),
	                                                                            op(op),
	                                                                            right(right) {}

	std::string getString() const override;
	LoxGeneric evaluate() const override;
};
class Grouping: public Expr {
public:
	std::shared_ptr<Expr> expression;

	Grouping(std::shared_ptr<Expr> expression) : Expr(ExprType::GROUPING),
					             expression(expression) {}

	std::string getString() const override;
	LoxGeneric evaluate() const override;
};
class Literal: public Expr {
public:
	LiteralGeneric value;

	Literal() : Expr(type) {}
	Literal(bool value) : Expr(ExprType::LITERAL),
			      value(value) {}
	Literal(double value) : Expr(ExprType::LITERAL),
				value(value) {}
	Literal(std::string value) : Expr(ExprType::LITERAL),
				     value(value) {}

	std::string getString() const override;
	LoxGeneric evaluate() const override;
};
class Unary: public Expr {
public:
	Token op;
	std::shared_ptr<Expr> right;

	Unary(Token op, std::shared_ptr<Expr> right) : Expr(ExprType::UNARY),
						       op(op),
	                                               right(right) {}

	std::string getString() const override;
	LoxGeneric evaluate() const override;
};
class IdentifierExpr: public Expr {
public:
	Token target;

	IdentifierExpr(const Token& target) : Expr(ExprType::IDENTIFIER),
						  target(target) {}

	std::string getString() const override;
	LoxGeneric evaluate() const override;
};
class AssignExpr : public Expr {
public:
	Token target;
	std::shared_ptr<Expr> expression;

	AssignExpr(const Token& target, std::shared_ptr<Expr> expression) : Expr(ExprType::ASSIGN),
						       target(target),
						       expression(expression) {}

	std::string getString() const override;
	LoxGeneric evaluate() const override;
};
#endif
