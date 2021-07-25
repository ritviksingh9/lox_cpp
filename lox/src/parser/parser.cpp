#include "parser/parser.hpp"
#include "error/staticErrorHandler.hpp"

Parser::Parser(const std::vector<Token>& sourceTokens) : tokens_(sourceTokens) {
	current_ = 0;
	successState_ = true;
	catchError_ = false;
}

bool Parser::isAtEnd() {return current_ >= tokens_.size() 
			|| tokens_[current_].type == TokenType::ENDOFFILE;}
bool Parser::check(TokenType type) {
	if(isAtEnd()) return false;
	return tokens_[current_].type == type;
}
Token Parser::advance() {
	if(!isAtEnd())
		current_++;
	return tokens_[current_-1];
}
bool Parser::match(const std::vector<TokenType>& types) {
	for(auto x: types) {
		if(check(x)) {
			advance();
			return true; 
		}
	}
	return false;
}

std::shared_ptr<Expr> Parser::primary() {
	std::vector <TokenType> keyTypes = {TokenType::STRING, TokenType::NUMBER};
	if(check(TokenType::FALSE)) {
		advance();
		return std::shared_ptr<Expr>(new Literal(false));
	}
	else if(check(TokenType::TRUE)) {
		advance();
		return std::shared_ptr<Expr>(new Literal(true));
	}
	else if(check(TokenType::NIL)) {
		advance();
		return std::shared_ptr<Expr>(new Literal());
	}
	else if(match(keyTypes)) {
		Token tok = tokens_[current_-1];
		if(tok.type == TokenType::NUMBER) {
			double literal = tok.getNumLiteral();
			return std::shared_ptr<Expr> (new Literal(literal));
		}
		else if(tok.type == TokenType::STRING) {
			std::string literal = tok.getStringLiteral();
			return std::shared_ptr<Expr> (new Literal(literal));
		}
		else {
			return std::shared_ptr<Expr> (new Literal());
		}
	}
	else if(check(TokenType::IDENTIFIER)) {
		advance();
		return std::shared_ptr<Expr>(new IdentifierExpr(tokens_[current_-1]));
	}
	else if(check(TokenType::LEFT_PAREN)) {
		advance();
		std::shared_ptr<Expr> expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return std::shared_ptr<Expr>(new Grouping(expr));
	}
	staticError::reportParserError(tokens_[current_], "Expected expression");
	return nullptr;
}
std::shared_ptr<Expr> Parser::unary() {
	std::vector <TokenType> keyTypes = {TokenType::BANG, TokenType::MINUS};
	if(match(keyTypes)) {
		Token op = tokens_[current_-1];
		std::shared_ptr<Expr> right = unary();
		return std::shared_ptr<Expr>(new Unary(op, right));
	}
	std::shared_ptr<Expr> expr = primary();
	return expr;
}
std::shared_ptr<Expr> Parser::factor() {
	std::shared_ptr<Expr> expr = unary();
	std::vector <TokenType> keyTypes = {TokenType::SLASH, TokenType::STAR};

	while(match(keyTypes)) {
		Token op = tokens_[current_-1];
		std::shared_ptr<Expr> right = unary();
		expr = std::shared_ptr<Expr>(new Binary(expr, op, right));
	}
	return expr;
}
std::shared_ptr<Expr> Parser::term() {
	std::shared_ptr<Expr> expr = factor();
	std::vector <TokenType> keyTypes = {TokenType::MINUS, TokenType::PLUS};

	while(match(keyTypes)) {
		Token op = tokens_[current_-1];
		std::shared_ptr<Expr> right = factor();
		expr = std::shared_ptr<Expr>(new Binary(expr, op, right));
	}
	return expr;
}
std::shared_ptr<Expr> Parser::comparison() {
	std::shared_ptr<Expr> expr = term();
	std::vector <TokenType> keyTypes = {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL};

	while(match(keyTypes)) {
		Token op = tokens_[current_-1];
		std::shared_ptr<Expr> right = term();
		expr = std::shared_ptr<Expr>(new Binary(expr, op, right));
	}
	return expr;
}
std::shared_ptr<Expr> Parser::equality() {
	std::shared_ptr<Expr> expr = comparison();
	std::vector <TokenType> keyTypes = {TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL};

	while(match(keyTypes)) {
		Token op = tokens_[current_-1];
		std::shared_ptr<Expr> right = comparison();
		expr = std::shared_ptr<Expr>(new Binary(expr, op, right));
	}
	return expr;
}
std::shared_ptr<Expr> Parser::assignment() {
	std::shared_ptr<Expr> expr = equality();
	if(check(TokenType::EQUAL)) {
		Token target = tokens_[current_-1];
		advance();
		std::shared_ptr<Expr> value = assignment();
		if(expr->type == ExprType::IDENTIFIER) {
			return std::shared_ptr<Expr>(new AssignExpr(target, value));
		}
		staticError::reportSyntaxError(tokens_[current_-1], "Invalid assignment target");
	}
	return expr;
}
std::shared_ptr<Expr> Parser::expression() { return assignment();}
std::vector<std::shared_ptr<Stmt>> Parser::parse() {
	// parses the internal buffer of tokens and outputs the corresponding statements
	std::vector<std::shared_ptr<Stmt>> statements;
	while (!isAtEnd()) {
		// check if this is a variable decalration
		if(check(TokenType::VAR)) {
			advance();
			statements.push_back(varDeclaration());
		}
		// generic statement
		else 
			statements.push_back(statement());
		// synchronize to the next statement/declaration
		if(catchError_)
			synchronize();
	}
	return statements;
}

std::shared_ptr<Stmt> Parser::statement() {
	// print statement
	if(check(TokenType::PRINT)) {
		advance();
		return printStatement();
	}
	// new block of code which corresponds to new scope
	else if(check(TokenType::LEFT_BRACE)) {
		advance();
		return std::shared_ptr<Stmt>(new BlockStmt(blockStatement()));
	}
	// conditional branching
	else if(check(TokenType::IF)) {
		advance();
		return ifStatement();
	}
	// while loop
	else if(check(TokenType::WHILE)) {
		advance();
		return whileStatement();
	}
	// for loop
	else if(check(TokenType::FOR)) {
		advance();
		return forStatement();
	}
	// generic statement which is just an expression
	return expressionStatement();
}
std::shared_ptr<Stmt> Parser::printStatement() {
	// printing the contents of the print statement
	std::shared_ptr<Expr> expr = expression();
	consume(TokenType::SEMICOLON, "Expected ';' at end of statement");
	return std::shared_ptr<Stmt>(new PrintStmt(expr));
}
std::vector<std::shared_ptr<Stmt>> Parser::blockStatement() {
	// new block scope
	std::vector<std::shared_ptr<Stmt>> statements;	
	while(!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
		// variable declaration
		if(check(TokenType::VAR)) {
			advance();
			statements.push_back(varDeclaration());
		}
		else 
			statements.push_back(statement());
	}
	consume(TokenType::RIGHT_BRACE, "Expected '}' after block statement.");
	return statements;
}
std::shared_ptr<Stmt> Parser::ifStatement() {
	// new if (and possibly else) statement
	// if statement condition must be wrapped in parentheses
	consume(TokenType::LEFT_PAREN, "Expected '(' before 'if' condition.");
	std::shared_ptr<Expr> condition = expression();
	consume(TokenType::RIGHT_PAREN, "Expected ')' after 'if' condition.");
	std::shared_ptr<Stmt> thenStmt = statement();
	// not all if statements need an else
	std::shared_ptr<Stmt> elseStmt = nullptr;
	if(check(TokenType::ELSE)) {
		advance();
		elseStmt = statement();
	}
	return std::shared_ptr<Stmt>(new IfStmt(condition, thenStmt, elseStmt));
}
std::shared_ptr<Stmt> Parser::whileStatement() {
	// constructing the while statement
	consume(TokenType::LEFT_PAREN, "Expected '(' before 'while' condition.");
	std::shared_ptr<Expr> condition = expression();
	consume(TokenType::RIGHT_PAREN, "Expected ')' after 'while' condition.");
	std::shared_ptr<Stmt> body = statement();
	return std::shared_ptr<Stmt>(new WhileStmt(condition, body));
}
std::shared_ptr<Stmt> Parser::forStatement() {
	// extract information for for loop
	consume(TokenType::LEFT_PAREN, "Expected '(' before 'for' loop.");
	// dealing with initial statement in for loop
	// can either be empty, initialize a variable, or just be an expression statement
	std::shared_ptr<Stmt> initialStmt = nullptr;
	if(check(TokenType::VAR)) {
		advance();
		initialStmt = varDeclaration();
	}
	else if(!check(TokenType::SEMICOLON)) {
		advance();
		initialStmt = expressionStatement();
	
	}
	else
		advance();
	// dealing with condition of for loop
	// default value of condition is true unless otherwise specified
	std::shared_ptr<Expr> condition = std::shared_ptr<Expr>(new Literal(true));
	if(!check(TokenType::SEMICOLON)) 
		condition = expression();
	consume(TokenType::SEMICOLON, "Expected ';' at the end of condition");
	// dealing with tail statement in for loop
	std::shared_ptr<Stmt> tail = nullptr;
	// when checking for expression, need to not use expressionStatement()
	// because we are not expecting a semicolon at the end
	if(!check(TokenType::RIGHT_PAREN)) 
		tail = std::shared_ptr<Stmt>(new ExpressionStmt(expression()));
	consume(TokenType::RIGHT_PAREN, "Expected ')' after 'for' loop.");

	// begin desugarizing for loop into while loop
	// first add the body of the while loop
	std::vector<std::shared_ptr<Stmt>> body = { statement()};
	body.push_back(tail);
	std::shared_ptr<Stmt> whileBody = std::shared_ptr<Stmt> (new BlockStmt(body));
	// create the while loop with the for loop condition
	std::shared_ptr<Stmt> whileLoop = std::shared_ptr<Stmt> 
						(new WhileStmt(condition, whileBody));
	// if there is no initializer we are done
	if(initialStmt == nullptr)
		return whileLoop;
	// create a new block scope in which the initializer and loop reside
	std::vector<std::shared_ptr<Stmt>> outerBlockStmts = {initialStmt, whileLoop};
	// return new block scope
	return std::shared_ptr<Stmt> (new BlockStmt(outerBlockStmts));
}
std::shared_ptr<Stmt> Parser::expressionStatement() {
	// retrieve expression
	std::shared_ptr<Expr> expr = expression();
	consume(TokenType::SEMICOLON, "Expected ';' at end of expression");
	return std::shared_ptr<Stmt>(new ExpressionStmt(expr));
}
std::shared_ptr<Stmt> Parser::varDeclaration() {
	Token name = consume(TokenType::IDENTIFIER, "Expected variable name");
	std::shared_ptr<Expr> initializer = nullptr;
	// check if variable is initialized 
	if(check(TokenType::EQUAL)) {
		advance();
		initializer = expression();
	}
	consume(TokenType::SEMICOLON, "Expected ';' at end of variable declaration");
	return std::shared_ptr<Stmt> (new VarStmt(name, initializer));
}

Token Parser::consume(TokenType type, const std::string& errorMessage) {
	if(check(type)) return advance();
	staticError::reportParserError(tokens_[current_], errorMessage);
	successState_ = false;
	catchError_ = true;
	return Token(TokenType::NIL, "", 1);
}
void Parser::synchronize() {
	advance();
	catchError_ = false;
	for(; !isAtEnd(); advance()) {
		if(tokens_[current_-1].type == TokenType::SEMICOLON) return;

		switch(tokens_[current_].type) {
			case TokenType::CLASS:
			case TokenType::FUN:
			case TokenType::VAR:
			case TokenType::FOR:
			case TokenType::IF:
			case TokenType::WHILE:
			case TokenType::PRINT:
			case TokenType::RETURN:
				return;
		}
	}
}
bool Parser::getSuccess() {return successState_;}
