#include <vector>
#include <map>

#include "token.hpp"

class Scanner {
private:	
	int start;
	int current;
	int line;
	std::string source;
	std::vector<Token*> tokens;
	static const std::map<std::string, TokenType> keywords;

	void scanToken();
	void identifier();
	void number();
	void string();
	bool match(char expected);
	char peek();
	char peekNext();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	bool isDigit(char c);
	bool isAtEnd();
	char advance();
	void addToken(TokenType type);
	template<typename T>
	void addToken(TokenType type, T literal);

	static std::map<std::string, TokenType> initMap();

public:
	Scanner(const std::string& source);
	std::vector<Token> scanTokens();
};
