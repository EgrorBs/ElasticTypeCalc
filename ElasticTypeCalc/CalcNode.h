#pragma once

#include "TypedNum.h"
#include <string>

class CalcNode {
public:
	CalcNode(std::string exp = "");
	~CalcNode();
	
	void parse();
	TypedNum comp();
	TypedNum cComp() const;
	void print(int tabs = 0) const;

	enum NodeType { NUM, SUM, SUB, MUL, DIV, POW, BRC };
private:
	NodeType type;
	std::string exp;
	TypedNum val;
	CalcNode* left = nullptr;
	CalcNode* right = nullptr;
	bool isCached = false;
};

