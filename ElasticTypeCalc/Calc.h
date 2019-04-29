#pragma once

#include "TypedNum.h"
#include "CalcNode.h"
#include <string>

class Calc
{
public:
	Calc(std::string exp = "");
	CALC_TYPE comp();
	~Calc();
private:
	std::string exp;
	CalcNode* root = nullptr;

};

