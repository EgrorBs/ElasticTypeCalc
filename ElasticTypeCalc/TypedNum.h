#pragma once

#include <string>
#include <map>

class TypedNum
{
public:
	TypedNum(std::string val = "");
	TypedNum(std::map<std::string, double> vals);
	std::string toString();
	~TypedNum();

	std::map<std::string, double> vals;
};

TypedNum operator+(const TypedNum& left, const TypedNum& right);

TypedNum operator-(const TypedNum& left, const TypedNum& right);

TypedNum operator*(const TypedNum& left, const TypedNum& right);

TypedNum operator/(const TypedNum& left, const TypedNum& right);

TypedNum operator^(const TypedNum& left, const TypedNum& right);