#include "expr.hpp"

template <class T>
std::string Literal<T>::getString() const {
	if(value == NULL) return "nil";
	if(typeid(value) == typeid(double)) 
		return std::to_string(value);
	return std::to_string(value);
}


