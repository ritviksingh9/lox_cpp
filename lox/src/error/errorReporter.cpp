#include <iostream>

#include "error/errorReporter.hpp"

void reportError(int line, std::string message) { 
//	throw std::runtime_error("Line: "+std::to_string(line)+" "+message);
	std::cerr << "ERROR: Line "<< line << " " << message <<  std::endl;
}
