#pragma once

#include <string>
#include <map>

class ElasticType
{
public:
	ElasticType(std::string val = "");
	ElasticType(std::map<std::string, int> types);
	std::string toString() const;
	~ElasticType();

	std::map<std::string, int> types;
};

ElasticType operator+(const ElasticType& left, const ElasticType& right);

ElasticType operator-(const ElasticType& left, const ElasticType& right);

ElasticType operator*(const ElasticType& left, int pow);

bool operator<(const ElasticType& left, const ElasticType& right);