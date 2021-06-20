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
		return std::shared_ptr<Expr>(new IdentifierExpr(tokens_[current_-1].lexeme));
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
	std::vector <TokenType> keyTypes = {TokenType::EQUAL, TokenType::BANG_EQUAL};

	while(match(keyTypes)) {
		Token op = tokens_[current_-1];
		std::shared_ptr<Expr> right = comparison();
		expr = std::shared_ptr<Expr>(new Binary(expr, op, right));
	}
	return expr;
}
std::shared_ptr<Expr> Parser::expression() { return equality();}
std::vector<std::shared_ptr<Stmt>> Parser::parse() {
	std::vector<std::shared_ptr<Stmt>> statements;
	while (!isAtEnd()) {
		if(check(TokenType::VAR)) {
			advance();
			statements.push_back(varDeclaration());
		}
		else 
			statements.push_back(statement());
		//synchronize to the next statement/declaration
		if(catchError_)
			synchronize();
	}
	return statements;
}

std::shared_ptr<Stmt> Parser::statement() {
	if(check(TokenType::PRINT)) {
		advance();
		return printStatement();
	}
	return expressionStatement();
}
std::shared_ptr<Stmt> Parser::printStatement() {
	std::shared_ptr<Expr> expr = expression();
	consume(TokenType::SEMICOLON, "Expected ';' at end of statement");
	return std::shared_ptr<Stmt>(new PrintStmt(expr));
}
std::shared_ptr<Stmt> Parser::expressionStatement() {
	std::shared_ptr<Expr> expr = expression();
	consume(TokenType::SEMICOLON, "Expected ';' at end of expression");
	return std::shared_ptr<Stmt>(new ExpressionStmt(expr));
}
std::shared_ptr<Stmt> Parser::varDeclaration() {
	Token name = consume(TokenType::IDENTIFIER, "Expected variable name");
	std::shared_ptr<Expr> initializer = nullptr;
	//check if variable is initialized 
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
