#include "pch.h"
#include "ElasticType.h"
#include <cmath>

ElasticType::ElasticType(std::string val) {
	this->types[val] = 1;
	if (this->types.count(""))
		this->types.erase("");
}

ElasticType::ElasticType(std::map<std::string, int> types) {
	this->types = types;
}

std::string ElasticType::toString() const {
	std::string plus;
	for (auto type : this->types) {
		if (type.second <= 0 || type.first == "")
			continue;
		if (plus.size() > 0)
			plus += "*";
		plus += type.first;
		if (type.second > 1)
			plus += "^" + std::to_string(type.second);
	}

	std::string minus;
	for (auto type : this->types) {
		if (type.second >= 0 || type.first == "")
			continue;
		if (minus.size() > 0)
			minus += "*";
		minus += type.first;
		if (-type.second > 1)
			minus += "^" + std::to_string(-type.second);
	}

	std::string ret;

	if (plus.size() > 0) {
		if (minus.size() > 0) {
			ret += "(" + plus + ")";
		} else {
			ret += plus;
		}
	}

	if (minus.size() > 0) {
		if (plus.size() > 0) {
			ret += "/(" + minus + ")";
		} else {
			ret += "1/" + minus;
		}
	}

	return ret;
}

ElasticType::~ElasticType()
{
}

ElasticType ElasticType::binOperator(std::function<std::pair<std::string, int>(std::string, int)> fnc) const {
	std::map<std::string, int> out;
	std::pair<std::string, int> retPair;
	for (auto pair : this->types) {
		retPair = fnc(pair.first, pair.second);
		if (out.count(retPair.first))
			out[retPair.first] += retPair.second;
		else
			out[retPair.first] = retPair.second;
	}
	return ElasticType(out);
}

ElasticType operator+(const ElasticType& left, const ElasticType& right) {
	std::map<std::string, int> out = left.types;
	for (auto rval : right.types) {
		out[rval.first] += rval.second;
		if (out[rval.first] == 0)
			out.erase(rval.first);
	}
	if (out.count(""))
		out.erase("");
	return ElasticType(out);
}

ElasticType operator-(const ElasticType& left, const ElasticType& right) {
	std::map<std::string, int> out = left.types;
	for (auto rval : right.types) {
		out[rval.first] -= rval.second;
		if (out[rval.first] == 0)
			out.erase(rval.first);
	}
	if (out.count(""))
		out.erase("");
	return ElasticType(out);
}

ElasticType operator*(const ElasticType& left, int pow) {
	std::map<std::string, int> out;
	for (auto val : left.types) {
		out[val.first] = val.second * pow;
		if (out[val.first] == 0)
			out.erase(val.first);
	}
	if (out.count(""))
		out.erase("");
	return ElasticType(out);
}

bool operator<(const ElasticType& left, const ElasticType& right) {
	if (left.types.size() < right.types.size())
		return true;

	unsigned int leftSum = 0;
	for (auto pair : left.types) {
		leftSum += std::abs(pair.second);
	}

	unsigned int rightSum = 0;
	for (auto pair : right.types) {
		rightSum += std::abs(pair.second);
	}

	if (leftSum < rightSum)
		return true;

	return left.toString() < right.toString();
}

bool operator==(const ElasticType& left, const ElasticType& right) {
	if (left.types.size() != right.types.size())
		return false;

	unsigned int leftSum = 0;
	for (auto pair : left.types) {
		leftSum += std::abs(pair.second);
	}

	unsigned int rightSum = 0;
	for (auto pair : right.types) {
		rightSum += std::abs(pair.second);
	}

	if (leftSum != rightSum)
		return false;

	return left.toString() == right.toString();
}

bool operator!=(const ElasticType& left, const ElasticType& right) {
	return !(left == right);
}
