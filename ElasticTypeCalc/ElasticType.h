#pragma once

#include <functional>
#include <string>
#include <map>

class ElasticType
{
public:
	explicit ElasticType(std::string val = "");
	explicit ElasticType(std::map<std::string, int> types);
	std::string toString() const;
	~ElasticType();

	ElasticType binOperator(std::function<
		std::pair<std::string, int>(std::string, int)
	> fnc) const;

private:
	std::map<std::string, int> types;

	friend ElasticType operator+(const ElasticType& left, const ElasticType& right);
	friend ElasticType operator-(const ElasticType& left, const ElasticType& right);
	friend ElasticType operator*(const ElasticType& left, int pow);
	friend bool operator<(const ElasticType& left, const ElasticType& right);
	friend bool operator==(const ElasticType& left, const ElasticType& right);
	friend bool operator!=(const ElasticType& left, const ElasticType& right);
};

ElasticType operator+(const ElasticType& left, const ElasticType& right);

ElasticType operator-(const ElasticType& left, const ElasticType& right);

ElasticType operator*(const ElasticType& left, int pow);

bool operator<(const ElasticType& left, const ElasticType& right);

bool operator==(const ElasticType& left, const ElasticType& right);

bool operator!=(const ElasticType& left, const ElasticType& right);