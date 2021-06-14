#include <iostream>

#include "error/runtimeErrorHandler.hpp"

namespace runtimeError {

void reportRuntimeError(const std::string& message) {
	std::cerr << message << std::endl;
}
}
