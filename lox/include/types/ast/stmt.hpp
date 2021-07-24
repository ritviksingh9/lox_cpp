#ifndef STMT_H
#define STMT_H

#include <vector>
#include <memory>

#include "types/token.hpp"
#include "types/loxGeneric.hpp"
#include "types/ast/expr.hpp"

enum class StmtType {EXPR, PRINT, VAR, BLOCK, IF};

class Stmt{
public:
	StmtType type;
	Stmt(StmtType type) : type(type) {}
	virtual ~Stmt() {}
	virtual void evaluate() const {};
	virtual LoxGeneric declaration() const {return LoxGeneric();};
};

class ExpressionStmt: public Stmt {
public:
	std::shared_ptr<Expr> expression;

	ExpressionStmt(const std::shared_ptr<Expr>& expression) : Stmt(StmtType::EXPR),
								  expression(expression) {}

	void evaluate() const override;
};
class PrintStmt: public Stmt {
public:
	std::shared_ptr<Expr> expression;

	PrintStmt(const std::shared_ptr<Expr>& expression) : Stmt(StmtType::PRINT),
							     expression(expression) {}

	void evaluate() const override;
};
class VarStmt: public Stmt {
public:
	Token name;
	std::shared_ptr<Expr> initializer;

	VarStmt(const Token& name, const std::shared_ptr<Expr>& initializer) : Stmt(StmtType::VAR),
									       name(name),
							 	               initializer(initializer) {}
	
//	void evaluate() const override;
	LoxGeneric declaration() const override;
};
class BlockStmt: public Stmt {
public:
	std::vector<std::shared_ptr<Stmt>> statements;

	BlockStmt(const std::vector<std::shared_ptr<Stmt>>& statements) : Stmt(StmtType::BLOCK),
								      statements(statements) {};
	
	void evaluate() const override;
};
class IfStmt: public Stmt {
public:
	std::shared_ptr<Expr> condition;
	std::shared_ptr<Stmt> thenStmt;
	std::shared_ptr<Stmt> elseStmt;

	IfStmt(const std::shared_ptr<Expr>& condition, 
	       const std::shared_ptr<Stmt>& thenStmt,
	       const std::shared_ptr<Stmt>& elseStmt) : Stmt(StmtType::IF),
	       						condition(condition),
							thenStmt(thenStmt),
							elseStmt(elseStmt) {}
	void evaluate() const override;
};
#endif
