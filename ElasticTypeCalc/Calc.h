#pragma once

#include "CalcFncVarController.h"
#include "TypedNum.h"
#include "CalcNode.h"
#include <string>

class Calc
{
public:
	Calc(std::string exp = "");
	TypedNum comp();
	TypedNum cComp() const;
	void parse();
	void print(char fillSym = '_', char splitSym = '|') const;
	CalcFncVarController* controller();
	~Calc();
private:
	std::string exp;
	CalcNode* root = nullptr;
	CalcFncVarController varFnc;

};

