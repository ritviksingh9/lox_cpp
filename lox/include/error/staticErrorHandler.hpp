#ifndef STATICERROR_H
#define STATICERROR_H

#include <stdexcept>
#include <string>

#include "types/token.hpp"

namespace staticError {

void reportScannerError(int line, const std::string& message);
void reportParserError(const Token& Tok, const std::string& message);
void reportSyntaxError(const Token& tok);
void reportSyntaxError(const Token& tok, const std::string& message);
}

#endif
