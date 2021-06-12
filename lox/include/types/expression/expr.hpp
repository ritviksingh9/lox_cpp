#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <memory>

#include "types/token.hpp"
#include "types/literalGeneric.hpp"


class Expr{
public:
	virtual ~Expr() {}
	virtual std::string getString() const = 0;
};

class Binary: public Expr {
public:
	std::shared_ptr<Expr> left;
	Token op;
	std::shared_ptr<Expr> right;

	Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left),
	                                                                            op(op),
	                                                                            right(right) {}

	std::string getString() const override;
};
class Grouping: public Expr {
public:
	std::shared_ptr<Expr> expression;

	Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

	std::string getString() const override;
};
class Literal: public Expr {
public:
	LiteralGeneric value;

	Literal() {}
	Literal(bool value) : value(value) {}
	Literal(double value) : value(value) {}
	Literal(std::string value) : value(value) {}

	std::string getString() const override;
};
class Unary: public Expr {
public:
	Token op;
	std::shared_ptr<Expr> right;

	Unary(Token op, std::shared_ptr<Expr> right) : op(op),
	                                               right(right) {}

	std::string getString() const override;
};

#endif
