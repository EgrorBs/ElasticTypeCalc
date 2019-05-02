#pragma once

#include "CalcFncVarController.h"
#include "TypedNum.h"
#include <functional>
#include <string>

class CalcNode {
public:
	CalcNode(std::string exp = "", CalcFncVarController* fncVar = nullptr);
	~CalcNode();
	
	void parse();
	TypedNum comp();
	TypedNum cComp() const;
	void print(int tabs = 0) const;

	enum NodeType { NUM, SUM, SUB, MUL, DIV, POW, BRC, FNC, VAR };
private:
	NodeType type;
	std::string exp;
	std::string symName;
	TypedNum val;
	CalcNode* left = nullptr;
	CalcNode* right = nullptr;
	bool isCached = false;

	CalcFncVarController* fncVar = nullptr;
};

