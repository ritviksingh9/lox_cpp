#include "types/loxGeneric.hpp"

//constructor
LoxGeneric::LoxGeneric() : type{GenericType::NONE},
			   boolValue(false), 
			   numValue(0), 
			   strValue("") {};
LoxGeneric::LoxGeneric(bool val) : type{GenericType::BOOL},
				   boolValue(val), 
				   numValue(0), 
				   strValue("") {};
LoxGeneric::LoxGeneric(double val) : type{GenericType::NUM},
				     boolValue(false), 
				     numValue(val), 
				     strValue("") {};
LoxGeneric::LoxGeneric(std::string val) : type{GenericType::STRING},
					  boolValue(false), 
					  numValue(0), 
					  strValue(val) {};

bool LoxGeneric::getTruthValue() {
	if(type == GenericType::NONE) return false;
	if(type == GenericType::BOOL) return boolValue;
	if(type == GenericType::NUM) return !(numValue == 0);
	return true;
}

//arithmetic operations
LoxGeneric operator+(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return LoxGeneric(left.numValue+right.numValue);
	else if(left.type == GenericType::STRING && right.type == GenericType::STRING)
		return LoxGeneric(left.strValue+right.strValue);
	return LoxGeneric();//throw error
}
LoxGeneric operator-(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return LoxGeneric(left.numValue-right.numValue);
	return LoxGeneric();//throw error
}
LoxGeneric operator*(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return LoxGeneric(left.numValue*right.numValue);
	return LoxGeneric();//throw error
}
LoxGeneric operator/(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return LoxGeneric(left.numValue/right.numValue);
	return LoxGeneric();//throw error
}
//comparison operators
bool operator==(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::BOOL && right.type == GenericType::BOOL)
		return left.boolValue == right.boolValue;
	else if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return left.numValue == right.numValue;
	else if(left.type == GenericType::STRING && right.type == GenericType::STRING)
		return left.strValue == right.strValue;
	return true; //condition where we are comparing two null expressions
}
bool operator!=(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::BOOL && right.type == GenericType::BOOL)
		return left.boolValue != right.boolValue;
	else if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return left.numValue != right.numValue;
	else if(left.type == GenericType::STRING && right.type == GenericType::STRING)
		return left.strValue != right.strValue;
	return false; //condition where we are comparing two null expressions
}
bool operator>=(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return left.numValue >= right.numValue;
	return false;
}
bool operator<=(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return left.numValue <= right.numValue;
	return false;
}
bool operator>(const LoxGeneric& left, const LoxGeneric& right) {
		return left.numValue > right.numValue;
	return false;
}
bool operator<(const LoxGeneric& left, const LoxGeneric& right) {
	if(left.type == GenericType::NUM && right.type == GenericType::NUM)
		return left.numValue < right.numValue;
	return false;
}
