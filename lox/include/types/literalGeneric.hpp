#include <string>

//this is a light wrapper for bool, double, std::string, and null types for literals
//prevents a lot of headache with templates
//should be different than the LoxGeneric type because this is smaller in scope
enum class LiteralType {BOOL, NUM, STRING, NONE};

struct LiteralGeneric {
	LiteralType type;

	bool boolValue;
	double numValue;
	std::string strValue;
	//constructor for different types
	LiteralGeneric() : boolValue(false),
			   numValue(0),
			   strValue(""),
			   type(LiteralType::NONE) {};
	LiteralGeneric(bool val) : boolValue(val),
				   numValue(0),
				   strValue(""),
				   type(LiteralType::BOOL) {};
	LiteralGeneric(double val) : boolValue(false),
				     numValue(val),
				     strValue("false"),
				     type(LiteralType::NUM) {};
	LiteralGeneric(std::string val) : boolValue(false),
 				     	  numValue(0),
				     	  strValue(""),
					  type(LiteralType::STRING) {};
};
