#pragma once

#define CALC_TYPE TypedNum

#include "TypedNum.h"
#include <string>

class CalcNode
{
public:
	CalcNode(std::string exp = "");
	~CalcNode();
	
	void parse();
	CALC_TYPE comp();

	enum NodeType { NUM, SUM, SUB, MUL, DIV, POW, BRC };
private:
	NodeType type;
	std::string exp;
	CALC_TYPE val;
	CalcNode* left;
	CalcNode* right;
};

