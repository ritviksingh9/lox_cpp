#ifndef LOXGENERIC_H
#define LOXGENERIC_H

#include <memory>
#include <string>

enum GenericType {BOOL, NUM, STRING};

struct LoxGeneric {
	GenericType type;

	bool boolValue;
	double numValue;
	std::string strValue;
	//constructor for different types	
	LoxGeneric(bool val);
	LoxGeneric(double val);
	LoxGeneric(std::string val);
	//getters
	bool getBool();
	double getNum();
	std::string getStr();
};

#endif
