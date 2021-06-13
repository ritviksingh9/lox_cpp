#ifndef LOXGENERIC_H
#define LOXGENERIC_H

#include <memory>
#include <string>

enum class GenericType {BOOL, NUM, STRING, NONE};

struct LoxGeneric {
	GenericType type;

	bool boolValue;
	double numValue;
	std::string strValue;
	//constructor for different types	
	LoxGeneric();
	LoxGeneric(bool val);
	LoxGeneric(double val);
	LoxGeneric(std::string val);
	//whether something is "true"
	bool getTruthValue();
	//arithmetic operators
	friend LoxGeneric operator+(const LoxGeneric& left, const LoxGeneric& right);
	friend LoxGeneric operator-(const LoxGeneric& left, const LoxGeneric& right);
	friend LoxGeneric operator*(const LoxGeneric& left, const LoxGeneric& right);
	friend LoxGeneric operator*(const LoxGeneric& expr, double multiplicand);
	friend LoxGeneric operator/(const LoxGeneric& left, const LoxGeneric& right);
	//comparison operators
	friend bool operator==(const LoxGeneric& left, const LoxGeneric& right);
	friend bool operator!=(const LoxGeneric& left, const LoxGeneric& right);
	friend bool operator>=(const LoxGeneric& left, const LoxGeneric& right);
	friend bool operator<=(const LoxGeneric& left, const LoxGeneric& right);
	friend bool operator>(const LoxGeneric& left, const LoxGeneric& right);
	friend bool operator<(const LoxGeneric& left, const LoxGeneric& right);
	
};

#endif
