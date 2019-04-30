#include "pch.h"
#include "TypedNum.h"

#include <vector>

#include <iostream>

std::vector<std::string> strSplit(std::string str, char sym) {
	std::vector<std::string> strs;
	int lastSplit = 0;
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == sym) {
			strs.push_back(str.substr(lastSplit, i));
			lastSplit = i;
		}
	}
	strs.push_back(str.substr(lastSplit));
	return strs;
}

double getVal(std::string str) {
	int i = 0;
	for (i = 0; i < str.length() && (isdigit(str[i]) || str[i] == '.'); i++);
	if (i == str.length())
		return std::stod(str);
	if (i == 0)
		return 1;
	return std::stod(str.substr(0, i));
}

std::string getType(std::string str) {
	int i = 0;
	for (i = 0; i < str.length() && (isdigit(str[i]) || str[i] == '.'); i++);
	return str.substr(i);
}

std::string cutLastNull(std::string in) {
	int i = 0;
	for (i = in.length() - 1; i >= 0 && (in[i] == '0'); i--);
	if (in[i] == '.')
		i--;
	return in.substr(0, i+1);
}

TypedNum::TypedNum(std::string in) {
	if (in.length() == 0)
		return;
	std::vector<std::string> strs = strSplit(in, '+');
	for (auto str : strs) {
		vals[getType(str)] = getVal(str);
		//std::cout << "type: " << getType(str) << "; val: " << getVal(str) << std::endl;
	}
}

TypedNum::TypedNum(std::map<ElasticType, double> vals) {
	this->vals = vals;
}

std::string TypedNum::toString() {
	std::string ret, type;
	for (auto val : this->vals) {
		if (ret.length() > 0)
			ret += (val.second >= 0)?"+":"";
		type = val.first.toString();
		ret += cutLastNull(std::to_string(val.second));
		if (type.size() > 0)
			ret += "[" + type + "]";
	}
	return ret;
}

TypedNum::~TypedNum()
{
}

TypedNum operator+(const TypedNum& left, const TypedNum& right) {
	std::map<ElasticType, double> out = left.vals;
	for (auto val : right.vals) {
		if (out.count(val.first) > 0)
			out[val.first] += val.second;
		else
			out[val.first] = val.second;
	}
	return TypedNum(out);
}

TypedNum operator-(const TypedNum& left, const TypedNum& right) {
	std::map<ElasticType, double> out = left.vals;
	for (auto val : right.vals) {
		if (out.count(val.first) > 0)
			out[val.first] -= val.second;
		else
			out[val.first] = -val.second;
	}
	return TypedNum(out);
}

TypedNum operator*(const TypedNum& left, const TypedNum& right) {
	std::map<ElasticType, double> out;
	for (auto rval : right.vals) {
		for (auto lval : left.vals) {
			if (lval.first.types.size() != 0 && rval.first.types.size() != 0)
				out[lval.first + rval.first] += lval.second * rval.second;
			else
				out[(lval.first.types.size() != 0)?lval.first:rval.first] = lval.second * rval.second;
		}
	}
	return TypedNum(out);
}

TypedNum operator/(const TypedNum& left, const TypedNum& right) {
	std::map<ElasticType, double> out;
	for (auto rval : right.vals) {
		for (auto lval : left.vals) {
			if (lval.first.types.size() != 0 && rval.first.types.size() != 0)
				out[lval.first - rval.first] = lval.second / rval.second;
			else
				out[(lval.first.types.size() != 0) ? lval.first : rval.first] = lval.second / rval.second;
		}
	}
	return TypedNum(out);
}

TypedNum operator^(const TypedNum& left, const TypedNum& right) {
	if (right.vals.size() != 1 || right.vals.count(ElasticType("")) != 1)
		throw std::string("pow to non-simple-number");
	TypedNum out = TypedNum("1");
	for (int i = 0; i < right.vals.at(ElasticType("")); i++) {
		out = out * left;
	}

	return out;
}