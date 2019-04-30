#pragma once

#include "TypedNum.h"
#include <string>

class CalcNode
{
public:
	CalcNode(std::string exp = "");
	~CalcNode();
	
	void parse();
	TypedNum comp();
	void print(int tabs);

	enum NodeType { NUM, SUM, SUB, MUL, DIV, POW, BRC };
private:
	NodeType type;
	std::string exp;
	TypedNum val;
	CalcNode* left;
	CalcNode* right;
};

