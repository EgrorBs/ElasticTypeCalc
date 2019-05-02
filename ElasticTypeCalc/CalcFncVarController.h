#pragma once

#include "TypedNum.h"
#include <map>
#include <vector>
#include <functional>

class CalcFncVarController {
public:
	CalcFncVarController();
	~CalcFncVarController();

	void setVar(std::string var, TypedNum value);
	void setFnc(std::string name, std::function<TypedNum(TypedNum)>* fnc);

	void delVar(std::string var);
	void delFnc(std::string fnc);

	bool isVar(std::string var) const;
	bool isFnc(std::string fnc) const;

	TypedNum compVar(std::string var) const;
	TypedNum compFnc(std::string fnc, TypedNum par) const;

	unsigned int addOnChange(std::function<void(void)> cb);
	void delOnChange(unsigned int id);

private:
	std::map<unsigned int, std::function<void(void)>> onChange;
	//TODO : mulparams https://gist.github.com/sjrdc/5ff96d8c40b8714e7fb828bd3f86e72c
	std::map<std::string, std::function<TypedNum(TypedNum)>*> fncs;
	std::map<std::string, TypedNum> vars;
};

