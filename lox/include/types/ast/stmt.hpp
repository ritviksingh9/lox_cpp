#ifndef STMT_H
#define STMT_H

#include <vector>
#include <memory>

#include "types/token.hpp"
#include "types/literalGeneric.hpp"
#include "types/ast/expr.hpp"

class Stmt{
public:
	std::shared_ptr<Expr> expression;
	Stmt(const std::shared_ptr<Expr>& expression) : expression(expression) {};
	virtual ~Stmt() {}
	virtual void evaluate() const = 0;
};

class Expression: public Stmt {
public:
//	std::shared_ptr<Expr> expression;

	Expression(const std::shared_ptr<Expr>& expression) : Stmt(expression) {}

	void evaluate() const override;
};
class Print: public Stmt {
public:
//	std::shared_ptr<Expr> expression;

	Print(const std::shared_ptr<Expr>& expression) : Stmt(expression) {}

	void evaluate() const override;
};

#endif
