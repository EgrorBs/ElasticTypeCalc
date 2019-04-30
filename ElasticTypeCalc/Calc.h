#pragma once

#include "TypedNum.h"
#include "CalcNode.h"
#include <string>

class Calc
{
public:
	Calc(std::string exp = "");
	TypedNum comp();
	void print();
	~Calc();
private:
	std::string exp;
	CalcNode* root = nullptr;

};

