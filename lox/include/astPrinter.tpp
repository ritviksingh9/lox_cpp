#include <sstream>

#include "expr.hpp"

template <class T>
std::string Literal<T>::getString() const {
/*	if(value == NULL) return "nil";
	if(typeid(value) == typeid(double)) 
		return std::to_string(value);
	else if(typeid(value) == typeid(std::string))
		return value;
	return "nil";i*/
	if(typeid(value) == typeid(double) ||
	   typeid(value) == typeid(std::string)) {
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}	
	return "nil";
}


