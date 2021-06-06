#include "expr.hpp"

inline std::string parenthesize(const std::string& str,
			 const std::vector<Expr*>& expressions) {
	std::string strRep = "(";
	strRep.append(str);
	for(auto x: expressions) {
		strRep.append(" ");
		strRep.append(x -> getString());
	}
	strRep.append(")");

	return strRep;
}
template <class T>
std::string Binary<T>::getString() const {
	std::vector<Expr*> expressions = {left, right};
	return parenthesize(op.lexeme, expressions);
}
template <class T>
std::string Literal<T>::getString() const {
	if(value == NULL) return "nil";
	if(typeid(value) == typeid(double)) 
		return std::to_string(value);
	return std::to_string(value);
}
template <class T>
std::string Unary<T>::getString() const {
	std::vector<Expr*> expressions = {right};
	return parenthesize(op.lexeme, expressions);
}

