#include "types/loxGeneric.hpp"

//constructor
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

//getters
bool LoxGeneric::getBool() {return boolValue;}
double LoxGeneric::getNum() {return numValue;}
std::string LoxGeneric::getStr() {return strValue;}

