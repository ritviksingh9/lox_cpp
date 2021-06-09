#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <memory>

#include "token.hpp"


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
	template <class U>
	U evaluate();
};
class Grouping: public Expr {
public:
	std::shared_ptr<Expr> expression;

	Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

	std::string getString() const override;
	template <class U>
	U evaluate();
};
template <class T>
class Literal: public Expr {
public:
	T value;

	Literal(T value) : value(value) {}

	std::string getString() const override;
	template <class U>
	U evaluate();
};
class Unary: public Expr {
public:
	Token op;
	std::shared_ptr<Expr> right;

	Unary(Token op, std::shared_ptr<Expr> right) : op(op),
	                                               right(right) {}

	std::string getString() const override;
	template <class U>
	U evaluate();
};

#include "astPrinter.tpp"

#endif
