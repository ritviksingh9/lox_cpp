#include <stdexcept>
#include <string>

#include "types/token.hpp"

namespace staticError {

void reportScannerError(int line, const std::string& message);
void reportParserError(const Token& Tok, const std::string& message);
}
