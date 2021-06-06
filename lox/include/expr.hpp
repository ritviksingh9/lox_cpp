#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>

#include "token.hpp"


class Expr{
public:
	virtual ~Expr() {}
	virtual std::string getString() const = 0;
};

template <class T>
class Binary: public Expr {
public:
	Expr* left;
	TokenImpl<T> op;
	Expr* right;

	Binary(Expr* left, TokenImpl<T> op, Expr* right) : left(left),
	                                                   op(op),
	                                                   right(right) {}

	std::string getString() const override;
	template <class U>
	U evaluate();
};
class Grouping: public Expr {
public:
	Expr* expression;

	Grouping(Expr* expression) : expression(expression) {}

	std::string getString() const override;
	template <class U>
	U evaluate();
};
template <class T>
class Literal: public Expr {
public:
	T value;

	Literal(T value) : Expr(), value(value) {}

	std::string getString() const override;
	template <class U>
	U evaluate();
};
template <class T>
class Unary: public Expr {
public:
	TokenImpl<T> op;
	Expr* right;

	Unary(TokenImpl<T> op, Expr* right) : op(op),
	                                      right(right) {}

	std::string getString() const override;
	template <class U>
	U evaluate();
};

#include "astPrinter.tpp"
#endif
