#include <stdexcept>
#include <string>

#include "types/token.hpp"

void reportScannerError(int line, std::string message);
void reportParserError(Token Tok, std::string message);
