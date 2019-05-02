#pragma once

#include "CalcFncVarController.h"
#include "TypedNum.h"
#include <functional>
#include <string>

class CalcNode {
public:
	enum NodeType { NUM, SUM, SUB, MUL, DIV, POW, BRC, FNC, VAR };

	CalcNode(std::string exp = "", CalcFncVarController* fncVar = nullptr);
	~CalcNode();
	
	void parse();
	TypedNum comp();
	TypedNum cComp() const;
	std::string getExp() const;
	std::stringstream toLinedText(int level = -1) const;

private:
	NodeType type;
	std::string exp;
	std::string symName;
	TypedNum val;
	CalcNode* left = nullptr;
	CalcNode* right = nullptr;
	bool isCached = false;

	CalcFncVarController* fncVar = nullptr;

	friend std::string toLinedText(int tabs);
};

