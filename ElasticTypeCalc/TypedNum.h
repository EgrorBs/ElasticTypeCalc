#pragma once

#include "ElasticType.h"
#include <string>
#include <map>

class TypedNum
{
public:
	TypedNum(std::string val = "");
	TypedNum(std::map<ElasticType, double> vals);
	std::string toString();
	~TypedNum();

	std::map<ElasticType, double> vals;
};

TypedNum operator+(const TypedNum& left, const TypedNum& right);

TypedNum operator-(const TypedNum& left, const TypedNum& right);

TypedNum operator*(const TypedNum& left, const TypedNum& right);

TypedNum operator/(const TypedNum& left, const TypedNum& right);

TypedNum operator^(const TypedNum& left, const TypedNum& right);