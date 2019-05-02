#pragma once

#include "ElasticType.h"
#include <functional>
#include <string>
#include <map>

class TypedNum
{
public:
	explicit TypedNum(std::string val = "", bool complex = false);
	explicit TypedNum(std::map<ElasticType, double> vals);
	~TypedNum();

	std::string toString() const;

	TypedNum binOperator(std::function<
		std::pair<ElasticType, double>(ElasticType, double)
	> fnc) const;
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