#pragma once

#include "ElasticType.h"
#include <string>
#include <map>

class TypedNum
{
public:
	TypedNum(std::string val = "", bool complex = false);
	TypedNum(std::map<ElasticType, double> vals);
	std::string toString() const;
	~TypedNum();

private:
	std::map<ElasticType, double> vals;

	static double getVal(std::string str);
	static std::string getType(std::string str);
	static std::string cutLastNull(std::string in);

	friend TypedNum operator+(const TypedNum& left, const TypedNum& right);
	friend TypedNum operator-(const TypedNum& left, const TypedNum& right);
	friend TypedNum operator*(const TypedNum& left, const TypedNum& right);
	friend TypedNum operator/(const TypedNum& left, const TypedNum& right);
	friend TypedNum operator^(const TypedNum& left, const TypedNum& right);
};

TypedNum operator+(const TypedNum& left, const TypedNum& right);

TypedNum operator-(const TypedNum& left, const TypedNum& right);

TypedNum operator*(const TypedNum& left, const TypedNum& right);

TypedNum operator/(const TypedNum& left, const TypedNum& right);

TypedNum operator^(const TypedNum& left, const TypedNum& right);